#include "VideoCaptrue.h"
#include "ISMSSDK.h"

#include <QtCore/QtCore>
#include <QList>
#include <tuple>
#include <QFile>
#include <windows.h>
#include <log.h>
#include <chrono>
#include <utility>
#include <QDir>
#include "settingconfig.h"
#include "HttpConnect.h"
#include "defaultsetting.h"
#include "main.h"
QMutex _mtx;
volatile int curScreenshotIndex = 0;
volatile bool threadrun = true;
volatile int capturenum = 0;
volatile int loginstatus = 0; //
volatile bool testthreadflg = false;
QMutex capturemtx;
QMutex loginMutex;
sockets_s  socketd[SOCKET_SIZE];
static bool isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if (dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkpath(fullPath);//创建多级目录
        return ok;
    }
}
static int64_t ot() {
    using namespace std::chrono;
    auto const elapsed = system_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(elapsed).count();
}
static QString m_SnapFolder;
static CHttpConnect *s_http = nullptr;
typedef struct camaredata_s
{
    QString uuid;
    QString name;
    int tcpvalue;
    int frequency;
    volatile uint64_t timestamp;
    volatile int cnt;
    volatile int handle;
}camaredata_s;
using cameradata = std::tuple<QString,QString,int,int,uint64_t,int,int>;
static QList<camaredata_s> cameraNodeList;
static QList<std::tuple<QString, QString>> camerainfo({  //监控点编号uuid ,名字
std::make_tuple("",u8"北小吃区餐厅"),
std::make_tuple("",u8"北杭州味道通道"),
std::make_tuple("",u8"北监控室前停车场"),
std::make_tuple("", u8"北建德三宝窗口"),
std::make_tuple("", u8"北肯德基大门"),
std::make_tuple("", u8"北男厕所入口"),
std::make_tuple("", u8"北世纪联华门口"),
std::make_tuple("", u8"北中式快餐厅"),
std::make_tuple("", u8"北中式快餐厅(收银处)"),
std::make_tuple("", u8"南厕所通道"),
std::make_tuple("", u8"南超长车广场"),
std::make_tuple("", u8"南进口货车广场"),
std::make_tuple("", u8"南肯德基店内"),
std::make_tuple("", u8"南区机房门口"),
std::make_tuple("", u8"南区监控室前停车场"),
std::make_tuple("", u8"南小吃区餐厅"),
std::make_tuple("", u8"南星巴克大门"),
std::make_tuple("", u8"南中餐厅"),
std::make_tuple("", u8"南中门通道"),
std::make_tuple("", u8"南员工通道"),
std::make_tuple("", u8"北星巴克对面消防通道"),
std::make_tuple("", u8"南小吃收银"),
});

void VideoCaptrue::setThreadRunFlg(bool state)
{
    threadrun = state;
}
VideoCaptrue::VideoCaptrue()
{
}


