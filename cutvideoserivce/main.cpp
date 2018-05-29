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
std::unique_ptr<QThreadPool> pthreadpool;
static QString deleteExceedWeekFile(QString filepath, QString filesuffix)
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
    int delcnt = fileCount - 7;
    if (delcnt <= 0)
        return QNewfile;
    for (int i = 7; i < fileCount; i++)  /*����ÿ���ļ�*/
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
        VideoCaptrue::stopScreenshot();
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
    QApplication a(argc, argv);
    cutvideoserivce w; 
    //w.show();

    Setting::getInstance();
    SYSTEMTIME yst;
    ::GetLocalTime(&yst);
    QString CurPath = QCoreApplication::applicationDirPath();
    deleteExceedWeekFile(CurPath + "\\logs\\", "log");
    QString logName = QString("%1-%02-%03 %04-%05.log").arg(yst.wYear).arg(yst.wMonth, 2, 10, QLatin1Char('0')).arg(yst.wDay, 2, 10, QLatin1Char('0')).arg(yst.wHour, 2, 10, QLatin1Char('0')).arg(yst.wMinute, 2, 10, QLatin1Char('0'));
    Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() +"\\logs\\" + logName.toStdString());
    VideoCaptrue::Logininit();
    VideoCaptrue::CamerainfoInit();

    QTimer Timer;
    QObject::connect(&Timer, &QTimer::timeout, [=] {
        SYSTEMTIME yst;
        ::GetLocalTime(&yst);
        //if ( yst.wSecond == 0) //yst.wHour == 0 && yst.wMinute == 0 &&
        {
            VideoCaptrue::stopScreenshot();
            pthreadpool->waitForDone(1000);
            int threadnum = Setting::getInstance()->getSetting()->value("basic/threadnum").toInt();
            QString logName = QString("%1-%02-%03 %04-%05.log").arg(yst.wYear).arg(yst.wMonth, 2, 10, QLatin1Char('0')).arg(yst.wDay, 2, 10, QLatin1Char('0')).arg(yst.wHour, 2, 10, QLatin1Char('0')).arg(yst.wMinute, 2, 10, QLatin1Char('0'));
            Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() + "\\logs\\" + logName.toStdString());
            deleteExceedWeekFile(CurPath + "\\logs\\", "log");
            Setting::getInstance()->resetSetting();
            VideoCaptrue::CamerainfoInit();
            initThreadPool();
        }   
    });
    Timer.start(5*60*1000);
    initThreadPool();
    return a.exec();
}
