#include "cutvideoserivce.h"
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include "VideoCaptrue.h"
#include <windows.h>
#include "main.h"
cutvideoserivce::cutvideoserivce(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(":/cutvideoserivce/res/arguse2.png"),this);
    trayIcon->setToolTip(QStringLiteral("��ͼ��������"));
    QAction* exit = new QAction(QStringLiteral("�˳�"),
        trayIcon);
    connect(exit, &QAction::triggered, [this] {
        close();
        exitCutvideoService();
    });

    QMenu *trayMenu = new QMenu();
    trayMenu->addAction(exit);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}
