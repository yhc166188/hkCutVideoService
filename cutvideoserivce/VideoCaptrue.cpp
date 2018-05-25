#include "VideoCaptrue.h"
#include "ISMSSDK.h"
#include "crash/CrashAPI.h"
#include <QtCore/QtCore>
#include <QMessageBox>
#include <QList>
#include <QLabel>
#include <tuple>
#include <QFile>
#include <windows.h>
#include <log.h>
#include <chrono>
#include "settingconfig.h"
#include "HttpConnect.h"
#define PAGE_SIZE_REQ 400
QMutex _mtx;
volatile int curScreenshotIndex = 0;
volatile bool threadrun = true;
volatile int capturenum = 0;
volatile int loginstatus = 0; //
QMutex capturemtx;
QMutex loginMutex;
int  socketd[2] = { -1 };
#include <QDir>
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
        //QMessageBox::about(NULL, QStringLiteral("����"), QStringLiteral("��ʼ��ʧ�� ��鿴��־"));
        Log::instance().p(YLOG_ERROR, "��ʼ��ʧ�� �����룺%d", ISMS_GetLastError());
        return false;
    }
    loginstatus = 2;
    std::string strip = Setting::getInstance()->getSetting()->value("ip").toString().toStdString();
    int port = Setting::getInstance()->getSetting()->value("port").toInt();
    std::string strusername = Setting::getInstance()->getSetting()->value("username").toString().toStdString();
    std::string strpassword = Setting::getInstance()->getSetting()->value("password").toString().toStdString();
    reslut = ISMS_Login(strip.c_str(), port, strusername.c_str(), strpassword.c_str());
    if (reslut == -1)
    {
        //QMessageBox::about(NULL, QStringLiteral("����"), QStringLiteral("��¼ʧ�� ��鿴��־"));
        Log::instance().p(YLOG_ERROR, "��¼ʧ��,ip:%s,port:%d,user:%s,password:%s �����룺%d",strip.c_str(),port,strusername.c_str(),strpassword.c_str(), ISMS_GetLastError());
        return false;
    }
    else
    {
        Log::instance().p(YLOG_ERROR, "��¼�ɹ� ,ip:%s,port:%d,user:%s,password:%s", strip.c_str(), port, strusername.c_str(), strpassword.c_str(), ISMS_GetLastError());        
    }
    loginstatus = 3;
    QString picpath = Setting::getInstance()->getSetting()->value("picpath").toString();
    for (int i = 1; i <= camerainfo.size(); i++)
    {
        QString path = picpath + "\\" + QString::number(i);
        isDirExist(path);
    }
    Log::instance().p(YLOG_INFO, "����ͼƬ·��Ϊ��%s", picpath.toStdString().c_str());
    return true;
}
bool VideoCaptrue::CameraInit()
{
    int iPage = 1;
    __int64 i64Time = 0;
    PISMS_CAMERA pCameraArray = new (std::nothrow) ISMS_CAMERA[PAGE_SIZE_REQ];
    if (NULL == pCameraArray)
    {
        QMessageBox::about(NULL, QStringLiteral("����"), QStringLiteral(" ISMS_CAMERA�����ڴ�ʧ��"));
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
            QMessageBox::about(NULL, QStringLiteral("����"), QStringLiteral("ȫ����ȡ��ص���Ϣ����!��������:%1").arg(ISMS_GetLastError()));
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
                    Log::instance().p(YLOG_INFO, "��ص㣺%s,uuid:%s", pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
                }
                    
            }
            Log::instance().p(YLOG_INFO, "��ţ�%d��ص㣺%s,uuid:%s",i, pCameraArray[i].szCameraName, pCameraArray[i].szCameraUuid);
        }       
        ++iPage;
    }
    delete[] pCameraArray;
    if (s_http)
    {
        delete s_http;
    }
    s_http = new CHttpConnect();
    socketd[0] = s_http->socketInit("127.0.0.1",0);
    socketd[1] = s_http->socketInit("127.0.0.1", 1);
    //m_SnapFolder = "E:\\work\\0";
    //m_SnapFolder = m_SnapFolder+ "\\example.jpg";
    //QFile::remove(m_SnapFolder);
    //Log::instance().p(YLOG_INFO, "������־·��Ϊ��%s", m_SnapFolder.toStdString().c_str());
    return true;
}

