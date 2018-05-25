#include "cutvideoserivce.h"
#include <QtWidgets/QApplication>
#include "VideoCaptrue.h"
#include <windows.h>
#include <QThreadPool>
#include <QLabel>
#include "log.h"
#include "settingconfig.h"
#include <QTimer>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QPointer>
void SystemTrayInit()
{

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cutvideoserivce w; 
    //w.show();
    Setting::getInstance();
    QString CurPath = QCoreApplication::applicationDirPath();
    Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() +"\\cutvideoservice.log");
    VideoCaptrue::Logininit();
    VideoCaptrue::CameraInit();
    //设置线程池
    int threadnum = Setting::getInstance()->getSetting()->value("threadnum").toInt();
    if (threadnum <= 0)
    {
        Log::instance().p(YLOG_ERROR, "获取线程值异常,threadnum:%d", threadnum);
    }else
        Log::instance().p(YLOG_INFO, "当前启用线程池数量:%d", threadnum);
    QThreadPool pool;
    int runtime = Setting::getInstance()->getSetting()->value("runtime").toInt();
    if(runtime > 0)
    QTimer::singleShot(runtime, []
    {
        VideoCaptrue::stopScreenshot();
        exit(0);
    }
    );
    pool.setMaxThreadCount(threadnum);
    for (int i = 0; i < threadnum; i++)
    {
        pool.start(new VideoCaptrue());
    }

    return a.exec();
}
