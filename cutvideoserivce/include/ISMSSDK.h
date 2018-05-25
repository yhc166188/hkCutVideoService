#ifdef ISMSSDK_EXPORTS
#define ISMSSDK_API __declspec(dllexport)
#else
#define ISMSSDK_API __declspec(dllimport)
#endif

#ifndef HIK_ISMS_SDK_H
#define HIK_ISMS_SDK_H

#ifndef _IN_
#define _IN_    // 表示入参
#endif

#ifndef _OUT_
#define _OUT_    // 表示出参
#endif

#ifdef __cplusplus
extern "C"{
#endif

#pragma once
#include "ISMSDataDef.h"

/*
*	ISMS_Init
*	接口说明：  SDK初始化
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_Init();

/*
*	ISMS_Fini
*	接口说明：  SDK反初始化
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_Fini();

/*
*	ISMS_Login
*	接口说明：  根据用户名密码登入平台
*	参数说明：
*                      pszIp：平台IP
*                      iPort：平台端口
*                      pszUserName：平台登入用户名
*                      pszPassword：平台登入密码
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_Login(_IN_ const char* pszIp, _IN_ int iPort, _IN_ const char* pszUserName, _IN_ const char* pszPassword);

/*
*	ISMS_Login
*	接口说明：  根据用户名密码登入平台
*	参数说明：
*                      pszIp：平台IP
*                      iPort：平台端口
*                      pszST：st
*                      pszUserUuid：登入平台用户的UUID
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_LoginByST(_IN_ const char* pszIp, _IN_ int iPort, _IN_ const char* pszST, _IN_ const char* pszUserUuid);

/*
*	ISMS_Logout
*	接口说明：  登出平台
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_Logout();

/*
*	ISMS_StartListenEvent
*	接口说明：  开始监听事件
*	参数说明：
*                      pFunc：回调地址
*                      pUserData：用户数据
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StartListenEvent(_IN_ pfnEventCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenEvent
*	接口说明：  取消监听事件
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopListenEvent();

/*
*	ISMS_StartListenDataChange(暂不支持)
*	接口说明：  开始监听数据变更
*	参数说明：
*                      pFunc：回调地址
*                      pUserData：用户数据
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StartListenDataChange(_IN_ pfnDataChangeCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenDataChange(暂不支持)
*	接口说明：  取消监听数据变更
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopListenDataChange();

/*
*	ISMS_StartListenResourceStatus
*	接口说明：  开始监听资源状态变更
*	参数说明：
*                      pFunc：回调地址
*                      pUserData：用户数据
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StartListenResourceStatus(_IN_ pfnResourceStatusCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenResourceStatus
*	接口说明：  取消监听资源状态变更
*	参数说明：
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopListenResourceStatus();

/*
*	ISMS_GetImageDataByUrl
*	接口说明：  根据图片URL从图片服务器下载图片数据，接口内部申请内存
*	参数说明：  
*                      pszURL：图片URL，可来自设备抓图等接口
*                      ppBuffer：保存图片数据缓冲区的地址
*                      piLen：图片数据大小
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetImageDataByUrl(_IN_ const char* pszURL, _OUT_ char** ppBuffer, _OUT_ int* piLen);

/*
*	ISMS_ReleaseImageData
*	接口说明：  释放图片数据内存
*	参数说明：  
*                      pBuffer：保存图片数据缓冲区的地址
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ReleaseImageData(_IN_ char* pBuffer);

/*
*	ISMS_GetImageFile
*	接口说明：  根据图片URL从图片服务器下载图片
*	参数说明：  
*                      pszURL：图片URL，可来自设备抓图等接口
*                      pszPathFile：保存文件名称，如"C://Snap//test.jpg"
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetImageFile(_IN_ const char* pszURL, _IN_ const char* pszPathFile);

/*
*	ISMS_GetCtrlUnitInfo
*	接口说明：  分页获取控制中心，支持全量与增量两种方式
*	参数说明：  
*                      pstPageReq：分页请求
*                      pstPageRsp：分页请求响应
*                      pstCtrlUnit：控制中心信息
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetCtrlUnitInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_CTRLUNIT pstCtrlUnit);

/*
*	ISMS_GetRegionInfo
*	接口说明：  分页获取区域，支持全量与增量两种方式
*	参数说明：
*                      pstPageReq：分页请求
*                      pstPageRsp：分页请求响应
*                      pstRegion：区域信息
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetRegionInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_REGION pstRegion);

/*
*	ISMS_GetVideoDeviceInfo
*	接口说明：  分页获取设备信息，支持全量与增量两种方式
*	参数说明：
*                      pstPageReq：分页请求
*                      pstPageRsp：分页请求响应
*                      pstDevice：设备信息
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetVideoDeviceInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_DEVICE pstDevice);

/*
*	ISMS_GetCameraInfo
*	接口说明：  分页获取监控点信息，支持全量与增量两种方式
*	参数说明：
*                      pstPageReq：分页请求
*                      pstPageRsp：分页请求响应
*                      pstCamera：监控点信息
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetCameraInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_CAMERA pstCamera);

/*
*	ISMS_StartPreview
*	接口说明：  开始预览
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      hWnd：WINDOWS窗口句柄，如果为NULL，只通过pfnStream只推流
*                      enType：主子码流类型
*                      pfnStream：码流回调地址，如果不为NULL，则通过该回调推流
*                      pUserData：用户数据
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_StartPreview(_IN_ const char* pszCameraUuid, _IN_ void* hWnd, _IN_ ISMS_STREAM_TYPE_EN enType, _IN_ pfnStreamCallback  pfnStream = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_StopPreview
*	接口说明：  停止视频预览
*	参数说明：  
*                      lPlayHandle：视频预览句柄，来自ISMS_StartPreview（ISMS_StartPreviewEx）返回值
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopPreview(_IN_ long lPlayHandle);

/*
*	ISMS_PreviewSnapshot
*	接口说明：  预览抓图
*	参数说明：  
*                      lPlayHandle：视频预览句柄，来自ISMS_StartPreview（ISMS_StartPreviewEx）返回值
*                      pszSaveFilePath：保存文件名称，支持jpg和bmp，如"C:\\Snap\\test.jpg"
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_PreviewSnapshot(_IN_ long lPlayHandle, _IN_ const char* pszSaveFilePath);

/*
*	ISMS_DeviceSnapshotAsData
*	接口说明：  设备抓图，返回图片字节流
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      enImageSize：抓图尺寸
*                      enImageQuality：抓图质量
*                      ppBuffer：图片数据缓冲区地址，接口内部申请内存
*                      piSize：图片缓冲区大小
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_DeviceSnapshotAsData(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_SIZE_EN enSize, _IN_ ISMS_IMAGE_QUALITY_EN enQuality, _OUT_ char** ppBuffer, _OUT_ int* piSize);

/*
*	ISMS_ReleaseDeviceSnapshotData
*	接口说明：  释放图片数据内存
*	参数说明：  
*                      pBuffer：保存图片数据缓冲区的地址
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ReleaseDeviceSnapshotData(_IN_ char* pBuffer);

/*
*	int ISMS_DeviceSnapshotAsUrl
*	接口说明：  设备抓图，返回图片在图片服务器上的URL
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      enSize：抓图尺寸
*                      enQuality：抓图质量
*                      pszUrlBuffer：图片URL缓冲区地址
*                      uiBufferSize：图片URL缓冲区大小，建议512字节
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_DeviceSnapshotAsUrl(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_SIZE_EN enSize, _IN_ ISMS_IMAGE_QUALITY_EN enQuality, _OUT_ char* pszUrlBuffer, _IN_ unsigned int uiBufferSize);

/*
*	ISMS_StartManualRecord
*	接口说明：  手动录像
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      enRecordLocationType：录像存储位置
*                      iRecordSeconds：录像持续时间，单位：秒
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StartManualRecord(_IN_ const char* pszCameraUuid, _IN_ ISMS_RECORD_LOCATION_EN enRecordLocationType, _IN_ int iRecordSeconds);

/*
*	ISMS_QueryRecordPlan
*	接口说明：  查询录像计划
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      ppstRecPlanInfo：录像计划链表指针地址
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_QueryRecordPlan(_IN_ const char* pszCameraUuid, _OUT_ PISMS_RECORD_PLAN* ppstRecPlanInfo);

/*
*	ISMS_ReleaseRecordPlan
*	接口说明：  释放录像计划内存
*	参数说明：  
*                      pstRecordPlan：录像计划链表表头指针
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ReleaseRecordPlan(_IN_ PISMS_RECORD_PLAN pstRecordPlan);

/*
*	int ISMS_QueryRecord
*	接口说明：  查询录像
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      enRecordType：录像类型，取值详见ISMS_RECORD_TYPE_EN，多种类型使用“|”连接
*                      enLocation：录像存储位置
*                      iBeginTime：查询开始时间戳，单位：秒
*                      iEndTime：查询结束时间戳，单位：秒
*                      ppstRecordSection：录像片段链表头指针地址，传NULL则不返回录像片段
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_QueryRecord(_IN_ const char* pszCameraUuid, _IN_ int iRecordType, _IN_ ISMS_RECORD_LOCATION_EN enLocation, _IN_ __int64 iBeginTime, _IN_ __int64 iEndTime, _OUT_ PISMS_RECORD_SECTION* ppstRecordSection);

/*
*	ISMS_ReleaseRecord
*	接口说明：  释放录像片段内存
*	参数说明：  
*                      pstRecordSection：录像片段链表表头指针
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ReleaseRecordSection(_IN_ PISMS_RECORD_SECTION pstRecordSection);

/*
*	ISMS_CloseQueryRecord
*	接口说明：  释放录像查询句柄
*	参数说明：  
*                      lQueryHandle：录像查询句柄
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_CloseQueryRecord(_IN_ long lQueryHandle);

/*
*	int ISMS_StartPlayback
*	接口说明：  开始回放
*	参数说明：
*                      lQueryHandle：录像查询句柄，来自于ISMS_QueryRecord返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pFun只推流
*                      pFunc：码流回调地址，如果不为NULL，则通过该回调推流
*                      pUserData：用户数据
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_StartPlayback(_IN_ long lQueryHandle, _IN_ void* hWnd, _IN_ pfnStreamCallback pFunc = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_StopPlayback
*	接口说明：  停止录像回放
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopPlayback(_IN_ long lPlayHandle);

/*
*	ISMS_SetPlaybackSpeed
*	接口说明：  设置回放速度
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*                      iSpeed：速度值，取值：16、8、4、2、1、-2、-4、-8、-16
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_SetPlaybackSpeed(_IN_ long lPlayHandle, _IN_ int iSpeed);

/*
*	ISMS_PausePlayback
*	接口说明：  暂停录像回放
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_PausePlayback(_IN_ long lPlayHandle);

/*
*	ISMS_ResumePlayback
*	接口说明：  恢复录像回放
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ResumePlayback(_IN_ long lPlayHandle);

/*
*	ISMS_SeekPlayback
*	接口说明：  定位录像回放，支持海康系列设备
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*                      iSeeckTime：定位播放时间戳，单位：秒
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_SeekPlayback(_IN_ long lPlayHandle, _IN_ __int64 iSeeckTime);

/*
*	ISMS_PlaybackSnapshot
*	接口说明：  回放抓图
*	参数说明：  
*                      lPlayHandle：录像回放句柄，来自ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*                      pszSaveFilePath：保存文件名称，支持jpg和bmp，如"C:\\Snap\\test.jpg"
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_PlaybackSnapshot(_IN_ long lPlayHandle, _IN_ const char* pszSaveFilePath);

/*
*	ISMS_StartDownloadRecord
*	接口说明：  开始录像下载
*	参数说明：
*                      lQueryHandle：录像查询句柄，来自于ISMS_QueryRecord返回值
*                      pszSaveFilePath：录像文件绝对路径名称，目前只支持mp4格式，如“C:\Record\test.mp4”
*                      uiMaxFileSize：最大分包大小，单位：字节
*                      pfnGetPercent：下载进度回调地址
*                      pUserData：用户数据
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_StartDownloadRecord(_IN_ long lQueryHandle, _IN_ const char* pszSaveFilePath, _IN_ unsigned __int64 uiMaxFileSize, _IN_ pfnProgressCallback pfnGetPercent, _IN_ void* pUserData);

/*
*	ISMS_StopDownloadRecord
*	接口说明： 停止录像下载
*	参数说明：  
*                      lDownloadHandle：录像下载句柄，来自于ISMS_StartDownloadRecord返回值
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopDownloadRecord(_IN_ long lDownloadHandle);

/*
*	ISMS_StartDeviceTalk
*	接口说明：  设备对讲，支持模拟、数字通道对讲，同一时刻只能一个设备一路对讲
*	参数说明：
*                      pszDeviceUuid：设备Uuid
*                      iTalkChannelId：对讲通道号
*                      enDevTalkType：对讲类型，标识是数字通道对讲还是模拟通道对讲
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StartDeviceTalk(_IN_ const char* pszDeviceUuid, _IN_ int iTalkChannelId, _IN_ ISMS_TALK_TYPE_EN enDevTalkType);

/*
*	ISMS_StopDeviceTalk
*	接口说明： 停止设备对讲
*	参数说明：  
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_StopDeviceTalk();

/*
*	ISMS_PtzControl
*	接口说明：  云台控制，支持八个方向转动、自动扫描、光圈调节、焦点调节、镜头拉近拉远、调用预置点、电子放大以及云台锁定相关功能
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      iPtzCommand：云台控制命令，详见ISMS_PTZ_*
*                      iAction：云台控制启动或停止，详见ISMS_PTZ_ACTION_*
*                      iSpeed：云台控制速度，当iPtzCommand为八个方向转动、自动扫描、光圈调节、焦点调节以及镜头拉近拉远时有效
*                      iParam：云台控制参数，当iPtzCommand为ISMS_PTZ_GOTO_PRESET时为预置点id，当iPtzCommand为ISMS_PTZ_LOCK时为锁定时间（单位：秒），当
*                                    iPtzCommand为为其它值时无效
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_PtzControl(_IN_ const char* pszCameraUuid, _IN_ int iPtzCommand, _IN_ int iAction, _IN_ int iSpeed, _IN_ int iParam);

/*
*	ISMS_GetPresetByCamera
*	接口说明：  获取预置点
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      pstPerset：预置点链表头指针地址
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetPresetByCamera(_IN_ const char* pszCameraUuid, _OUT_ PISMS_PRESET_INFO* pstPerset);

/*
*	ISMS_ReleasePresetInfo
*	接口说明： 释放预置点内存
*	参数说明：  
*                      pstPerset：预支点链表头指针
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ReleasePresetInfo(_IN_ PISMS_PRESET_INFO pstPerset);

/*
*	ISMS_SetPreset
*	接口说明：  设置预置点
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      iPersetId：预置点id
*                      pszPersetName：预置点名称
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_SetPreset(_IN_ const char* pszCameraUuid, _IN_ int iPersetId, _IN_ const char* pszPersetName);

/*
*	ISMS_ClearPreset
*	接口说明：  清楚预置点
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      iPersetId：预置点id
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_ClearPreset(_IN_ const char* pszCameraUuid, _IN_ int iPersetId);

/*
*	ISMS_GetPlaybackTime
*	接口说明：  获取当前回放时间（仅支持海康设备）
*	参数说明：  
*                      lPlayHandle：回放句柄，来自于ISMS_StartPlayback（ISMS_StartPlaybackEx）返回值
*                      piPlayTime：出参，当前回放时间戳
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetPlaybackTime(_IN_ long lPlayHandle, _OUT_ __int64* piPlayTime);

/*
*	ISMS_GetVideoImageParam
*	接口说明：  获取视频图像参数
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      pstImageParam：出参，视频图像参数指针
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetVideoImageParam(_IN_ const char* pszCameraUuid, _OUT_ ISMS_IMAGE_PARAM* pstImageParam);

/*
*	ISMS_SetVideoImageParam
*	接口说明：  获取视频图像参数
*	参数说明：  
*                      pszCameraUuid：监控点Uuid
*                      pstImageParam：视频图像参数指针
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_SetVideoImageParam(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_PARAM* pstImageParam);

/*
*	ISMS_OpenSound
*	接口说明：  打开预览或回放声音
*	参数说明：  
*                      播放句柄，来自于ISMS_StartPreview（ISMS_StartPreviewEx）或ISMS_StartPlayback（ISMS_StartPlaybackEx）的返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话
*                      enType : 播放类型，详见ISMS_PLAY_TYPE_EN
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_OpenSound(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_CloseSound
*	接口说明：  关闭预览或回放声音
*	参数说明：  
*                      播放句柄，来自于ISMS_StartPreview（ISMS_StartPreviewEx）或ISMS_StartPlayback（ISMS_StartPlaybackEx）的返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话
*                      enType : 播放类型，详见ISMS_PLAY_TYPE_EN
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_CloseSound(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetVolume
*	接口说明：  获取预览或回放时音量，音量取值[0 100]
*	参数说明：  
*                      播放句柄，来自于ISMS_StartPreview（ISMS_StartPreviewEx）或ISMS_StartPlayback（ISMS_StartPlaybackEx）的返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话
*                      enType : 播放类型，详见ISMS_PLAY_TYPE_EN
*	返回值：      -1表示失败，其它表示音量值，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetVolume(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_SetVolume
*	接口说明：  设置预览或回放时音量
*	参数说明：  
*                      播放句柄，来自于ISMS_StartPreview（ISMS_StartPreviewEx）或ISMS_StartPlayback（ISMS_StartPlaybackEx）的返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话
*                      iVolume : 音量值，取值范围：[0 100]
*                      enType : 播放类型，详见ISMS_PLAY_TYPE_EN
*	返回值：      -1表示失败，其它表示音量值，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_SetVolume(_IN_ long lPlayHandle, _IN_ int iVolume, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetVideoDeviceInfoByUuid
*	接口说明：  根据中心Uuid获取中心信息
*	参数说明：  
*                      pszDevUuid：视频编码设备UUID
*                      pstDevice : 视频编码设备信息指针
*	返回值：      -1表示失败，其它表示音量值，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetVideoDeviceInfoByUuid(_IN_ const char* pszDevUuid, _OUT_ PISMS_DEVICE pstDevice);

/*
*	ISMS_GetCameraInfoByUuid
*	接口说明：  根据中心Uuid获取中心信息
*	参数说明：  
*                      pszCameraUuid：监控点UUID
*                      pstCamera : 监控点信息指针
*	返回值：      -1表示失败，其它表示音量值，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetCameraInfoByUuid(_IN_ const char* pszCameraUuid, _OUT_ PISMS_CAMERA pstCamera);

/*
*	ISMS_GetStreamTraceType
*	接口说明：  获取取流路径
*	参数说明：  lPlayHandle：播放句柄，来自ISMS_StartPreview的返回值
*	返回值：      详见ISMS_STRAM_TRACE_TYPE，当返回值是TYPE_TRACE_ERROR时为失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API ISMS_STRAM_TRACE_TYPE_EN ISMS_GetStreamTraceType(_IN_ const char* pszCameraUuid);

/*
*	ISMS_GetVideoDetailInfo
*	接口说明：  获取如画面分辨率、帧率等视频详细信息
*	参数说明：  lPlayHandle：播放句柄，来自ISMS_StartPreview的返回值
*               pstDetail：视频详细信息指针
*           	enType：播放类型，有预览和回放
*	返回值：      0 调用成功, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API int ISMS_GetVideoDetailInfo(_IN_ long lPlayHandle, _OUT_ PISMS_VIDEO_DETAIL_INFO pstDetail, ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetStreamTypeISMS_STRAM_TRACE_TYPE
*	接口说明：  获取当前预览主子码流类型
*	参数说明：  lPlayHandle：播放句柄，来自ISMS_StartPreview的返回值
*	返回值：      详见ISMS_STREAM_TYPE_EN，当返回值是TYPE_ERROR_STREAM时为失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API ISMS_STREAM_TYPE_EN ISMS_GetStreamType(_IN_ long lPlayHandle);

/*
*	ISMS_StartPreviewEx
*	接口说明：  开始预览，支持消息回调，转封装码流回调，解码后YUV数据回调
*	参数说明：
*                      pszCameraUuid：监控点Uuid
*                      hWnd：WINDOWS窗口句柄，如果为NULL，可通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话）
*                      enStreamType：主子码流类型
*                      fnTranformedStream：推送经转码后的码流数据（暂不支持，该回调后续可能会修改，请传NULL）
*                      fnPlayMsg：消息回调，详见ISMS_PLAY_MSG_EN
*                      fnDecodedStream：解码后的视频数据回调（YUV数据）
*                      pUserData：用户数据
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_StartPreviewEx(_IN_ const char* pszCameraUuid, _IN_ void* hWnd, _IN_ ISMS_STREAM_TYPE_EN enType, _IN_ pfnStreamCallback fnTranformedStream = NULL, _IN_ pfnPlayMsgCallback fnPlayMsg = NULL, _IN_ pfnDecodedDataCallback fnDecodedStream = NULL, _IN_ void* pUserData = NULL);

/*
*	int ISMS_StartPlaybackEx
*	接口说明：  开始回放，支持消息回调，转封装码流回调，解码后YUV数据回调
*	参数说明：
*                      lQueryHandle：录像查询句柄，来自于ISMS_QueryRecord返回值
*                      hWnd：WINDOWS窗口句柄，如果传NULL，则通过pfnTranformedStream或fnDecodedStream推流（如果二者有不为NULL的话）
*                      fnTranformedStream：推送经转码后的码流数据（暂不支持，该回调后续可能会修改，请传NULL）
*                      fnPlayMsg：消息回调，详见ISMS_PLAY_MSG_EN
*                      fnDecodedStream：解码后的视频数据回调（YUV数据）
*                      pUserData：用户数据
*	返回值：      成功返回句柄, -1 调用失败，通过ISMS_GetLastError()查看错误码
*/
ISMSSDK_API long ISMS_StartPlaybackEx(_IN_ long lQueryHandle, _IN_ void* hWnd, _IN_ pfnStreamCallback fnTranformedStream = NULL, _IN_ pfnPlayMsgCallback fnPlayMsg = NULL, _IN_ pfnDecodedDataCallback fnDecodedStream = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_GetVersion
*	接口说明：  获取SDK版本号
*	参数说明：  
*	返回值：      错误码
*/
ISMSSDK_API const char* ISMS_GetVersion();

/*
*	ISMS_GetLastError
*	接口说明：  获取错误码
*	参数说明：  
*	返回值：      错误码
*/
ISMSSDK_API int ISMS_GetLastError();

#ifdef __cplusplus
}
#endif
#endif