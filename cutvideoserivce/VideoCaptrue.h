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
    void PreviewScrennshot();
    static void stopScreenshot();
protected:
    void run();
};