void VideoCaptrue::PreviewScrennshot()
{
    int curindex = 0;
    QString path = "E:\\work\\0";//
    std::string  imagename;
    _mtx.lock();
    if (curScreenshotIndex >= 2000)
        curScreenshotIndex = 0;
    curindex = curScreenshotIndex;
    curScreenshotIndex++;
    imagename = "example" + std::to_string(curindex) + ".jpg";
    path = path + "\\" + imagename.c_str();
    QFile::remove(path);
    //if (std::get<0>(camerainfo[curindex]).isEmpty())
    //{
    //    Log::instance().p(YLOG_ERROR, "cameraindex:%d,�����߳�IDΪ��%d", curindex,  QThread::currentThread());
    //}
    _mtx.unlock();
    ISMS_STREAM_TYPE_EN enStreamType = TYPE_MAIN_STREAM;
    auto CB_StreamCallback = [](long lPlayHnadle, ISMS_STREAM_DATA_TYPE_EN enStreamDataType, const char* pDataArray, int iDataLen, void* pUserData) -> void __stdcall {
    
    };
    int64_t starttime = ot();
    long lPlayHandle = ISMS_StartPreview("9d36ed060ad047b29b080f7f5ce9cf89", nullptr, enStreamType, CB_StreamCallback, NULL);
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
        Log::instance().p(YLOG_ERROR, "��ǰ�߳�%d��Ԥ��ʧ�� �����룺%d", QThread::currentThread(), ISMS_GetLastError());
        return;
    }
    //__PreviewSnap(CameraUuid[numTime + i].CameraName, PlayHandle[i], SnapFolder, numTime + 1 + i);//ץͼ
    int iRet = -1;
    int sleepnum = 0;
    bool captureres = false;
    while (iRet == -1)
    {
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
    if (captureres)
    {
        QString str = QString("/num=%1").arg(curindex);
        std::string stdstr = str.toStdString();
        //QString str1 = u8"���������ǰͣ����";
        //QString str2 = u8"�������ǰͣ����";
        //QString str3 = u8"�ϳ������㳡";
        //QString str4 = u8"�Ͻ��ڻ����㳡";
        //QString str5 = u8"���������ſ�";
        loginMutex.lock();
        int index = 0;
        if (std::get<1>(camerainfo[curindex]) == std::get<1>(camerainfo[14])
            || std::get<1>(camerainfo[curindex]) == std::get<1>(camerainfo[2])
            || std::get<1>(camerainfo[curindex]) == std::get<1>(camerainfo[10])
            || std::get<1>(camerainfo[curindex]) == std::get<1>(camerainfo[2])
            || std::get<1>(camerainfo[curindex]) == std::get<1>(camerainfo[2]))
        {

            index = 0;
        }
        else 
        {
            index = 1;
        }
        if (s_http)
        {
            int iret = s_http->getData(socketd[index], stdstr, " ");
            if (iret < 0)
            {
                closesocket(socketd[index]);
                socketd[index] = s_http->socketInit("127.0.0.1", 0);
            }
        }
        loginMutex.unlock();
    }
    iRet = ISMS_StopPreview(lPlayHandle);
    int64_t endtime = ot();
    if (captureres)
    {
        capturemtx.lock();
        capturenum++;
        capturemtx.unlock();
        Log::instance().p(YLOG_INFO, "ץͼ�ɹ�,Ԥ�������%d,��ǰ����id:%d ,����ʱ�䣺%dms", lPlayHandle, QThread::currentThread(), (endtime - starttime));

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
        //Sleep(20);
    }
}

void VideoCaptrue::stopScreenshot()
{
    threadrun = false;
    
    int threadnum = Setting::getInstance()->getSetting()->value("threadnum").toInt();
    int runtime = Setting::getInstance()->getSetting()->value("runtime").toInt();
    int time = 0;
    if (capturenum > 0 && runtime > 0)
    {
        time = runtime * 1000 / capturenum;
        Log::instance().p(YLOG_INFO, "ץͼ������ץͼ��ʱ%d�룬ʹ���߳�����:%d,ץͼ������%d,һ��ͼƽ����ʱ:%d����", runtime, threadnum, capturenum, time);
    }
    closesocket(socketd[0]);
    closesocket(socketd[1]);
    Logindestroy();
}

void VideoCaptrue::Logindestroy()
{
    if(loginstatus >=3)
        ISMS_Logout();
    if (loginstatus >= 2)
        ISMS_Fini();
    if (loginstatus >= 1)
        CrashAPI_Uninit();
    loginstatus = 0;
}