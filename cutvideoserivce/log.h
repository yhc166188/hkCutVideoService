#pragma once
//����printf�ȷǰ�ȫ��������
#pragma warning(disable:4996)
#include <windows.h>
#include <string>
#include <sys/stat.h>
#include <assert.h>

#define YFL __FILE__,__LINE__
#define YLOG_MAXBUF 1024
#define YLOG_SLEEP 4

typedef enum YLOG_LEVELenum {
    //any info
    YLOG_TRACE,
    //useful info
    YLOG_INFO,
    YLOG_WARNING,
    YLOG_ERROR,
    YLOG_FATAL,
    //none info
    YLOG_RELEASE,//only for #define YLOGLEVELn,can not log out
    YLOG_MIN = 0,
}YLOG_LEVEL;

typedef enum YLOG_TYPEenum {
    YLOG_ADD,
    YLOG_OVER
}YLOG_TYPE;

class Log {
public:
    static Log& instance();
    void p(const int level, const char* format, ...);
    void initLog(const int type, const int level, std::string logname = "");
    ~Log();
    Log();
private:

private:
    char path[MAX_PATH];
    FILE*file;
    int level;
};
