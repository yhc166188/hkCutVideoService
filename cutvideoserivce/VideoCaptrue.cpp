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
        bool ok = dir.mkpath(fullPath);//�����༶Ŀ¼
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
static QList<std::tuple<QString, QString>> camerainfo({  //��ص���uuid ,����
std::make_tuple("",u8"��С��������"),
std::make_tuple("",u8"������ζ��ͨ��"),
std::make_tuple("",u8"�������ǰͣ����"),
std::make_tuple("", u8"��������������"),
std::make_tuple("", u8"���ϵ»�����"),
std::make_tuple("", u8"���в������"),
std::make_tuple("", u8"�����������ſ�"),
std::make_tuple("", u8"����ʽ�����"),
std::make_tuple("", u8"����ʽ�����(������)"),
std::make_tuple("", u8"�ϲ���ͨ��"),
std::make_tuple("", u8"�ϳ������㳡"),
std::make_tuple("", u8"�Ͻ��ڻ����㳡"),
std::make_tuple("", u8"�Ͽϵ»�����"),
std::make_tuple("", u8"���������ſ�"),
std::make_tuple("", u8"���������ǰͣ����"),
std::make_tuple("", u8"��С��������"),
std::make_tuple("", u8"���ǰͿ˴���"),
std::make_tuple("", u8"���в���"),
std::make_tuple("", u8"������ͨ��"),
std::make_tuple("", u8"��Ա��ͨ��"),
std::make_tuple("", u8"���ǰͿ˶�������ͨ��"),
std::make_tuple("", u8"��С������"),
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
    Log::instance().p(YLOG_INFO, "��ȡ����ͷ��λ����:%d", arraysize);
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
        Log::instance().p(YLOG_INFO, "���Ա���ͼƬ·��Ϊ��%s", path.toStdString().c_str());
    }
    else
    {
        Log::instance().p(YLOG_INFO, "����ͼƬ·��Ϊ��%s", m_SnapFolder.toStdString().c_str());
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
        Log::instance().p(YLOG_ERROR, "��ʼ��ʧ�� �����룺%d", ISMS_GetLastError());
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
        Log::instance().p(YLOG_ERROR, "��¼ʧ��,ip:%s,port:%d,user:%s,password:%s �����룺%d",strip.c_str(),port,strusername.c_str(),strpassword.c_str(), ISMS_GetLastError());
        return false;
    }
    else
    {
        Log::instance().p(YLOG_INFO, "��¼�ɹ� ,ip:%s,port:%d,user:%s,password:%s", strip.c_str(), port, strusername.c_str(), strpassword.c_str(), ISMS_GetLastError());        
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
        Log::instance().p(YLOG_ERROR, "ISMS_CAMERA �����ڴ�ʧ��");
        return false;
    }
    while (true)
    {
        ISMS_PAGE_REQ stReq;
        ISMS_PAGE_RSP stRsp;
        stReq.iPageNo = iPage;
        stReq.iPageRows = PAGE_SIZE_REQ;
        stReq.iLastUpdateTime = 0;   // ȫ����ȡ��ص�
        int iRet = ISMS_GetCameraInfo(&stReq, &stRsp, pCameraArray);
        if (iRet != ISMS_ERR_NOERROR)
        {
            Log::instance().p(YLOG_ERROR, "��ȡ��ص���Ϣ����!��������:%d", ISMS_GetLastError());
            break;
        }
        if (0 == stRsp.iRealRows)
        {
            break;
        }
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
       for (int i = 0; i < stRsp.iRealRows; ++i)
        {
            //int size = camerainfo.size();
            //for (int j = 0; j < size; ++j)
            //{
            //    if (std::get<1>(camerainfo[j]) == pCameraArray[i].szCameraName)
            //    {
            //        std::get<0>(camerainfo[j]) = pCameraArray[i].szCameraUuid;
            //        Log::instance().p(YLOG_INFO, "ƥ���ص㣺%s,uuid:%s", pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
            //    }                    
            //}
            Log::instance().p(YLOG_INFO, "ƽ̨��ص� ��ţ�%d,���ƣ�%s,uuid:%s",i, pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
        }       
        ++iPage;
    }
    delete[] pCameraArray;
    return true;
}

void VideoCaptrue::PreviewScrennshot()
{
    volatile int curindex = 0;
    ISMS_STREAM_TYPE_EN enStreamType = TYPE_MAIN_STREAM;
    auto CB_StreamCallback = [](long lPlayHnadle, ISMS_STREAM_DATA_TYPE_EN enStreamDataType, const char* pDataArray, int iDataLen, void* pUserData) -> void __stdcall {
    
    };
    std::string  imagename;
    std::string  imgpath;
    _mtx.lock();
    if (testthreadflg)
    {
        if (curScreenshotIndex >= 2000)
            curScreenshotIndex = 0;
        curindex = curScreenshotIndex%cameraNodeList.size();

        imagename = "example" + std::to_string(curScreenshotIndex) + ".jpg";
        imgpath = m_SnapFolder.toStdString() + "\\" + imagename.c_str();
    }
    else
    {
        if (curScreenshotIndex >= cameraNodeList.size())
            curScreenshotIndex = 0;
        curindex = curScreenshotIndex;
        //imagename = std::to_string(curindex + 1) + "\\example.jpg";
        //imgpath = m_SnapFolder + "\\" + imagename.c_str();
        imgpath = m_SnapFolder.toStdString() + "\\" + std::to_string(curindex + 1) + "_example.jpg";
    }
    
    curScreenshotIndex++;
    _mtx.unlock();
    uint64_t starttime = ot();
    bool bEnpireCapture = false;
    if (cameraNodeList[curindex].frequency == -1)
        bEnpireCapture = true;
    else
        bEnpireCapture = ((starttime - cameraNodeList[curindex].timestamp) >= cameraNodeList[curindex].frequency * 1000);

    if (curindex >= cameraNodeList.size() || cameraNodeList[curindex].uuid.isEmpty() || !bEnpireCapture)
    {        
        return;
    }
    //std::get<4>(cameraNodeList[curindex]) = ot();
    //Log::instance().p(YLOG_ERROR, "cameraindex:%d,�����߳�IDΪ��%d,�ѵ��ڿ�ץͼuuid:%s", curindex, QThread::currentThread(), uuid.toStdString().c_str());
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
        Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ��ʧ�� ���:%d uuid:%s �����룺%d", QThread::currentThread(), curindex, cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());
        return;
    }
    //Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ���ɹ� Ԥ�����:%d ���:%d uuid:%s �����룺%d", QThread::currentThread(), cameraNodeList[curindex].handle, curindex, cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());

    int iRet = -1;
    int sleepnum = 0;
    bool captureres = false;
    while (iRet == -1)
    {
        if (!threadrun)
            return;
        QFile::remove(imgpath.c_str());
        iRet = ISMS_PreviewSnapshot(cameraNodeList[curindex].handle, imgpath.c_str());
        if (iRet != -1){
            captureres = true;
            //Log::instance().p(YLOG_INFO, "��ǰ�߳�%d��Ԥ�������%d,���:%d,path:%s,uuid:%s��ץͼ�ɹ� ", QThread::currentThread(), (cameraNodeList[curindex]).handle,(curindex+1),imgpath.c_str(), cameraNodeList[curindex].uuid.toStdString().c_str());
            break;
        }
        if (sleepnum < 200)
        {
            sleepnum++;
            Sleep(10);
        }
        else
        {
            Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ�������%d,���:%d��uuid:%s��ץͼʧ�� �����룺%d", QThread::currentThread(),  cameraNodeList[curindex].handle, (curindex+1), cameraNodeList[curindex].uuid.toStdString().c_str(), ISMS_GetLastError());
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
                 Log::instance().p(YLOG_ERROR, "tcp��Ϣ����ʧ��,�߳�id:%d�������룺%d,index:%d,port:%d, ", QThread::currentThread(), iret, index, socketd[index].port);
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
        Log::instance().p(YLOG_INFO, "ץͼ�ɹ�,Ԥ�������%d,��ǰ����id:%d,uuid:%s,ͼƬid:%d ,����ʱ�䣺%dms", (cameraNodeList[curindex]).handle, QThread::currentThread(), (cameraNodeList[curindex]).uuid.toStdString().c_str(), (curindex + 1), (endtime - starttime));

    }
}

//�߳�����ִ�е�����
void VideoCaptrue::run()
{
    while (threadrun)
    {
        //qDebug() << "VideoCaptrue run �����ã������߳�IDΪ��" << QThread::currentThread();
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
        Log::instance().p(YLOG_INFO, "ץͼ������ץͼ��ʱ%d�룬ʹ���߳�����:%d,ץͼ������%d,һ��ͼƽ����ʱ:%d����", runtime, threadnum, capturenum, time);
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