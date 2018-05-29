#pragma once
#include <QRunnable>
#include <QMutex>
#include <QLabel>
class VideoCaptrue : public QRunnable
{
public:
    VideoCaptrue();
    ~VideoCaptrue();
    static bool CamerainfoInit();
    static bool Logininit();
    static bool CameraInit();
    static void Logindestroy();
    static void setThreadRunFlg(bool state);
    void PreviewScrennshot();
    static void stopScreenshot();
protected:
    void run();
};

