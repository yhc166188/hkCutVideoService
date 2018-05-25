#include "cutvideoserivce.h"
#include <QtWidgets/QApplication>
#include "VideoCaptrue.h"
#include <windows.h>
#include <QThreadPool>
#include <QLabel>
#include "log.h"
#include "settingconfig.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cutvideoserivce w; 
    //w.show();
    Setting::getInstance();
    QString CurPath = QCoreApplication::applicationDirPath();
    Log::instance().initLog(YLOG_OVER, YLOG_INFO, CurPath.toStdString() +"\\cutvideoservice.log");
    VideoCaptrue::Logininit();
    VideoCaptrue::CamerainfoInit();
    int runtime = Setting::getInstance()->getSetting()->value("basic/runtime").toInt();
    if (runtime > 0)
        QTimer::singleShot(runtime*1000, [=] {
        VideoCaptrue::stopScreenshot();
        exit(0);
    }
    );
    //�����̳߳�
    int threadnum = Setting::getInstance()->getSetting()->value("basic/threadnum").toInt();
    if (threadnum <= 0)
    {
        Log::instance().p(YLOG_ERROR, "��ȡ�߳�ֵ�쳣,threadnum:%d", threadnum);
    }else
        Log::instance().p(YLOG_INFO, "��ǰ�����̳߳�����:%d", threadnum);
    QThreadPool pool;
    pool.setMaxThreadCount(threadnum);
    for (int i = 0; i < threadnum; i++)
    {
        pool.start(new VideoCaptrue());
    }

    return a.exec();
}
