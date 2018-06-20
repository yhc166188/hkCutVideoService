#include "cutvideoserivce.h"
#include <QtWidgets/QApplication>
#include "VideoCaptrue.h"
#include <windows.h>
#include <QThreadPool>
#include <QLabel>
#include "log.h"
#include "settingconfig.h"
#include <QTimer>
#include <QFile>
#include <QDir>
#include <memory>
#include "main.h"
//#include "crash/CrashAPI.h"
std::unique_ptr<QThreadPool> pthreadpool;
#include <stdio.h>
#include <dbghelp.h>
#include <stdlib.h>
#pragma comment(lib, "Dbghelp.lib")
#include <DbgHelp.h>
//����DUMP�ļ�
int GenerateMiniDump(HANDLE hFile, PEXCEPTION_POINTERS pExceptionPointers, PWCHAR pwAppName)
{
    BOOL bOwnDumpFile = FALSE;
    HANDLE hDumpFile = hFile;
    MINIDUMP_EXCEPTION_INFORMATION ExpParam;

    typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
        HANDLE,
        DWORD,
        HANDLE,
        MINIDUMP_TYPE,
        PMINIDUMP_EXCEPTION_INFORMATION,
        PMINIDUMP_USER_STREAM_INFORMATION,
        PMINIDUMP_CALLBACK_INFORMATION
        );

    MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
    HMODULE hDbgHelp = LoadLibrary(L"DbgHelp.dll");
    if (hDbgHelp)
        pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

    if (pfnMiniDumpWriteDump)
    {
        if (hDumpFile == NULL || hDumpFile == INVALID_HANDLE_VALUE)
        {
            TCHAR szFileName[MAX_PATH] = { 0 };
            TCHAR* szVersion = L"v1.0";
            TCHAR dwBufferSize = MAX_PATH;
            SYSTEMTIME stLocalTime;
            GetLocalTime(&stLocalTime);
            CreateDirectory(szFileName, NULL);

            wsprintf(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
                szVersion,
                stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
                stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
                GetCurrentProcessId(), GetCurrentThreadId());
            // szFileName��ȫ·���ļ�������������ָ��dump�ļ��ı���λ��
            hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

            bOwnDumpFile = TRUE;
            OutputDebugString(szFileName);
        }

        if (hDumpFile != INVALID_HANDLE_VALUE)
        {
            ExpParam.ThreadId = GetCurrentThreadId();
            ExpParam.ExceptionPointers = pExceptionPointers;
            ExpParam.ClientPointers = FALSE;

            pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &ExpParam : NULL), NULL, NULL);

            if (bOwnDumpFile)
                CloseHandle(hDumpFile);
        }
    }

    if (hDbgHelp != NULL)
        FreeLibrary(hDbgHelp);

    return EXCEPTION_EXECUTE_HANDLER;
}


LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
    if (IsDebuggerPresent())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    return GenerateMiniDump(NULL, lpExceptionInfo, L"test");
}

