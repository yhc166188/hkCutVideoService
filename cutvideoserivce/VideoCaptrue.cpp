#include "VideoCaptrue.h"
#include "ISMSSDK.h"
#include "crash/CrashAPI.h"
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
#define PAGE_SIZE_REQ 400
#define SOCKET_SIZE   4
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
using cameradata = std::tuple<QString,QString,int,int,volatile uint64_t>;
static QList<cameradata> cameraNodeList;
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
    for (int i = 0; i < arraysize; ++i) {
        cameradata  data;
        Setting::getInstance()->getSetting()->setArrayIndex(i);
        std::get<0>(data) = Setting::getInstance()->getSetting()->value("uuid").toString();
        std::get<1>(data) = Setting::getInstance()->getSetting()->value("name").toString();
        std::get<2>(data) = Setting::getInstance()->getSetting()->value("tcpvalue").toInt();
        std::get<3>(data) = Setting::getInstance()->getSetting()->value("frequency").toInt();
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
    for (int i = 0; i < cameraNodeList.size(); i++)
    {
        QString detailpath = m_SnapFolder + "\\" + QString::number(i + 1);
        isDirExist(detailpath);
    }

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
    CrashAPI_Init();
    CrashAPI_SetDumpType(FullDumpType);
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
            Log::instance().p(YLOG_ERROR, "ȫ����ȡ��ص���Ϣ����!��������:%d", ISMS_GetLastError());
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
        for (int i = 0; i < stRsp.iRealRows; ++i)
        {
            int size = camerainfo.size();
            for (int j = 0; j < size; ++j)
            {
                if (std::get<1>(camerainfo[j]) == pCameraArray[i].szCameraName)
                {
                    std::get<0>(camerainfo[j]) = pCameraArray[i].szCameraUuid;
                    Log::instance().p(YLOG_INFO, "ƥ���ص㣺%s,uuid:%s", pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
                }                    
            }
            Log::instance().p(YLOG_INFO, "��ţ�%d��ص㣺%s,uuid:%s",i, pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
        }       
        ++iPage;
    }
    delete[] pCameraArray;
    return true;
}

void VideoCaptrue::PreviewScrennshot()
{
    int curindex = 0;
    QString path;//
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
    _mtx.unlock();
    QString uuid(std::get<0>(cameraNodeList[curindex]));
    uint64_t starttime = ot();
    bool bEnpireCapture = ((starttime - std::get<4>(cameraNodeList[curindex])) >= std::get<4>(cameraNodeList[curindex]) * 1000);
    Log::instance().p(YLOG_ERROR, "cameraindex:%d,�����߳�IDΪ��%d", curindex, QThread::currentThread());
    return;
    if (curindex >= cameraNodeList.size() || uuid.isEmpty() || bEnpireCapture)
    {        
        Log::instance().p(YLOG_ERROR, "cameraindex:%d,�����߳�IDΪ��%d,%d", curindex, QThread::currentThread());
        return;
    }

    long lPlayHandle = ISMS_StartPreview(uuid.toStdString().c_str(), nullptr, enStreamType, CB_StreamCallback, NULL);
    bool bSuc = lPlayHandle > ISMS_ERR_FAIL;
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
        Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ��ʧ�� uuid:%s �����룺%d", QThread::currentThread(), uuid.toStdString().c_str(), ISMS_GetLastError());
        return;
    }
    int iRet = -1;
    int sleepnum = 0;
    bool captureres = false;
    while (iRet == -1)
    {
        QFile::remove(path);
        iRet = ISMS_PreviewSnapshot(lPlayHandle, path.toStdString().c_str());
        if (iRet == -1)
        {
            //Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ�������%d��ץͼʧ�� �����룺%d", lPlayHandle,QThread::currentThread(), ISMS_GetLastError());
        }
        else {
            captureres = true;
            //Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ�������%d��ץͼ�ɹ� ", QThread::currentThread(), lPlayHandle);
            break;
        }
        if (sleepnum < 100)
        {
            sleepnum++;
            Sleep(10);
        }
        else
        {
            break;
        }
    }
    if (captureres && !testthreadflg)
    {
        QString str = QString("/num=%1").arg(curindex+1);
        std::string stdstr = str.toStdString();
        loginMutex.lock();
        std::get<4>(cameraNodeList[curindex]) = ot();
        int index = std::get<2>(cameraNodeList[curindex]);
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
    iRet = ISMS_StopPreview(lPlayHandle);
    int64_t endtime = ot();
    if (captureres && testthreadflg)
    {
        capturemtx.lock();
        capturenum++;
        capturemtx.unlock();
        Log::instance().p(YLOG_INFO, "ץͼ�ɹ�,Ԥ�������%d,��ǰ����id:%d,ͼƬid:%d ,����ʱ�䣺%dms", lPlayHandle, QThread::currentThread(), (curindex + 1), (endtime - starttime));

    }
    bSuc = iRet == ISMS_ERR_NOERROR;
    if (bSuc)
        return;
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
    if (loginstatus >= 1)
        //CrashAPI_Uninit();
    loginstatus = 0;
}