VideoCaptrue::~VideoCaptrue()
{
}
bool VideoCaptrue::CamerainfoInit()
{
    int arraysize = Setting::getInstance()->getSetting()->beginReadArray("camera");
    if (arraysize <= 0)
    {
        Setting::getInstance()->getSetting()->endArray();
        Setting::getInstance()->getSetting()->beginWriteArray("camera");
        for (int i = 0; i < 1; ++i) {
            Setting::getInstance()->getSetting()->setArrayIndex(i);
            Setting::getInstance()->getSetting()->setValue("uuid", defaultSetting::camerainfo[i][0]);
            Setting::getInstance()->getSetting()->setValue("name", defaultSetting::camerainfo[i][1]);
            Setting::getInstance()->getSetting()->setValue("tcpvalue", defaultSetting::camerainfo[i][2]);
            Setting::getInstance()->getSetting()->setValue("frequency", defaultSetting::camerainfo[i][3]);
        }       
    }
    Setting::getInstance()->getSetting()->endArray();
    arraysize = Setting::getInstance()->getSetting()->beginReadArray("camera");
    cameraNodeList.clear();
    Log::instance().p(YLOG_INFO, "获取摄像头点位数量:%d", arraysize);
    for (int i = 0; i < arraysize; ++i) {
        camaredata_s  data;
        Setting::getInstance()->getSetting()->setArrayIndex(i);
        data.uuid = Setting::getInstance()->getSetting()->value("uuid").toString();
        data.name = Setting::getInstance()->getSetting()->value("name").toString();
        data.tcpvalue = Setting::getInstance()->getSetting()->value("tcpvalue").toInt();
        data.frequency = Setting::getInstance()->getSetting()->value("frequency").toInt();
        Log::instance().p(YLOG_INFO, "camera uuid:%s,name:%s,tcpvalue:%d,frequency:%d", data.uuid.toStdString().c_str(), data.name.toStdString().c_str(), data.tcpvalue, data.frequency);
        cameraNodeList.push_back(data);
    }
    Setting::getInstance()->getSetting()->endArray();
    if (s_http)
    {
        for (auto scocket :socketd)
        {
            closesocket(scocket.socked);
        }
        delete s_http;
    }
    s_http = new CHttpConnect();
    for (int i = 0; i < SOCKET_SIZE; i++)
    {
        s_http->socketInit("127.0.0.1",i, socketd[i]);
    }
        
 
    m_SnapFolder = Setting::getInstance()->getSetting()->value("basic/picpath").toString();
    isDirExist(m_SnapFolder);
    //for (int i = 0; i < cameraNodeList.size(); i++)
    //{
    //    QString detailpath = m_SnapFolder + "\\" + QString::number(i + 1);
    //    isDirExist(detailpath);
    //}

    int runtime = Setting::getInstance()->getSetting()->value("basic/runtime").toInt();
    if (runtime > 0)
    {
        testthreadflg = true;
        QString path = m_SnapFolder + "\\test";
        isDirExist(path);
        Log::instance().p(YLOG_INFO, "测试保存图片路径为：%s", path.toStdString().c_str());
    }
    else
    {
        Log::instance().p(YLOG_INFO, "保存图片路径为：%s", m_SnapFolder.toStdString().c_str());
        testthreadflg = false;
    }
    return true;
}
bool VideoCaptrue::Logininit()
{
    Logindestroy();
    //CrashAPI_Init();
    //CrashAPI_SetDumpType(FullDumpType);
    loginstatus = 1;
    int iRet;
    int reslut;
    iRet = ISMS_Init();
    if (iRet != 0)
    {
        Log::instance().p(YLOG_ERROR, "初始化失败 错误码：%d", ISMS_GetLastError());
        return false;
    }
    loginstatus = 2;
    std::string strip = Setting::getInstance()->getSetting()->value("basic/ip").toString().toStdString();
    int port = Setting::getInstance()->getSetting()->value("basic/port").toInt();
    std::string strusername = Setting::getInstance()->getSetting()->value("basic/username").toString().toStdString();
    std::string strpassword = Setting::getInstance()->getSetting()->value("basic/password").toString().toStdString();
    reslut = ISMS_Login(strip.c_str(), port, strusername.c_str(), strpassword.c_str());
    if (reslut == -1)
    {
        Log::instance().p(YLOG_ERROR, "登录失败,ip:%s,port:%d,user:%s,password:%s 错误码：%d",strip.c_str(),port,strusername.c_str(),strpassword.c_str(), ISMS_GetLastError());
        return false;
    }
    else
    {
        Log::instance().p(YLOG_INFO, "登录成功 ,ip:%s,port:%d,user:%s,password:%s", strip.c_str(), port, strusername.c_str(), strpassword.c_str(), ISMS_GetLastError());        
    }
    loginstatus = 3;

    return true;
}
bool VideoCaptrue::CameraInit()
{
    int iPage = 1;
    __int64 i64Time = 0;
    PISMS_CAMERA pCameraArray = new (std::nothrow) ISMS_CAMERA[PAGE_SIZE_REQ];
    if (NULL == pCameraArray)
    {
        Log::instance().p(YLOG_ERROR, "ISMS_CAMERA 分配内存失败");
        return false;
    }
    while (true)
    {
        ISMS_PAGE_REQ stReq;
        ISMS_PAGE_RSP stRsp;
        stReq.iPageNo = iPage;
        stReq.iPageRows = PAGE_SIZE_REQ;
        stReq.iLastUpdateTime = 0;   // 全量获取监控点
        int iRet = ISMS_GetCameraInfo(&stReq, &stRsp, pCameraArray);
        if (iRet != ISMS_ERR_NOERROR)
        {
            Log::instance().p(YLOG_ERROR, "全量获取监控点信息出错!，错误码:%d", ISMS_GetLastError());
            delete[] pCameraArray;
            return false;
        }
        if (0 == stRsp.iRealRows)
            break;
        if (1 == iPage)
        {
            i64Time = stRsp.iUpdateTime;
        }
        else
        {
            if (i64Time > stRsp.iUpdateTime)
            {
                i64Time = stRsp.iUpdateTime;
            }
        }
/*        for (int i = 0; i < stRsp.iRealRows; ++i)
        {
            int size = camerainfo.size();
            for (int j = 0; j < size; ++j)
            {
                if (std::get<1>(camerainfo[j]) == pCameraArray[i].szCameraName)
                {
                    std::get<0>(camerainfo[j]) = pCameraArray[i].szCameraUuid;
                    Log::instance().p(YLOG_INFO, "匹配监控点：%s,uuid:%s", pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
                }                    
            }
            Log::instance().p(YLOG_INFO, "序号：%d监控点：%s,uuid:%s",i, pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
        }    */   
        ++iPage;
    }
    delete[] pCameraArray;
    return true;
}

