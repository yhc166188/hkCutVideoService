#ifdef ISMSSDK_EXPORTS
#define ISMSSDK_API __declspec(dllexport)
#else
#define ISMSSDK_API __declspec(dllimport)
#endif

#ifndef HIK_ISMS_SDK_H
#define HIK_ISMS_SDK_H

#ifndef _IN_
#define _IN_    // ��ʾ���
#endif

#ifndef _OUT_
#define _OUT_    // ��ʾ����
#endif

#ifdef __cplusplus
extern "C"{
#endif

#pragma once
#include "ISMSDataDef.h"

/*
*	ISMS_Init
*	�ӿ�˵����  SDK��ʼ��
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_Init();

/*
*	ISMS_Fini
*	�ӿ�˵����  SDK����ʼ��
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_Fini();

/*
*	ISMS_Login
*	�ӿ�˵����  �����û����������ƽ̨
*	����˵����
*                      pszIp��ƽ̨IP
*                      iPort��ƽ̨�˿�
*                      pszUserName��ƽ̨�����û���
*                      pszPassword��ƽ̨��������
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_Login(_IN_ const char* pszIp, _IN_ int iPort, _IN_ const char* pszUserName, _IN_ const char* pszPassword);

/*
*	ISMS_Login
*	�ӿ�˵����  �����û����������ƽ̨
*	����˵����
*                      pszIp��ƽ̨IP
*                      iPort��ƽ̨�˿�
*                      pszST��st
*                      pszUserUuid������ƽ̨�û���UUID
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_LoginByST(_IN_ const char* pszIp, _IN_ int iPort, _IN_ const char* pszST, _IN_ const char* pszUserUuid);

/*
*	ISMS_Logout
*	�ӿ�˵����  �ǳ�ƽ̨
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_Logout();

/*
*	ISMS_StartListenEvent
*	�ӿ�˵����  ��ʼ�����¼�
*	����˵����
*                      pFunc���ص���ַ
*                      pUserData���û�����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StartListenEvent(_IN_ pfnEventCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenEvent
*	�ӿ�˵����  ȡ�������¼�
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopListenEvent();

/*
*	ISMS_StartListenDataChange(�ݲ�֧��)
*	�ӿ�˵����  ��ʼ�������ݱ��
*	����˵����
*                      pFunc���ص���ַ
*                      pUserData���û�����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StartListenDataChange(_IN_ pfnDataChangeCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenDataChange(�ݲ�֧��)
*	�ӿ�˵����  ȡ���������ݱ��
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopListenDataChange();

/*
*	ISMS_StartListenResourceStatus
*	�ӿ�˵����  ��ʼ������Դ״̬���
*	����˵����
*                      pFunc���ص���ַ
*                      pUserData���û�����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StartListenResourceStatus(_IN_ pfnResourceStatusCallback pFunc, _IN_ void* pUserData);

/*
*	ISMS_StopListenResourceStatus
*	�ӿ�˵����  ȡ��������Դ״̬���
*	����˵����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopListenResourceStatus();

/*
*	ISMS_GetImageDataByUrl
*	�ӿ�˵����  ����ͼƬURL��ͼƬ����������ͼƬ���ݣ��ӿ��ڲ������ڴ�
*	����˵����  
*                      pszURL��ͼƬURL���������豸ץͼ�Ƚӿ�
*                      ppBuffer������ͼƬ���ݻ������ĵ�ַ
*                      piLen��ͼƬ���ݴ�С
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetImageDataByUrl(_IN_ const char* pszURL, _OUT_ char** ppBuffer, _OUT_ int* piLen);

/*
*	ISMS_ReleaseImageData
*	�ӿ�˵����  �ͷ�ͼƬ�����ڴ�
*	����˵����  
*                      pBuffer������ͼƬ���ݻ������ĵ�ַ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ReleaseImageData(_IN_ char* pBuffer);

/*
*	ISMS_GetImageFile
*	�ӿ�˵����  ����ͼƬURL��ͼƬ����������ͼƬ
*	����˵����  
*                      pszURL��ͼƬURL���������豸ץͼ�Ƚӿ�
*                      pszPathFile�������ļ����ƣ���"C://Snap//test.jpg"
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetImageFile(_IN_ const char* pszURL, _IN_ const char* pszPathFile);

/*
*	ISMS_GetCtrlUnitInfo
*	�ӿ�˵����  ��ҳ��ȡ�������ģ�֧��ȫ�����������ַ�ʽ
*	����˵����  
*                      pstPageReq����ҳ����
*                      pstPageRsp����ҳ������Ӧ
*                      pstCtrlUnit������������Ϣ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetCtrlUnitInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_CTRLUNIT pstCtrlUnit);

/*
*	ISMS_GetRegionInfo
*	�ӿ�˵����  ��ҳ��ȡ����֧��ȫ�����������ַ�ʽ
*	����˵����
*                      pstPageReq����ҳ����
*                      pstPageRsp����ҳ������Ӧ
*                      pstRegion��������Ϣ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetRegionInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_REGION pstRegion);

/*
*	ISMS_GetVideoDeviceInfo
*	�ӿ�˵����  ��ҳ��ȡ�豸��Ϣ��֧��ȫ�����������ַ�ʽ
*	����˵����
*                      pstPageReq����ҳ����
*                      pstPageRsp����ҳ������Ӧ
*                      pstDevice���豸��Ϣ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetVideoDeviceInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_DEVICE pstDevice);

/*
*	ISMS_GetCameraInfo
*	�ӿ�˵����  ��ҳ��ȡ��ص���Ϣ��֧��ȫ�����������ַ�ʽ
*	����˵����
*                      pstPageReq����ҳ����
*                      pstPageRsp����ҳ������Ӧ
*                      pstCamera����ص���Ϣ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetCameraInfo(_IN_ PISMS_PAGE_REQ pstPageReq, _OUT_ PISMS_PAGE_RSP pstPageRsp, _OUT_ PISMS_CAMERA pstCamera);

/*
*	ISMS_StartPreview
*	�ӿ�˵����  ��ʼԤ��
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      hWnd��WINDOWS���ھ�������ΪNULL��ֻͨ��pfnStreamֻ����
*                      enType��������������
*                      pfnStream�������ص���ַ�������ΪNULL����ͨ���ûص�����
*                      pUserData���û�����
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_StartPreview(_IN_ const char* pszCameraUuid, _IN_ void* hWnd, _IN_ ISMS_STREAM_TYPE_EN enType, _IN_ pfnStreamCallback  pfnStream = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_StopPreview
*	�ӿ�˵����  ֹͣ��ƵԤ��
*	����˵����  
*                      lPlayHandle����ƵԤ�����������ISMS_StartPreview��ISMS_StartPreviewEx������ֵ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopPreview(_IN_ long lPlayHandle);

/*
*	ISMS_PreviewSnapshot
*	�ӿ�˵����  Ԥ��ץͼ
*	����˵����  
*                      lPlayHandle����ƵԤ�����������ISMS_StartPreview��ISMS_StartPreviewEx������ֵ
*                      pszSaveFilePath�������ļ����ƣ�֧��jpg��bmp����"C:\\Snap\\test.jpg"
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_PreviewSnapshot(_IN_ long lPlayHandle, _IN_ const char* pszSaveFilePath);

/*
*	ISMS_DeviceSnapshotAsData
*	�ӿ�˵����  �豸ץͼ������ͼƬ�ֽ���
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      enImageSize��ץͼ�ߴ�
*                      enImageQuality��ץͼ����
*                      ppBuffer��ͼƬ���ݻ�������ַ���ӿ��ڲ������ڴ�
*                      piSize��ͼƬ��������С
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_DeviceSnapshotAsData(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_SIZE_EN enSize, _IN_ ISMS_IMAGE_QUALITY_EN enQuality, _OUT_ char** ppBuffer, _OUT_ int* piSize);

/*
*	ISMS_ReleaseDeviceSnapshotData
*	�ӿ�˵����  �ͷ�ͼƬ�����ڴ�
*	����˵����  
*                      pBuffer������ͼƬ���ݻ������ĵ�ַ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ReleaseDeviceSnapshotData(_IN_ char* pBuffer);

/*
*	int ISMS_DeviceSnapshotAsUrl
*	�ӿ�˵����  �豸ץͼ������ͼƬ��ͼƬ�������ϵ�URL
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      enSize��ץͼ�ߴ�
*                      enQuality��ץͼ����
*                      pszUrlBuffer��ͼƬURL��������ַ
*                      uiBufferSize��ͼƬURL��������С������512�ֽ�
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_DeviceSnapshotAsUrl(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_SIZE_EN enSize, _IN_ ISMS_IMAGE_QUALITY_EN enQuality, _OUT_ char* pszUrlBuffer, _IN_ unsigned int uiBufferSize);

/*
*	ISMS_StartManualRecord
*	�ӿ�˵����  �ֶ�¼��
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      enRecordLocationType��¼��洢λ��
*                      iRecordSeconds��¼�����ʱ�䣬��λ����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StartManualRecord(_IN_ const char* pszCameraUuid, _IN_ ISMS_RECORD_LOCATION_EN enRecordLocationType, _IN_ int iRecordSeconds);

/*
*	ISMS_QueryRecordPlan
*	�ӿ�˵����  ��ѯ¼��ƻ�
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      ppstRecPlanInfo��¼��ƻ�����ָ���ַ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_QueryRecordPlan(_IN_ const char* pszCameraUuid, _OUT_ PISMS_RECORD_PLAN* ppstRecPlanInfo);

/*
*	ISMS_ReleaseRecordPlan
*	�ӿ�˵����  �ͷ�¼��ƻ��ڴ�
*	����˵����  
*                      pstRecordPlan��¼��ƻ������ͷָ��
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ReleaseRecordPlan(_IN_ PISMS_RECORD_PLAN pstRecordPlan);

/*
*	int ISMS_QueryRecord
*	�ӿ�˵����  ��ѯ¼��
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      enRecordType��¼�����ͣ�ȡֵ���ISMS_RECORD_TYPE_EN����������ʹ�á�|������
*                      enLocation��¼��洢λ��
*                      iBeginTime����ѯ��ʼʱ�������λ����
*                      iEndTime����ѯ����ʱ�������λ����
*                      ppstRecordSection��¼��Ƭ������ͷָ���ַ����NULL�򲻷���¼��Ƭ��
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_QueryRecord(_IN_ const char* pszCameraUuid, _IN_ int iRecordType, _IN_ ISMS_RECORD_LOCATION_EN enLocation, _IN_ __int64 iBeginTime, _IN_ __int64 iEndTime, _OUT_ PISMS_RECORD_SECTION* ppstRecordSection);

/*
*	ISMS_ReleaseRecord
*	�ӿ�˵����  �ͷ�¼��Ƭ���ڴ�
*	����˵����  
*                      pstRecordSection��¼��Ƭ�������ͷָ��
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ReleaseRecordSection(_IN_ PISMS_RECORD_SECTION pstRecordSection);

/*
*	ISMS_CloseQueryRecord
*	�ӿ�˵����  �ͷ�¼���ѯ���
*	����˵����  
*                      lQueryHandle��¼���ѯ���
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_CloseQueryRecord(_IN_ long lQueryHandle);

/*
*	int ISMS_StartPlayback
*	�ӿ�˵����  ��ʼ�ط�
*	����˵����
*                      lQueryHandle��¼���ѯ�����������ISMS_QueryRecord����ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pFunֻ����
*                      pFunc�������ص���ַ�������ΪNULL����ͨ���ûص�����
*                      pUserData���û�����
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_StartPlayback(_IN_ long lQueryHandle, _IN_ void* hWnd, _IN_ pfnStreamCallback pFunc = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_StopPlayback
*	�ӿ�˵����  ֹͣ¼��ط�
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopPlayback(_IN_ long lPlayHandle);

/*
*	ISMS_SetPlaybackSpeed
*	�ӿ�˵����  ���ûط��ٶ�
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*                      iSpeed���ٶ�ֵ��ȡֵ��16��8��4��2��1��-2��-4��-8��-16
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_SetPlaybackSpeed(_IN_ long lPlayHandle, _IN_ int iSpeed);

/*
*	ISMS_PausePlayback
*	�ӿ�˵����  ��ͣ¼��ط�
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_PausePlayback(_IN_ long lPlayHandle);

/*
*	ISMS_ResumePlayback
*	�ӿ�˵����  �ָ�¼��ط�
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ResumePlayback(_IN_ long lPlayHandle);

/*
*	ISMS_SeekPlayback
*	�ӿ�˵����  ��λ¼��طţ�֧�ֺ���ϵ���豸
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*                      iSeeckTime����λ����ʱ�������λ����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_SeekPlayback(_IN_ long lPlayHandle, _IN_ __int64 iSeeckTime);

/*
*	ISMS_PlaybackSnapshot
*	�ӿ�˵����  �ط�ץͼ
*	����˵����  
*                      lPlayHandle��¼��طž��������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*                      pszSaveFilePath�������ļ����ƣ�֧��jpg��bmp����"C:\\Snap\\test.jpg"
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_PlaybackSnapshot(_IN_ long lPlayHandle, _IN_ const char* pszSaveFilePath);

/*
*	ISMS_StartDownloadRecord
*	�ӿ�˵����  ��ʼ¼������
*	����˵����
*                      lQueryHandle��¼���ѯ�����������ISMS_QueryRecord����ֵ
*                      pszSaveFilePath��¼���ļ�����·�����ƣ�Ŀǰֻ֧��mp4��ʽ���硰C:\Record\test.mp4��
*                      uiMaxFileSize�����ְ���С����λ���ֽ�
*                      pfnGetPercent�����ؽ��Ȼص���ַ
*                      pUserData���û�����
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_StartDownloadRecord(_IN_ long lQueryHandle, _IN_ const char* pszSaveFilePath, _IN_ unsigned __int64 uiMaxFileSize, _IN_ pfnProgressCallback pfnGetPercent, _IN_ void* pUserData);

/*
*	ISMS_StopDownloadRecord
*	�ӿ�˵���� ֹͣ¼������
*	����˵����  
*                      lDownloadHandle��¼�����ؾ����������ISMS_StartDownloadRecord����ֵ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopDownloadRecord(_IN_ long lDownloadHandle);

/*
*	ISMS_StartDeviceTalk
*	�ӿ�˵����  �豸�Խ���֧��ģ�⡢����ͨ���Խ���ͬһʱ��ֻ��һ���豸һ·�Խ�
*	����˵����
*                      pszDeviceUuid���豸Uuid
*                      iTalkChannelId���Խ�ͨ����
*                      enDevTalkType���Խ����ͣ���ʶ������ͨ���Խ�����ģ��ͨ���Խ�
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StartDeviceTalk(_IN_ const char* pszDeviceUuid, _IN_ int iTalkChannelId, _IN_ ISMS_TALK_TYPE_EN enDevTalkType);

/*
*	ISMS_StopDeviceTalk
*	�ӿ�˵���� ֹͣ�豸�Խ�
*	����˵����  
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_StopDeviceTalk();

/*
*	ISMS_PtzControl
*	�ӿ�˵����  ��̨���ƣ�֧�ְ˸�����ת�����Զ�ɨ�衢��Ȧ���ڡ�������ڡ���ͷ������Զ������Ԥ�õ㡢���ӷŴ��Լ���̨������ع���
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      iPtzCommand����̨����������ISMS_PTZ_*
*                      iAction����̨����������ֹͣ�����ISMS_PTZ_ACTION_*
*                      iSpeed����̨�����ٶȣ���iPtzCommandΪ�˸�����ת�����Զ�ɨ�衢��Ȧ���ڡ���������Լ���ͷ������Զʱ��Ч
*                      iParam����̨���Ʋ�������iPtzCommandΪISMS_PTZ_GOTO_PRESETʱΪԤ�õ�id����iPtzCommandΪISMS_PTZ_LOCKʱΪ����ʱ�䣨��λ���룩����
*                                    iPtzCommandΪΪ����ֵʱ��Ч
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_PtzControl(_IN_ const char* pszCameraUuid, _IN_ int iPtzCommand, _IN_ int iAction, _IN_ int iSpeed, _IN_ int iParam);

/*
*	ISMS_GetPresetByCamera
*	�ӿ�˵����  ��ȡԤ�õ�
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      pstPerset��Ԥ�õ�����ͷָ���ַ
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetPresetByCamera(_IN_ const char* pszCameraUuid, _OUT_ PISMS_PRESET_INFO* pstPerset);

/*
*	ISMS_ReleasePresetInfo
*	�ӿ�˵���� �ͷ�Ԥ�õ��ڴ�
*	����˵����  
*                      pstPerset��Ԥ֧������ͷָ��
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ReleasePresetInfo(_IN_ PISMS_PRESET_INFO pstPerset);

/*
*	ISMS_SetPreset
*	�ӿ�˵����  ����Ԥ�õ�
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      iPersetId��Ԥ�õ�id
*                      pszPersetName��Ԥ�õ�����
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_SetPreset(_IN_ const char* pszCameraUuid, _IN_ int iPersetId, _IN_ const char* pszPersetName);

/*
*	ISMS_ClearPreset
*	�ӿ�˵����  ���Ԥ�õ�
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      iPersetId��Ԥ�õ�id
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_ClearPreset(_IN_ const char* pszCameraUuid, _IN_ int iPersetId);

/*
*	ISMS_GetPlaybackTime
*	�ӿ�˵����  ��ȡ��ǰ�ط�ʱ�䣨��֧�ֺ����豸��
*	����˵����  
*                      lPlayHandle���طž����������ISMS_StartPlayback��ISMS_StartPlaybackEx������ֵ
*                      piPlayTime�����Σ���ǰ�ط�ʱ���
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetPlaybackTime(_IN_ long lPlayHandle, _OUT_ __int64* piPlayTime);

/*
*	ISMS_GetVideoImageParam
*	�ӿ�˵����  ��ȡ��Ƶͼ�����
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      pstImageParam�����Σ���Ƶͼ�����ָ��
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetVideoImageParam(_IN_ const char* pszCameraUuid, _OUT_ ISMS_IMAGE_PARAM* pstImageParam);

/*
*	ISMS_SetVideoImageParam
*	�ӿ�˵����  ��ȡ��Ƶͼ�����
*	����˵����  
*                      pszCameraUuid����ص�Uuid
*                      pstImageParam����Ƶͼ�����ָ��
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_SetVideoImageParam(_IN_ const char* pszCameraUuid, _IN_ ISMS_IMAGE_PARAM* pstImageParam);

/*
*	ISMS_OpenSound
*	�ӿ�˵����  ��Ԥ����ط�����
*	����˵����  
*                      ���ž����������ISMS_StartPreview��ISMS_StartPreviewEx����ISMS_StartPlayback��ISMS_StartPlaybackEx���ķ���ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ�
*                      enType : �������ͣ����ISMS_PLAY_TYPE_EN
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_OpenSound(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_CloseSound
*	�ӿ�˵����  �ر�Ԥ����ط�����
*	����˵����  
*                      ���ž����������ISMS_StartPreview��ISMS_StartPreviewEx����ISMS_StartPlayback��ISMS_StartPlaybackEx���ķ���ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ�
*                      enType : �������ͣ����ISMS_PLAY_TYPE_EN
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_CloseSound(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetVolume
*	�ӿ�˵����  ��ȡԤ����ط�ʱ����������ȡֵ[0 100]
*	����˵����  
*                      ���ž����������ISMS_StartPreview��ISMS_StartPreviewEx����ISMS_StartPlayback��ISMS_StartPlaybackEx���ķ���ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ�
*                      enType : �������ͣ����ISMS_PLAY_TYPE_EN
*	����ֵ��      -1��ʾʧ�ܣ�������ʾ����ֵ��ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetVolume(_IN_ long lPlayHandle, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_SetVolume
*	�ӿ�˵����  ����Ԥ����ط�ʱ����
*	����˵����  
*                      ���ž����������ISMS_StartPreview��ISMS_StartPreviewEx����ISMS_StartPlayback��ISMS_StartPlaybackEx���ķ���ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ�
*                      iVolume : ����ֵ��ȡֵ��Χ��[0 100]
*                      enType : �������ͣ����ISMS_PLAY_TYPE_EN
*	����ֵ��      -1��ʾʧ�ܣ�������ʾ����ֵ��ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_SetVolume(_IN_ long lPlayHandle, _IN_ int iVolume, _IN_ ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetVideoDeviceInfoByUuid
*	�ӿ�˵����  ��������Uuid��ȡ������Ϣ
*	����˵����  
*                      pszDevUuid����Ƶ�����豸UUID
*                      pstDevice : ��Ƶ�����豸��Ϣָ��
*	����ֵ��      -1��ʾʧ�ܣ�������ʾ����ֵ��ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetVideoDeviceInfoByUuid(_IN_ const char* pszDevUuid, _OUT_ PISMS_DEVICE pstDevice);

/*
*	ISMS_GetCameraInfoByUuid
*	�ӿ�˵����  ��������Uuid��ȡ������Ϣ
*	����˵����  
*                      pszCameraUuid����ص�UUID
*                      pstCamera : ��ص���Ϣָ��
*	����ֵ��      -1��ʾʧ�ܣ�������ʾ����ֵ��ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetCameraInfoByUuid(_IN_ const char* pszCameraUuid, _OUT_ PISMS_CAMERA pstCamera);

/*
*	ISMS_GetStreamTraceType
*	�ӿ�˵����  ��ȡȡ��·��
*	����˵����  lPlayHandle�����ž��������ISMS_StartPreview�ķ���ֵ
*	����ֵ��      ���ISMS_STRAM_TRACE_TYPE��������ֵ��TYPE_TRACE_ERRORʱΪʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API ISMS_STRAM_TRACE_TYPE_EN ISMS_GetStreamTraceType(_IN_ const char* pszCameraUuid);

/*
*	ISMS_GetVideoDetailInfo
*	�ӿ�˵����  ��ȡ�续��ֱ��ʡ�֡�ʵ���Ƶ��ϸ��Ϣ
*	����˵����  lPlayHandle�����ž��������ISMS_StartPreview�ķ���ֵ
*               pstDetail����Ƶ��ϸ��Ϣָ��
*           	enType���������ͣ���Ԥ���ͻط�
*	����ֵ��      0 ���óɹ�, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API int ISMS_GetVideoDetailInfo(_IN_ long lPlayHandle, _OUT_ PISMS_VIDEO_DETAIL_INFO pstDetail, ISMS_PLAY_TYPE_EN enType);

/*
*	ISMS_GetStreamTypeISMS_STRAM_TRACE_TYPE
*	�ӿ�˵����  ��ȡ��ǰԤ��������������
*	����˵����  lPlayHandle�����ž��������ISMS_StartPreview�ķ���ֵ
*	����ֵ��      ���ISMS_STREAM_TYPE_EN��������ֵ��TYPE_ERROR_STREAMʱΪʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API ISMS_STREAM_TYPE_EN ISMS_GetStreamType(_IN_ long lPlayHandle);

/*
*	ISMS_StartPreviewEx
*	�ӿ�˵����  ��ʼԤ����֧����Ϣ�ص���ת��װ�����ص��������YUV���ݻص�
*	����˵����
*                      pszCameraUuid����ص�Uuid
*                      hWnd��WINDOWS���ھ�������ΪNULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ���
*                      enStreamType��������������
*                      fnTranformedStream�����;�ת�����������ݣ��ݲ�֧�֣��ûص��������ܻ��޸ģ��봫NULL��
*                      fnPlayMsg����Ϣ�ص������ISMS_PLAY_MSG_EN
*                      fnDecodedStream����������Ƶ���ݻص���YUV���ݣ�
*                      pUserData���û�����
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_StartPreviewEx(_IN_ const char* pszCameraUuid, _IN_ void* hWnd, _IN_ ISMS_STREAM_TYPE_EN enType, _IN_ pfnStreamCallback fnTranformedStream = NULL, _IN_ pfnPlayMsgCallback fnPlayMsg = NULL, _IN_ pfnDecodedDataCallback fnDecodedStream = NULL, _IN_ void* pUserData = NULL);

/*
*	int ISMS_StartPlaybackEx
*	�ӿ�˵����  ��ʼ�طţ�֧����Ϣ�ص���ת��װ�����ص��������YUV���ݻص�
*	����˵����
*                      lQueryHandle��¼���ѯ�����������ISMS_QueryRecord����ֵ
*                      hWnd��WINDOWS���ھ���������NULL����ͨ��pfnTranformedStream��fnDecodedStream��������������в�ΪNULL�Ļ���
*                      fnTranformedStream�����;�ת�����������ݣ��ݲ�֧�֣��ûص��������ܻ��޸ģ��봫NULL��
*                      fnPlayMsg����Ϣ�ص������ISMS_PLAY_MSG_EN
*                      fnDecodedStream����������Ƶ���ݻص���YUV���ݣ�
*                      pUserData���û�����
*	����ֵ��      �ɹ����ؾ��, -1 ����ʧ�ܣ�ͨ��ISMS_GetLastError()�鿴������
*/
ISMSSDK_API long ISMS_StartPlaybackEx(_IN_ long lQueryHandle, _IN_ void* hWnd, _IN_ pfnStreamCallback fnTranformedStream = NULL, _IN_ pfnPlayMsgCallback fnPlayMsg = NULL, _IN_ pfnDecodedDataCallback fnDecodedStream = NULL, _IN_ void* pUserData = NULL);

/*
*	ISMS_GetVersion
*	�ӿ�˵����  ��ȡSDK�汾��
*	����˵����  
*	����ֵ��      ������
*/
ISMSSDK_API const char* ISMS_GetVersion();

/*
*	ISMS_GetLastError
*	�ӿ�˵����  ��ȡ������
*	����˵����  
*	����ֵ��      ������
*/
ISMSSDK_API int ISMS_GetLastError();

#ifdef __cplusplus
}
#endif
#endif