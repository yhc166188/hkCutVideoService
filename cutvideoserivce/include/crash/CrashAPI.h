/** @file    CrashAPI\CrashAPI\client\windows\handler\CrashAPI.h
 *  @note    HangZhou Hikvision System Technology Co., Ltd. All Right Reserved  
 *  @brief   The CrashAPI library is responsible for monitor an application
             for crashes(exceptions),handing them when they occur by 
             generating a minidump file. 
             This library is based on the open source project google-breakpad.
             You can get the source code in google code to learn more.
 *  @author  yangyanwei
 *  @date    21:3:2013
 *  @note    
 *  @warning 
 */

#ifndef __CRASHAPI_API__
#define __CRASHAPI_API__

#if (defined(_WIN32) || defined(_WIN64))
#  if defined(CRASHAPI_EXPORTS)
#    define CRASH_EXTERN extern "C" __declspec(dllexport)
#  else
#    define CRASH_EXTERN extern "C" __declspec(dllimport)
#  endif
#  define CRASH_API __stdcall
#elif defined(__linux__)
#  define CRASH_EXTERN extern "C"
#  define CRASH_API
#else
#  define CRASH_EXTERN
#  define CRASH_API
#endif

//< CrashAPI定义两种dump类型
//typedef enum _MINIDUMP_TYPE {
//    MiniDumpNormal                         = 0x00000000,
//    MiniDumpWithDataSegs                   = 0x00000001, //进程装载的所有可执行模块的可写数据段
//    MiniDumpWithFullMemory                 = 0x00000002,
//    MiniDumpWithHandleData                 = 0x00000004,
//    MiniDumpFilterMemory                   = 0x00000008, //过滤内存，指定MiniDumpWithFullMemory则无效
//    MiniDumpScanMemory                     = 0x00000010, //和CallBack一起
//    MiniDumpWithUnloadedModules            = 0x00000020,
//    MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
//    MiniDumpFilterModulePaths              = 0x00000080, //过滤模块路径
//    MiniDumpWithProcessThreadData          = 0x00000100,
//    MiniDumpWithPrivateReadWriteMemory     = 0x00000200,
//    MiniDumpWithoutOptionalData            = 0x00000400, //否定义
//    MiniDumpWithFullMemoryInfo             = 0x00000800,
//    MiniDumpWithThreadInfo                 = 0x00001000,
//    MiniDumpWithCodeSegs                   = 0x00002000, //所有进程装载的可执行模块的代码段
//    MiniDumpWithoutAuxiliaryState          = 0x00004000, //否定义
//    MiniDumpWithFullAuxiliaryState         = 0x00008000,
//
//    MiniDumpValidTypeFlags                 = 0x0000ffff,
//} MINIDUMP_TYPE;
enum CRASHAPI_DUMP_TYPE
{
    MiniDumpType = 0x00000000,/*MiniDumpNormal*/
    FullDumpType = 0x00009b67 /*Full*/
};

typedef  void (*CrashCallback)();

#ifdef __cplusplus
extern "C"
{
#endif

    /**************************************************************************
    *   Function:           CrashAPI_Init
    *   Description:        Init the Crash API lib.Call this function  as early
                            in the start-up process as possible.
    *   Input:              (null)
    *   Output:             (null)
    *   Return:             returns true on success.
    **************************************************************************/
    CRASH_EXTERN bool CRASH_API CrashAPI_Init();

    /**************************************************************************
    *   Function:           CrashAPI_Uninit
    *   Description:        uninstall the library
    *   Input:              (null)
    *   Output:             (null)
    *   Return:             none
    **************************************************************************/
    CRASH_EXTERN void CRASH_API CrashAPI_Uninit();

    /**************************************************************************
    *   Function:           CrashAPI_SetDumpPath
    *   Description:        set the minidump file path.the file will be generated
                            in the current dictionary if you don't set it.
    *   Input:              dump_path the path of the  
    *   Output:             (null)
    *   Return:             returns true on success.
    **************************************************************************/
    CRASH_EXTERN bool CRASH_API CrashAPI_SetDumpPath(char * dump_path);

    /**************************************************************************
    *   Function:           CrashAPI_SetDumpType
    *   Description:        set the minidump file type.the file will be MiniDumpNormal
                            if you don't set it.
    *   Input:              dump_type of MINIDUMP_TYPE  
    *   Output:             (null)
    *   Return:             returns true on success.
    **************************************************************************/
    CRASH_EXTERN bool CRASH_API CrashAPI_SetDumpType(CRASHAPI_DUMP_TYPE dump_type);

    /**************************************************************************
    *   Function:           CrashAPI_WriteMinidump
    *   Description:        writes a minidump immediately.it can be used to 
    *                       capture the execution state independently of a crash.
    *   Input:              (null)  
    *   Output:             (null)
    *   Return:             returns true on success.
    **************************************************************************/
    CRASH_EXTERN bool CRASH_API CrashAPI_WriteMinidump();

    /**************************************************************************
    *   Function:           CrashAPI_SetCallBack
    *   Description:        Set the call back function which will be called when 
                            the crash occurs.
    *   Input:              (null)  
    *   Output:             (null)
    *   Return:             returns true on success.
    **************************************************************************/
    CRASH_EXTERN bool CRASH_API CrashAPI_SetCallBack(CrashCallback callback);

#ifdef __cplusplus
}
#endif

#endif