void VideoCaptrue::PreviewScrennshot()
{
    volatile int curindex = 0;
    QString path;
    ISMS_STREAM_TYPE_EN enStreamType = TYPE_MAIN_STREAM;
    auto CB_StreamCallback = [](long lPlayHnadle, ISMS_STREAM_DATA_TYPE_EN enStreamDataType, const char* pDataArray, int iDataLen, void* pUserData) -> void __stdcall {
    
    };
    std::string  imagename;
    _mtx.lock();
    if (testthreadflg)
    {
        if (curScreenshotIndex >= 2000)
            curScreenshotIndex = 0;
        curindex = curScreenshotIndex%cameraNodeList.size();

        imagename = "test\\example" + std::to_string(curScreenshotIndex) + ".jpg";
        path = m_SnapFolder + "\\" + imagename.c_str();
    }
    else
    {
        if (curScreenshotIndex >= cameraNodeList.size())
            curScreenshotIndex = 0;
        curindex = curScreenshotIndex;
        imagename = std::to_string(curindex + 1) + "\\example.jpg";
        path = m_SnapFolder + "\\" + imagename.c_str();
    }
    curScreenshotIndex++;
    //if (std::get<5>(cameraNodeList[curindex]) >= TRY_CAPTURE_CNT)
    //    std::get<5>(cameraNodeList[curindex]) = 0;
    //std::get<5>(cameraNodeList[curindex])++;
    _mtx.unlock();
    uint64_t starttime = ot();
    bool bEnpireCapture = false;
    if (cameraNodeList[curindex].frequency == -1)
        bEnpireCapture = true;
    else
        bEnpireCapture = ((starttime - cameraNodeList[curindex].timestamp) >= cameraNodeList[curindex].cnt * 1000);

    if (curindex >= cameraNodeList.size() || cameraNodeList[curindex].uuid.isEmpty() || !bEnpireCapture)
    {        
        return;
    }
    //std::get<4>(cameraNodeList[curindex]) = ot();
    //Log::instance().p(YLOG_ERROR, "cameraindex:%d,调用线程ID为：%d,已到期可抓图uuid:%s", curindex, QThread::currentThread(), uuid.toStdString().c_str());
    //return;
    if (!threadrun)
        return;
    cameraNodeList[curindex].handle = ISMS_StartPreview(cameraNodeList[curindex].uuid.toStdString().c_str(), nullptr, enStreamType, CB_StreamCallback, NULL);
    bool bSuc = cameraNodeList[curindex].handle > ISMS_ERR_FAIL;
    if (!bSuc)
    {
        int errorcode = ISMS_GetLastError();
        if (errorcode>=100 && errorcode<=110)
        {
            loginMutex.lock();
            if (loginstatus < 3)
            {
                Logininit();
            }
            loginMutex.unlock();
        }
        //if(threadrun && std::get<5>(cameraNodeList[curindex]) == TRY_CAPTURE_CNT)
        Log::instance().p(YLOG_ERROR, "当前线程%d，预览失败 序号:%d uuid:%s 错误码：%d", QThread::currentThread(), curindex, cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());
        return;
    }
    //Log::instance().p(YLOG_ERROR, "当前线程%d，预览成功 预览句柄:%d 序号:%d uuid:%s 错误码：%d", QThread::currentThread(), cameraNodeList[curindex].handle, curindex, cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());

    int iRet = -1;
    int sleepnum = 0;
    bool captureres = false;
    while (iRet == -1)
    {
        if (!threadrun)
            return;
        std::string  imgpath = m_SnapFolder.toStdString()+"\\"+ std::to_string(curindex + 1) + "_example.jpg";
        QFile::remove(imgpath.c_str());
        iRet = ISMS_PreviewSnapshot(cameraNodeList[curindex].handle, imgpath.c_str());
        if (iRet != -1){
            captureres = true;
            //Log::instance().p(YLOG_ERROR, "当前线程%d，预览句柄：%d,序号:%d,path:%s,uuid:%s，抓图成功 ", QThread::currentThread(), (cameraNodeList[curindex]).handle,(curindex+1),imgpath.c_str(), cameraNodeList[curindex].uuid.toStdString().c_str());
            break;
        }
        if (sleepnum < 200)
        {
            sleepnum++;
            Sleep(10);
        }
        else
        {
            //if (std::get<5>(cameraNodeList[curindex]) == TRY_CAPTURE_CNT)
            Log::instance().p(YLOG_ERROR, "当前线程%d，预览句柄：%d,序号:%d，uuid:%s，抓图失败 错误码：%d", QThread::currentThread(), curindex, cameraNodeList[curindex].handle, cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());
            break;
        }
        if (!threadrun)
            return;
    }
    if (captureres && !testthreadflg)
    {
        QString str = QString("/num=%1").arg(curindex+1);
        std::string stdstr = str.toStdString();
        loginMutex.lock();
        (cameraNodeList[curindex]).timestamp = ot();
        int index = (cameraNodeList[curindex]).tcpvalue;
        if (index < SOCKET_SIZE)
        {
            int iret = s_http->getData(socketd[index].socked, stdstr, " ");
            if (iret < 0)
            {
                //if (threadrun && std::get<5>(cameraNodeList[curindex]) == TRY_CAPTURE_CNT)
                 Log::instance().p(YLOG_ERROR, "tcp消息发送失败,线程id:%d，错误码：%d,index:%d,port:%d, ", QThread::currentThread(), iret, index, socketd[index].port);
                closesocket(socketd[index].socked);
                s_http->socketInit("127.0.0.1",index, socketd[index]);
                s_http->getData(socketd[index].socked, stdstr, " ");
            }
        }
        loginMutex.unlock();
    }
    iRet = ISMS_StopPreview(cameraNodeList[curindex].handle);
    int64_t endtime = ot();
    if (captureres&& testthreadflg) // 
    {
        capturemtx.lock();
        capturenum++;
        capturemtx.unlock();
        Log::instance().p(YLOG_INFO, "抓图成功,预览句柄：%d,当前进程id:%d,uuid:%s,图片id:%d ,花费时间：%dms", (cameraNodeList[curindex]).handle, QThread::currentThread(), (cameraNodeList[curindex]).uuid.toStdString().c_str(), (curindex + 1), (endtime - starttime));

    }
}

//线程真正执行的内容
void VideoCaptrue::run()
{
    while (threadrun)
    {
        //qDebug() << "VideoCaptrue run 被调用，调用线程ID为：" << QThread::currentThread();
        PreviewScrennshot();
        Sleep(10);
    }
}

void VideoCaptrue::stopScreenshot()
{
    threadrun = false;    
    int threadnum = Setting::getInstance()->getSetting()->value("basic/threadnum").toInt();
    int runtime = Setting::getInstance()->getSetting()->value("basic/runtime").toInt();
    int time = 0;
    if (capturenum > 0 && runtime > 0)
    {
        time = runtime * 1000 / capturenum;
        Log::instance().p(YLOG_INFO, "抓图结束，抓图用时%d秒，使用线程数量:%d,抓图个数：%d,一张图平均用时:%d毫秒", runtime, threadnum, capturenum, time);
    }
    for (auto const sock:socketd)
    {
        closesocket(sock.socked);
    }
}

void VideoCaptrue::Logindestroy()
{
    if(loginstatus >=3)
        ISMS_Logout();
    if (loginstatus >= 2)
        ISMS_Fini();
    loginstatus = 0;
}