void exitCutvideoService()
{
    VideoCaptrue::setThreadRunFlg(false);
    if(pthreadpool.get())
        pthreadpool->waitForDone(2000);
    VideoCaptrue::stopScreenshot();
}
static void deleteTempImageFile(QString filepath, QString filesuffix)
{
    QDir dir(filepath);
    if (!dir.exists())
        return;
    dir.setFilter(QDir::Files); 
    dir.setSorting(QDir::Time);
    QFileInfoList fileList = dir.entryInfoList();  /*��ȡ���ļ����������ļ�����Ϣ*/
    int filesize = fileList.count();
    if (filesize <= 0)
        return;
    for (int i = 0; i < filesize; i++)  /*����ÿ���ļ�*/
    {
        QFileInfo fileInfo = fileList[i];
        QString suffix = fileInfo.suffix(); /*��ȡ�ļ���׺��*/
        if (QString::compare(suffix, filesuffix, Qt::CaseInsensitive) == 0)
        {
            QString QImagefile = fileInfo.absoluteFilePath();/*��ȡ�ļ�����·����ȫ·��*/
            QFile::remove(QImagefile);
        }
    }
    return;
}
static QString deleteExceedWeeklog(QString filepath, QString filesuffix)
{
    QString QNewfile;
    QDir dir(filepath);
    if (!dir.exists())
        return QNewfile;
    dir.setFilter(QDir::Files); /*����dir�Ĺ���ģʽ,��ʾֻ�������ļ����ڵ��ļ�*/
    dir.setSorting(QDir::Time);
    QFileInfoList fileList = dir.entryInfoList();  /*��ȡ���ļ����������ļ�����Ϣ*/
    if (fileList.count() <= 0)
        return QNewfile;
    int fileCount = fileList.count();
    int delcnt = fileCount - 6;
    if (delcnt <= 0)
        return QNewfile;
    for (int i = 6; i < fileCount; i++)  /*����ÿ���ļ�*/
    {
        QFileInfo fileInfo = fileList[i];
        QString suffix = fileInfo.suffix(); /*��ȡ�ļ���׺��*/
        if (QString::compare(suffix, filesuffix, Qt::CaseInsensitive) == 0)
        {
            QNewfile = fileInfo.absoluteFilePath();/*��ȡ�ļ�����·����ȫ·��*/
            QFile::remove(QNewfile);
        }
    }
    return QNewfile;
}
void initThreadPool()
{
    pthreadpool.reset(new QThreadPool);
    //�����̳߳�
    int threadnum = Setting::getInstance()->getSetting()->value("basic/threadnum").toInt();
    if (threadnum <= 0)
    {
        Log::instance().p(YLOG_ERROR, "��ȡ�߳�ֵ�쳣,threadnum:%d", threadnum);
    }
    else
        Log::instance().p(YLOG_INFO, "��ǰ�����̳߳�����:%d", threadnum);

    pthreadpool->setMaxThreadCount(threadnum);
    int runtime = Setting::getInstance()->getSetting()->value("basic/runtime").toInt();
    if (runtime > 0)
        QTimer::singleShot(runtime * 1000, [=] {
        exitCutvideoService();
        exit(0);
    }
    );
    VideoCaptrue::setThreadRunFlg(true);
    for (int i = 0; i < threadnum; i++)
    {
        pthreadpool->start(new VideoCaptrue());
    }
}
int main(int argc, char *argv[])
{
    //dump�ļ����� 
    ::SetUnhandledExceptionFilter(ExceptionFilter);
    //CrashAPI_Init();
    //CrashAPI_SetDumpType(FullDumpType);
    QApplication a(argc, argv);
    cutvideoserivce w; 
    //w.show();
    Setting::getInstance();
    SYSTEMTIME yst;
    ::GetLocalTime(&yst);
    QString CurPath = QCoreApplication::applicationDirPath();
    deleteExceedWeeklog(CurPath + "\\logs\\", "log");
    QString logName = QString("%1-%02-%03 %04-%05.log").arg(yst.wYear).arg(yst.wMonth, 2, 10, QLatin1Char('0')).arg(yst.wDay, 2, 10, QLatin1Char('0')).arg(yst.wHour, 2, 10, QLatin1Char('0')).arg(yst.wMinute, 2, 10, QLatin1Char('0'));
    Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() +"\\logs\\" + logName.toStdString());
    VideoCaptrue::Logininit();
    VideoCaptrue::CameraInit();
    VideoCaptrue::CamerainfoInit();
    
    QTimer Timer;
    QObject::connect(&Timer, &QTimer::timeout, [=] {
        SYSTEMTIME yst;
        ::GetLocalTime(&yst);
        if ((yst.wSecond == 0) &&(yst.wHour == 0) && (yst.wMinute == 0))
        {
            VideoCaptrue::stopScreenshot();
            pthreadpool->waitForDone(1000);
            pthreadpool.reset();
            int threadnum = Setting::getInstance()->getSetting()->value("basic/threadnum").toInt();
            QString logName = QString("%1-%02-%03 %04-%05.log").arg(yst.wYear).arg(yst.wMonth, 2, 10, QLatin1Char('0')).arg(yst.wDay, 2, 10, QLatin1Char('0')).arg(yst.wHour, 2, 10, QLatin1Char('0')).arg(yst.wMinute, 2, 10, QLatin1Char('0'));
            Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() + "\\logs\\" + logName.toStdString());
            deleteExceedWeeklog(CurPath + "\\logs\\", "log");
            Setting::getInstance()->resetSetting();
            VideoCaptrue::Logininit();
            VideoCaptrue::CameraInit();
            VideoCaptrue::CamerainfoInit();           
            initThreadPool();
        }   
    });
    Timer.start(1000);

    QTimer DelTempTimer;
    QObject::connect(&DelTempTimer, &QTimer::timeout, [=] {
        QString path = QDir::tempPath();
        deleteTempImageFile(path, "jpg");
    });
    DelTempTimer.start(3*1000);
    initThreadPool();
    return a.exec();
}
