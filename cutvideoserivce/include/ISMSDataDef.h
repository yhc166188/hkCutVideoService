#pragma once
#include <string.h>
////////////////////////////////////////////// �����붨�� ///////////////////////////////////////////////////////
#define ISMS_ERR_FAIL                                          -1     // ʧ��
#define ISMS_ERR_NOERROR                                0      // �ɹ�
#define ISMS_ERR_PARAM                                    1      // ��������
#define ISMS_ERR_NET_EXCEPTION                      2      // �����쳣
#define ISMS_ERR_APPLY_MEMORY                     3      // �����ڴ�ʧ��
#define ISMS_ERR_BUFFER_SMALL                       4      // �����ڴ治��
#define ISMS_ERR_NOT_INIT                                5      // δ��ʼ��
#define ISMS_ERR_WS_INIT                                  6      // webservice��ʼ��ʧ��
#define ISMS_ERR_DEV_NO_RSP                          7     // �豸����Ӧ
#define ISMS_ERR_STREAM_DLL_INIT                  8      // ��ý�������ʧ��
#define ISMS_ERR_USER_HANDLE_NO_RLS         9      // �û����δ�ͷŶ����з���ʼ��
#define ISMS_ERR_USER_HANDLE_INVALID        10      // �û������Ч
#define ISMS_ERR_CREATE_THREAD                    11      // �����߳�ʧ��
#define ISMS_ERR_CONNECT_SERVER                 12      // �޷����ӷ�����
#define ISMS_ERR_NOERR_BUT_NODATA           13      // ���ӿڳɹ�����������

// ������ش���
#define ISMS_ERR_LOGIN                                     100      // ����ʧ��
#define ISMS_ERR_NOT_LOGIN                            101      // δ����
#define ISMS_ERR_LOGOUT                                  102      // �ǳ�ʧ��
#define ISMS_ERR_PASSWORD                             103      // �������
#define ISMS_ERR_USER_ALREADY_LOGIN           104      // �û��ѵ���
#define ISMS_ERR_USER_EXPIRED                         105      // �û��ѹ���
#define ISMS_ERR_NOT_ACTIVE                            106     // �û�δ����
#define ISMS_ERR_USER_MULTI                            107     // �û�����Ψһ
#define ISMS_ERR_USER_DELETE                           108      // �û���ɾ��
#define ISMS_ERR_USER                                        109     // �û���������
#define ISMS_ERR_USER_ID                                   110      // �޴��û��ỰID

// Ȩ�޴���
#define ISMS_ERR_QUERY_RIGHT                          201     // ��ѯȨ��ʧ��
#define ISMS_ERR_NO_CTRL_RIGHT                      202     // �û��޿���Ȩ��
#define ISMS_ERR_NO_CONFIG_RIGHT                 203     // �û�������Ȩ��
#define ISMS_ERR_NO_REALPLAY_RIGHT              204     // �û���Ԥ��Ȩ��
#define ISMS_ERR_NO_PLAYBACK_RIGHT             205     // �û��޻ط�Ȩ��
#define ISMS_ERR_NO_RESOURCE                         206     // �޴���Դ

// ��ȡ��Դ����
#define ISMS_ERR_GET_CTRLUNIT                         301     // ��ȡ��������ʧ��
#define ISMS_ERR_GET_REGION                             302     // ��ȡ����ʧ��
#define ISMS_ERR_GET_PRESET                              303     // ��ȡԤ�õ�ʧ��
#define ISMS_ERR_GET_RECPLAN                           304     // ��ȡ¼��ƻ�ʧ��
#define ISMS_ERR_GET_SERVER                              305    // ��ȡ��������Ϣʧ��
#define ISMS_ERR_GET_RECORD                            306     // ��ѯ¼���ļ�ʧ��
#define ISMS_ERR_GET_DEVICE                              307     // ��ȡ�豸ʧ��
#define ISMS_ERR_GET_CAMERA                           308     // ��ȡ��ص�ʧ��
#define ISMS_ERR_GET_PICTURE                            309     // ��ȡͼƬʧ��
#define ISMS_ERR_GETPLAYTIME                           310     // ��ȡ�ط�ʱ��ʧ��
#define ISMS_ERR_GETIMGPARAM                        311     // ��ȡ��Ƶͼ�����ʧ��
#define ISMS_ERR_GET_STREAMTRACETYPE          312     // ��ѯȡ��·��ʧ��
#define ISMS_ERR_GET_STREAMTYPE                     313    // ��ѯ������������ʧ��
#define ISMS_ERR_GET_VIDEODETAILINFO            314    // ��ѯ��Ƶ��ϸ��Ϣʧ��

// ��Դ���ƴ���
#define ISMS_ERR_RES_CONTROL                           701     // ��Դ����ʧ��
#define ISMS_ERR_PTZ_CONTROL                           702     // ��̨����ʧ��
#define ISMS_ERR_PTZ_CTRL_LOCK                         703     // ��̨��ռʧ��
#define ISMS_ERR_REALPLAY                                   704     // Ԥ��ʧ��
#define ISMS_ERR_PLAYBACK                                  705     // �ط�ʧ��
#define ISMS_ERR_STOPPLAY                                  706     // ֹͣԤ��ʧ��
#define ISMS_ERR_STOPPLAYBACK                         707     // ֹͣ�ط�ʧ��
#define ISMS_ERR_PLAYCTRL                                   708     // ���ſ���ʧ��
#define ISMS_ERR_STARTTALK                                709     // �Խ�ʧ��
#define ISMS_ERR_STOPTALK                                  710     // ֹͣ�Խ�ʧ��
#define ISMS_ERR_SNAP                                          711     // ץͼʧ��
#define ISMS_ERR_MANUALRECORD                      712     // �ֶ�¼��ʧ��
#define ISMS_ERR_DOWNLOAD                              713     // ¼������ʧ��
#define ISMS_ERR_STOP_DOWNLOAD                    714     // ֹͣ¼������ʧ��
#define ISMS_ERR_OPER_PRESET                             715     // Ԥ�õ����ʧ��
#define ISMS_ERR_SETIMGPARAM                          716     // ������Ƶͼ�����ʧ��
#define ISMS_ERR_OPER_SOUND                            717     // ��������ʧ��
#define ISMS_ERR_RECORD                   718  // ¼��ʧ��

////////////////////////////////////////////// ö�ٶ��� /////////////////////////////////////////////////////////

// ��Դ��������ö��
typedef enum enUpdateType
{
    TYPE_UPDATE_UNKNOWN = 0,
    TYPE_UPDATE_ADDMOD = 1,  // ��Դ���ӻ��޸�
    TYPE_UPDATE_DELETE = 2,   // ��Դɾ��
}ISMS_UPDATE_TYPE_EN;

// ������������ö��
typedef enum enStreamDataType
{
    TYPE_HEADER = 1,   // ����ͷ��
    TYPE_DATA = 2,     // ��������
    TYPE_TAIL = 3,       // ����β��
}ISMS_STREAM_DATA_TYPE_EN;

// �¼�����ö��
typedef enum enEventType
{
    EVENT_TYPE_UNKNOWN = 0,
    //��ص㱨��
    EVENT_TYPE_CAMERA_LOST = 0x00020101,   //��Ƶ��ʧ
    EVENT_TYPE_CAMERA_COVER = 0x00020102,   //��Ƶ�ڵ�
    EVENT_TYPE_CAMERA_MOVING = 0x00020103,   //�ƶ����
	EVENT_TYPE_PIR_ALARM = 0x00020104,    // PIR����
	EVENT_TYPE_WIRELES_ALARM = 0x00020105,    // ���߱���
	EVENT_TYPE_CALLING_ALARM = 0x00020106,    // ���ȱ���
	EVENT_TYPE_AUDIO_INPUT_EXCEPTION = 0x00020107,    // ��Ƶ�����쳣
	EVENT_TYPE_AUDIO_INPUT_MUTATION = 0x00020108,    // ��Ƶ����ͻ��
	EVENT_TYPE_CAMERA_OFFLINE = 0x00020109,    // ��ص����
	EVENT_TYPE_CAMERA_ONLINE = 0x0002010A,    // ��ص�����

    //���ܱ���
    EVENT_TYPE_SMART_CROSSING = 0x00020201,    // ��Խ������
    EVENT_TYPE_SMART_IN = 0x00020202,    // ��������
    EVENT_TYPE_SMART_OUT = 0x00020203,    // �뿪����
    EVENT_TYPE_SMART_REGION_INVASION = 0x00020204,     // ��������
    EVENT_TYPE_SMART_PICUP = 0x00020205,    // ��Ʒ��ȡ����
    EVENT_TYPE_SMART_HOVER = 0x00020206,    // �ǻ�
    EVENT_TYPE_SMART_PARKING = 0x00020207,    // ͣ��
    EVENT_TYPE_SMART_MOVING_FAST = 0x00020208,    // �����ƶ�
    EVENT_TYPE_SMART_PERSON_AGGREGATION = 0x00020209,    // ��Ա�ۼ�
    EVENT_TYPE_SMART_GOODS_BEHIND = 0x0002020A,    // ��Ʒ����
    EVENT_TYPE_SMART_GOODS_TAKING = 0x0002020B,    // ��Ʒ��ȡ
    EVENT_TYPE_SMART_VIOLENT_MOTION = 0x0002020C,    // �����˶�
	EVENT_TYPE_SMART_CLIMBING_DETECTION = 0x0002020D,    // �ʸ߼��
	EVENT_TYPE_SMART_GETTING_UP_DETECTION = 0x0002020E,    // ������
	EVENT_TYPE_SMART_CLOSING_TO_ATM = 0x0002020F,    // �˿���ATM
	EVENT_TYPE_SMART_OPERATION_TIMEOUT = 0x00020210,    // ������ʱ
	EVENT_TYPE_SMART_STICKER_STRIP = 0x00020211,    // ��ֽ��
	EVENT_TYPE_SMART_INSTALLING_CARDR_EADER = 0x00020212,    // ��װ������
	EVENT_TYPE_SMART_ABSENCE_DETECTION = 0x00020213,    // ���
	EVENT_TYPE_SMART_TRAILING_DETECTION = 0x00020214,    // β��
	EVENT_TYPE_SMART_FALLING_DETECTION = 0x00020215,    // ���ؼ��
	EVENT_TYPE_SMART_SOUND_SUDDEN_CHANGE_DETECTION = 0x00020216,    // ��ǿͻ����
	EVENT_TYPE_SMART_BROKEN_LINE_CLIMBING = 0x00020217,    // �����ʸ�
	EVENT_TYPE_SMART_WC_TIMEOUT = 0x00020218,    // ��޳�ʱ
	EVENT_TYPE_SMART_PLAYGROUND_OVERSTAY = 0x00020219,    // �ŷ糡����
	EVENT_TYPE_SMART_KEY_PERSON_GETTING_UP = 0x0002021A,    // �ص���Ա����
	EVENT_TYPE_SMART_BROKEN_LINE_WARNING_SURFACE = 0x0002021B,    // ���߾�����
	EVENT_TYPE_SMART_SCENE_CHANGE_ALARM = 0x0002021C,    // �����������
	EVENT_TYPE_SMART_DEFOCUS_ALARM = 0x0002021D,    // �齹����
	EVENT_TYPE_SMART_FACE_RECOGNITION_RESULT = 0x0002021E,    // ����ʶ����
	EVENT_TYPE_SMART_PASSENGER_FLOW_INFO = 0x00020220,    // ��������Ϣ
	EVENT_TYPE_SMART_PASSENGER_FLOW_FULL = 0x00020221,    // ��������Ա
	EVENT_TYPE_SMART_OVERCROWDING_ALARM = 0x00020222,    // ����Ա����
	EVENT_TYPE_SMART_HEAT_MAP_INFO = 0x00020223,    // �ȶ�ͼ��Ϣ
	EVENT_TYPE_SMART_FACE_RECOGNITION_WHITE_LIST = 0x000202224,    // ����ʶ�������
	EVENT_TYPE_SMART_FACE_DETECTION = 0x000202225,    // �������
	EVENT_TYPE_SMART_VEHICLE_DETECTION = 0x00020226,    // �������
	EVENT_TYPE_SMART_AUDIO_INPUT_EXCEPTION = 0x00020227,    // ��Ƶ�����쳣
	EVENT_TYPE_SMART_AUDIO_INPUT_MUTATION = 0x00020228,    // ��Ƶ����ͻ��
	EVENT_TYPE_SMART_TEACHING = 0x00020229,    // �ڿ�
	EVENT_TYPE_SMART_ANSWER_QUESTION = 0x0002022A,    // �ش�����
	EVENT_TYPE_SMART_PASSENGER_FLOW_DATA_TIMESPAN = 0x0002022B,    // ����������-ʱ���
	EVENT_TYPE_SMART_PASSWNGER_FLOW_DATA_FRAME = 0x0002022C,    // ����������-��֡
	EVENT_TYPE_SMART_HEAT_MAP_DATA_STATISTIC = 0x0002022D,    // �ȶ�ͼ����-ͳ��
	EVENT_TYPE_SMART_HEAT_MAP_DATA_ABOSOLTION = 0x0002022E,    // �ȶ�ͼ����-����
	EVENT_TYPE_SMART_ABNORMAL_POPULATION = 0x0002022F,    // �����쳣
	EVENT_TYPE_SMART_ABNORMAL_INTEVAL = 0x00020230,    // ����쳣
	EVENT_TYPE_SMART_PERSON_STANDING = 0x00020231,    // ��Ավ��
	EVENT_TYPE_SMART_FACE_CAPTURE_STATISTIC = 0x00020232,    // ����ץ��ͳ������
	EVENT_TYPE_SMART_REGIONAL_ALARM = 0x00020233,    // ���򿴷�����
	EVENT_TYPE_SMART_DOUBLE_GUARD_ALARM = 0x00020234,    // ˫��ֵ�ڱ���
	EVENT_TYPE_SMART_GUARD_DETECTION_ALARM = 0x00020235,    // ֵ�ڼ�ⱨ��
	EVENT_TYPE_SMART_BLACK_LIST_DEPLOYMENT = 0x00020236,    // ����������
	EVENT_TYPE_SMART_ILLEGAl_PARKING_ALARM = 0x00020237,    // Υͣ�澯
	EVENT_TYPE_SMART_FACE_BLACK_LIST_ALARM_6200FA = 0x00020238,    // 6200FA��������������
	EVENT_TYPE_SMART_FACE_PICTURE_COMPARISON_ALARM = 0x00020254, // �����ȶԱ���(���ס�������������������)

}ISMS_EVENT_TYPE_EN;

// �¼��ȼ�ö��
typedef enum enEventLevel
{
    EVENT_LEVEL_UNKNOWN = 0, //δ֪����
    EVENT_LEVEL_HIGH = 1, //�ߵȼ������¼�
    EVENT_LEVEL_MIDUME = 2, //�еȼ������¼�
    EVENT_LEVEL_LOW = 3, //�͵ȼ������¼�
    EVENT_LEVEL_NORAML = 4 //��ͨ�¼�
}ISMS_EVENT_LEVEL_EN;

// �¼�״̬ö��
typedef enum enEventStatus
{
    EVENT_STATUS_UNKNOWN = 0, //δ֪״̬
    EVENT_STATUS_INSTANT = 1, //˲ʱ�¼����ǳ������¼�
    EVENT_STATUS_BEGIN = 2, //�¼���ʼ
    EVENT_STATUS_END = 3, //�¼�ֹͣ
    EVENT_STATUS_UPDATE = 4, //�¼���Ϣ����
	EVENT_STATUS_PULSE = 5   // �����¼�
}ISMS_EVENT_STATUS_EN;

// ���ݱ������ö��
typedef enum enDataChangeType
{
    DATA_CHANGE_TYPE_UNKNOWN = 0,
    DATA_CHANGE_TYPE_ADD = 1, //����
    DATA_CHANGE_TYPE_MODIFY = 2, //�޸�
    DATA_CHANGE_TYPE_DELETE = 3, //ɾ��
}ISMS_DATA_CHANGE_TYPE_EN;

// ��Դ����ö��
typedef enum enRsrcType
{
    RESOURCE_TYPE_UNKNOWN = 0,
    RESOURCE_TYPE_ENCODER = 1, //��Ƶ�����豸
    RESOURCE_TYPE_CAMERA = 2,  //��ص�
}ISMS_RESOURCE_TYPE_EN;

// ��Դ״̬ö��
typedef enum enRsrcStatus
{
    RESOURCE_STATUS_UNKNOWN = 0,
    //IO��Դ״̬
    RESOURCE_STATUS_IOOPEN = 9,  //IO��
    RESOURCE_STATUS_IOCLOSE = 10,   //IO�ر�
    //��Դͨ��״̬����Ƶ�豸��
    RESOURCE_STATUS_ONLINE = 11,  //����
    RESOURCE_STATUS_OFFLINE = 12  //����
}ISMS_RESOURCE_STATUS_EN;

// �豸����
typedef enum enDeviceType
{
    DEVICE_TYPE_UNKNOWN = 0,
    DEVICE_TYPE_HIK = 1,     // hik�豸
    DEVICE_TYPE_DAHUA = 2,  // ���豸
}ISMS_DEVICE_TYPE_EN;

// ��������ö��
typedef enum enStreamType
{
    TYPE_ERROR_STREAM = -1,
    TYPE_DEFAULT_STREAM = 0,  // Ĭ���������ͣ�ʹ��ƽ̨������ֵ
    TYPE_MAIN_STREAM = 1,    // ������
    TYPE_SUB_STREAM = 2,     // ������
}ISMS_STREAM_TYPE_EN;

// �豸ץͼ�ߴ�ö��
typedef enum enImageSize
{
    SIZE_CIF = 0,           // CIF(352*288/352*240)
    SIZE_QCIF = 1,         // QCIF(176*144/176*120)
    SIZE_4CIF_OR_D1 = 2,  //4CIF(704*576/704*480)��D1(720*576/720*486)
    SIZE_UXGA = 3,       // UXGA(1600*1200)
    SIZE_SVGA = 4,       // SVGA(800*600)
    SIZE_HD720P = 5,      // HD720P(1280*720)
    SIZE_VGA = 6,         // VGA(640*480)
    SIZE_XVGA = 7,       // XVGA(1280*960)
    SIZE_HD900P = 8,      //HD900P(1600*900)
    SIZE_HD1080P = 9,     // HD1080P(1920*1080)
    SIZE_2560x1024 = 10,
    SIZE_1600x204 = 11,
    SIZE_2048x1536 = 12,
    SIZE_2448x2048 = 13,
    SIZE_2448x1200 = 14,
    SIZE_2448x800 = 15,
    SIZE_XGA = 16,       //XGA(1024*768)
    SIZE_SXGA = 17,      //SXGA(1280*1024)
    SIZE_WD1 = 18,       //WD1(960*576/960*480)
    SIZE_1080I = 19,      //1080I(1920*1080)
    SIZE_576x576 = 20,
    SIZE_1536x1536 = 21,
    SIZE_1920x1920 = 22,
    SIZE_Auto = 0xFF     //(ʹ�õ�ǰ�����ֱ���)
}ISMS_IMAGE_SIZE_EN;

// �豸ץͼ����ö��
typedef enum enImageQuality
{
    QUALITY_BEST = 0,
    QUALITY_GOOD = 1,
    QUALITY_NORMAL = 2
}ISMS_IMAGE_QUALITY_EN;

// ¼��洢λ��ö��
typedef enum enRecordLocation
{
    LOCATION_UNKNOWN = 0,
    LOCATION_DEVICE = 1,  //�豸�洢
    LOCATION_PCNVR = 2,   //PCNVR�洢
    LOCATION_CVR = 3,      //CVR�洢
    LOCATION_CVM = 4      //CVM�洢
}ISMS_RECORD_LOCATION_EN;

// ¼������ö��
typedef enum enRecType
{
    RECORD_TYPE_UNKNOWN = 0, //δ֪����
    RECORD_TYPE_PLAN = 0x01,     // �ƻ�¼��
    RECORD_TYPE_MOVE = 0x02,     // �ƶ�¼��
    RECORD_TYPE_ALARM = 0x04,    // �澯¼��
    RECORD_TYPE_MANUAL = 0x10   // �ֶ�¼��
}ISMS_RECORD_TYPE_EN;

// �Խ�ͨ������ö��
typedef enum enTalkType
{
    TYPE_TALK_UNKNOWN = 0,
    TYPE_TALK_ANALOG = 1,     // ģ��ͨ���Խ�
    TYPE_TALK_DIGITAL = 2,     // ����ͨ���Խ�
}ISMS_TALK_TYPE_EN;

typedef enum enPlayType
{
    PLAYTYPE_PREVIEW = 0,       // Ԥ��
    PLAYTYPE_PLAYBACK = 1,    // �ط�
}ISMS_PLAY_TYPE_EN;

// ȡ��·��ö��
typedef enum enStreamTraceType
{
    TYPE_TRACE_ERROR,
    TYPE_TRACE_CASC,         // ����
    TYPE_TRACE_DEVICE,      // ֱ���豸
    TYPE_TRACE_VAG,          // ����VAG
    TYPE_TRACE_SMS,          // ��׼����ý�岻��VAG
    TYPE_TRACE_SMS_VAG,         // ��׼����ý���VAG
    TYPE_TRACE_SMS_CASC,       // ��ý�弶������VAG
    TYPE_TRACE_SMS_CASC_VAG,      // ��ý�弶����VAG
    TYPE_TRACE_UNKNOWN,
}ISMS_STRAM_TRACE_TYPE_EN;

/////////////////////////////////////////// ͨ���ַ����ȶ���//////////////////////////////////////////////////////
#define MAX_COMMON_UUID_LENGTH 64          // ͨ��UUID�ַ����ֽڳ���
#define MAX_COMMON_NAME_LENGTH 256        // ͨ�������ַ����ֽڳ���
#define MAX_COMMON_TIME_LENGTH 32          // ͨ������ʱ���ַ����ֽڳ���
#define MAX_COMMON_IP_LENGTH 32             // ͨ��IP�ַ����ֽڳ���
#define MAX_COMMON_USER_LENGTH 64         // ͨ���û����ַ����ֽڳ���
#define MAX_COMMON_PASSWORD_LENGTH 64     // ͨ�������ַ����ֽڳ���
#define MAX_COMMON_DATA_NAME 128            // ͨ�����ݱ�������ַ����ֽڳ���
#define MAX_COMMON_DESCRIPUTE_LENGTH 512   // ͨ�������ַ����ֽڳ���
#define MAX_COMMON_URL_LENGTH 2038          // ͨ��URL�ַ����ֽڳ���

//////////////////////////////////////////// ��̨������ض��� /////////////////////////////////////////////////
#define ISMS_PTZ_UP                      21                    // ����ת��         
#define ISMS_PTZ_DOWN               22                    // ����ת�� 
#define ISMS_PTZ_LEFT                   23                    // ����ת��
#define ISMS_PTZ_RIGHT                24                    // ����ת��
#define ISMS_PTZ_UP_LEFT             25                    // ������ת��
#define ISMS_PTZ_UP_RIGHT          26                    // ������ת��
#define ISMS_PTZ_DOWN_LEFT      27                    // ������ת��
#define ISMS_PTZ_DOWN_RIGHT   28                    // ������ת��
#define ISMS_PTZ_AUTO                 29                    // �Զ�ɨ��
#define ISMS_PTZ_ZOOM_IN          11                    // ��ͷ����
#define ISMS_PTZ_ZOOM_OUT      12                    // ��ͷ��Զ
#define ISMS_PTZ_FOCUS_NEAR    13                    // ����ǰ��
#define ISMS_PTZ_FOCUS_FAR       14                    // �������
#define ISMS_PTZ_IRIS_OPEN         15                    // ��Ȧ����
#define ISMS_PTZ_IRIS_CLOSE        16                    // ��Ȧ��С
#define ISMS_PTZ_GOTO_PRESET   39                    // ����Ԥ�õ�
#define ISMS_PTZ_SEL_ZOOM        99                    // ���ӷŴ�
#define ISMS_PTZ_LOCK                 200                  // ��̨����
#define ISMS_PTZ_UNLOCK            201                  // ��̨����
#define ISMS_PTZ_UNLOCK_ALL    202                  // ��������ܹ�����������
#define ISMS_PTZ_LOCK_CHECK     203                  // �������

#define ISMS_PTZ_ACTION_START  0    // ��̨��ʼ
#define ISMS_PTZ_ACTION_STOP    1    // ��̨����

/////////////////////////////////////////// ��Ƶ����֡���Ͷ��� //////////////////////////////////////////////////

// ��Ƶ���ݣ�uyvy��ʽ����U0-Y0-V0-Y1-U2-Y2-V2-Y3��.������һ������λ��ͼ�����Ͻ�
#define ISMS_FRAME_TYPE_UYVY      1 

// ��Ƶ���ݣ�yv12��ʽ����ǰ��������Ƶ��ʽ������˳��Y0-Y1-����������V0-V1��.������U0-U1-��..��
#define ISMS_FRAME_TYPE_YV12             3 

// ��Ƶ���ݡ�ÿ������4���ֽڣ����з�ʽ��λͼ���ƣ���B-G-R-0 ��������һ������λ��ͼ�����½�
#define ISMS_FRAME_TYPE_RGB32           7

// ��Ƶ����;������16khz����������ÿ��������16λ��ʾ�������Խ��������Ƶ��ϢΪ׼
#define ISMS_FRAME_TYPE_AUDIO16      101

//////////////////////////////////////////// �ṹ�嶨��////////////////////////////////////////////////////////////
// ��ҳ����ṹ��
typedef struct stPageReq
{
    int iPageNo;  //����ҳ�루��1��ʼ��
    int iPageRows;  //ÿҳ����
    __int64 iLastUpdateTime;   // �ϴθ������ݵ�����ʱ�䣬�������0����ʾȫ����ȡ���ݣ��������0����ʾ������ȡ����
    stPageReq() : iPageNo(0), iPageRows(400), iLastUpdateTime(0)  // ����400��ÿҳ
    {
    }
}ISMS_PAGE_REQ, *PISMS_PAGE_REQ;

// ��ҳ������Ӧ�ṹ��
typedef struct stPageRsp
{
    int iPageNo; //��ǰҳ�루��1��ʼ��
    int iPageRows;  //ÿҳ����
    int iTotalPage;  // ��ҳ��
    int iRealRows;   //��ǰҳ�뷵�ؼ�¼�������һҳ���¼��һ����ҳ��
    __int64 iUpdateTime;     //�������ݸ���ʱ��
    stPageRsp() : iPageNo (1), iPageRows (400), iTotalPage(0), iRealRows(0), iUpdateTime(-1)
    {
    }
}ISMS_PAGE_RSP, *PISMS_PAGE_RSP;

// �������Ľṹ��
typedef struct stCtrlUnit
{
    ISMS_UPDATE_TYPE_EN updateType;                //��Դ��������
    char szCtrlUnitUuid[MAX_COMMON_UUID_LENGTH]; //��������UUID
    char szCtrlUnitName[MAX_COMMON_NAME_LENGTH]; //������������
    char szParentCtrlUnitUuid[MAX_COMMON_UUID_LENGTH];  // ����������UUID��Ϊ���ַ���ʱ��ʾ���ڵ�

    stCtrlUnit() : updateType(TYPE_UPDATE_UNKNOWN)
    {
        memset(szCtrlUnitUuid, 0, sizeof(szCtrlUnitUuid));
        memset(szCtrlUnitName, 0, sizeof(szCtrlUnitName));
        memset(szParentCtrlUnitUuid, 0, sizeof(szParentCtrlUnitUuid));
    }
}ISMS_CTRLUNIT, *PISMS_CTRLUNIT;

// ����ṹ��
typedef struct stRegion
{
    ISMS_UPDATE_TYPE_EN updateType;                //��Դ��������
    char szRegionUuid[MAX_COMMON_UUID_LENGTH]; //����UUID
    char szRegionName[MAX_COMMON_NAME_LENGTH]; //��������
    char szParentRegionUuid[MAX_COMMON_UUID_LENGTH]; //������UUID
    char szParentCtrlUnitUUid[MAX_COMMON_UUID_LENGTH]; //����������UUID

    stRegion() : updateType(TYPE_UPDATE_UNKNOWN)
    {
        memset(szRegionUuid, 0, sizeof(szRegionUuid));
        memset(szRegionName, 0, sizeof(szRegionName));
        memset(szParentRegionUuid, 0, sizeof(szParentRegionUuid));
        memset(szParentCtrlUnitUUid, 0, sizeof(szParentCtrlUnitUUid));
    }
}ISMS_REGION, *PISMS_REGION;

typedef struct stDevice
{
    int iAnalogTalkChanSize;  // ģ��Խ�ͨ����
    int iDigitalTalkChanSize;  // ���ֶԽ�ͨ����
    ISMS_RESOURCE_STATUS_EN status;                // �豸״̬
    ISMS_UPDATE_TYPE_EN updateType;                //��Դ��������
    char szDeviceUuid[MAX_COMMON_UUID_LENGTH]; // �豸UUID
    char szDeviceName[MAX_COMMON_NAME_LENGTH]; 
    ISMS_DEVICE_TYPE_EN enDevType;                         // �豸����
    char szCtrlUnitUuid[MAX_COMMON_UUID_LENGTH]; // ��������UUID

    stDevice() : iAnalogTalkChanSize(0), iDigitalTalkChanSize(0), enDevType(DEVICE_TYPE_HIK), updateType(TYPE_UPDATE_UNKNOWN), status(RESOURCE_STATUS_UNKNOWN)
    {
        memset(szDeviceUuid, 0, sizeof(szDeviceUuid));
        memset(szDeviceName, 0, sizeof(szDeviceName));
        memset(szCtrlUnitUuid, 0, sizeof(szCtrlUnitUuid));
    }
}ISMS_DEVICE, *PISMS_DEVICE;

typedef struct stCamera
{
    int iChannelIndex; //���豸������ͨ����
    char szCameraUuid[MAX_COMMON_UUID_LENGTH]; //��ص�UUID
    char szCameraName[MAX_COMMON_NAME_LENGTH]; //��ص�����
    ISMS_RESOURCE_STATUS_EN status;                //��ص�״̬
    ISMS_UPDATE_TYPE_EN updateType;                //��Դ��������
    char szDeviceUuid[MAX_COMMON_UUID_LENGTH]; //�豸UUID
    char szRegionUuid[MAX_COMMON_UUID_LENGTH]; //����UUID

    stCamera() : iChannelIndex(0), status(RESOURCE_STATUS_OFFLINE), updateType(TYPE_UPDATE_UNKNOWN)
    {
        memset(szCameraUuid, 0, sizeof(szCameraUuid));
        memset(szCameraName, 0, sizeof(szCameraName));
        memset(szDeviceUuid, 0, sizeof(szDeviceUuid));
        memset(szRegionUuid, 0, sizeof(szRegionUuid));
    }
}ISMS_CAMERA, *PISMS_CAMERA;

typedef struct stRecordPlan
{
    ISMS_RECORD_LOCATION_EN enLocation; //¼��洢λ��
    char szPlanUuid[MAX_COMMON_UUID_LENGTH]; //¼��ƻ�UUID
    char szPlanName[MAX_COMMON_NAME_LENGTH]; //¼��ƻ�����

    stRecordPlan* pNext;
    stRecordPlan() : enLocation(LOCATION_UNKNOWN), pNext(NULL)
    {
        memset(szPlanUuid, 0, sizeof(szPlanUuid));
        memset(szPlanName, 0, sizeof(szPlanName));
    }
}ISMS_RECORD_PLAN, *PISMS_RECORD_PLAN;

// ¼��Ƭ�νṹ��
typedef struct stRecordSection
{
    __int64 i64Start;  // ¼��Ƭ�����ʱ�䣬��λ����
    __int64 i64End;  // ¼��Ƭ�����ʱ�䣬��λ����
    ISMS_RECORD_TYPE_EN enSegRecType;    // ¼��Ƭ������

    stRecordSection* pNext;
    stRecordSection() : i64Start(0), i64End(0), pNext(NULL), enSegRecType(RECORD_TYPE_UNKNOWN)
    {
    }
}ISMS_RECORD_SECTION, *PISMS_RECORD_SECTION;

// Ԥ�õ�ṹ��
typedef struct stPreset
{
    int iPresetId;          // Ԥ�õ�id
    char szName[MAX_COMMON_NAME_LENGTH]; //Ԥ�õ�����
    stPreset* pNext;
    stPreset() : iPresetId(-1), pNext(NULL)
    {
        memset(szName, 0, sizeof(szName));
    }
}ISMS_PRESET_INFO, *PISMS_PRESET_INFO;

typedef struct stImageParam
{
    int iHue;      // ɫ����ȡֵ��Χ��[1, 10]
    int iContrast;   // �Աȶȣ�ȡֵ��Χ��[1, 10]
    int iBright;    // ���ȣ�ȡֵ��Χ��[1, 10]
    int iSaturation; // ���Ͷȣ�ȡֵ��Χ��[1, 10]
    stImageParam () : iHue (0), iContrast (0), iBright(0), iSaturation(0)
    {
    } 
}ISMS_IMAGE_PARAM, *PISMS_IMAGE_PARAM;


// �¼��ṹ��
typedef struct stEvent            
{
    ISMS_EVENT_TYPE_EN enEvtType;             // �¼�����
    ISMS_EVENT_LEVEL_EN enEvtLevel;           // �¼��ȼ���1-�� 2-�� 3-�� 4-��ͨ
    ISMS_EVENT_STATUS_EN enEvtStatus;         //�¼�״̬
    const char* pszAdditionInfo;                             // �¼�������Ϣ����XML������ʽ����������
    char szEventTime[MAX_COMMON_TIME_LENGTH];     //����ʱ�䣬����2018-12-12 10:11:12
    char szSrcUuid[MAX_COMMON_UUID_LENGTH];        // �¼�Դ���
    char szSrcName[MAX_COMMON_NAME_LENGTH];      // �¼�Դ����
    char szEventUuid[MAX_COMMON_UUID_LENGTH];      // �¼����
    char szEventName[MAX_COMMON_NAME_LENGTH];    // �¼�����
    char szDescripute[MAX_COMMON_DESCRIPUTE_LENGTH];         // �¼�����
    stEvent():enEvtType(EVENT_TYPE_UNKNOWN),enEvtLevel(EVENT_LEVEL_UNKNOWN),enEvtStatus(EVENT_STATUS_UNKNOWN),pszAdditionInfo(NULL)
    {
        memset(szEventTime, 0, sizeof(szEventTime)); 
        memset(szSrcUuid, 0, sizeof(szSrcUuid));
        memset(szSrcName, 0, sizeof(szSrcName));
        memset(szEventUuid, 0, sizeof(szEventUuid));
        memset(szEventName, 0, sizeof(szEventName));
        memset(szDescripute, 0, sizeof(szDescripute));
    }
}ISMS_EVENT, *PISMS_EVENT;

// ���ݱ���ṹ��
typedef struct stDataChange
{
    ISMS_DATA_CHANGE_TYPE_EN enChangeType;          // ֪ͨ����
    char szSubsystemUuid[MAX_COMMON_DATA_NAME];     // ��ϵͳUUID
    char szChangeDataName[MAX_COMMON_DATA_NAME]; //����������ƣ�"controlunit":�������ģ�"region":����"device":�豸��Ϣ��"camera":��ص�
    stDataChange() : enChangeType(DATA_CHANGE_TYPE_UNKNOWN)
    {
        memset(szSubsystemUuid, 0, sizeof(szSubsystemUuid));
        memset(szChangeDataName, 0, sizeof(szChangeDataName));
    }
}ISMS_DATA_CHANGE, *PISMS_DATA_CHANGE;

// ��Դ״̬����ṹ��
typedef struct stResourceStatusChange
{
    ISMS_RESOURCE_TYPE_EN enRsourceType;    // ��Դ���ͣ�
    char szResourceUuid[MAX_COMMON_UUID_LENGTH]; //��ԴUUID
    ISMS_RESOURCE_STATUS_EN enResourceStatus; //��Դ״̬�����豸���ߣ����ߣ��쳣
    char szStatusDescription[MAX_COMMON_DESCRIPUTE_LENGTH];    // ״̬����

    stResourceStatusChange() : enRsourceType (RESOURCE_TYPE_UNKNOWN), enResourceStatus(RESOURCE_STATUS_UNKNOWN)
    {
        memset(szResourceUuid, 0, sizeof(szResourceUuid));
        memset(szStatusDescription, 0, sizeof(szStatusDescription));
    }
}ISMS_RESOURCE_STATUS_CHANGE, *PISMS_RESOURCE_STATUS_CHANGE;

// ��Ƶ��ϸ��Ϣ
typedef struct stVideoDetailInfo
{
    int iPicWidth;                    // ͼ����
    int iPicHeight;                   // ͼ��߶�
    unsigned __int64 ui64FrameRate;      // ֡��
    stVideoDetailInfo() : iPicWidth(0), iPicHeight(0), ui64FrameRate(0)
    {
    }
}ISMS_VIDEO_DETAIL_INFO, *PISMS_VIDEO_DETAIL_INFO;

////////////////////////////////////////////////// �ص����� /////////////////////////////////////////////////////////////////
/*
*	pfnEventCallback
*	�ӿ�˵����  �¼�������ַ
*	����˵����
*                      pstEvent�����������¼�
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall* pfnEventCallback)(PISMS_EVENT pstEvent, void* pUserData);

/*
*	pfnDataChangeCallback
*	�ӿ�˵����  ���ݱ��������ַ
*	����˵����
*                      pstDataNotify�������������ݱ����Ϣ
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall* pfnDataChangeCallback)( PISMS_DATA_CHANGE pstDataNotify, void* pUserData);

/*
*	pfnResourceStatusCallback
*	�ӿ�˵����  ��Դ״̬���������ַ
*	����˵����
*                      pstResourceStatus������������Դ״̬�����Ϣ
*                      iResNum����Դ����
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall* pfnResourceStatusCallback)(PISMS_RESOURCE_STATUS_CHANGE pstResourceStatus, int iResNum, void* pUserData);

/*
*	pfnStreamCallback
*	�ӿ�˵����  �����ص���ַ
*	����˵����
*                      lPlayHnadle��Ԥ�����
*                      enStreamType���û�����
*                      pDataArray���������ݣ����ַ������赱�ɶ�����������ʹ�ã�
*                      iDataLen���������ݳ���
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall *pfnStreamCallback)(long lPlayHnadle, ISMS_STREAM_DATA_TYPE_EN enStreamDataType, const char* pDataArray, int iDataLen, void* pUserData);

/*
*	pfnProgressCallback
*	�ӿ�˵����  ¼�����ؽ��Ȼص���ַ
*	����˵����
*                      lDownloadHandle��¼�����ؾ��
*                      fPercent��¼�����ؽ���
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall *pfnProgressCallback)(long lDownloadHandle, float fPercent, void* pUserData);

/*
*	pfnPlayMsgCallback
*	�ӿ�˵����  ������Ϣ�ص���������Ԥ�����ط�
*	����˵����
*                      lPlayHandle��¼�����ؾ��
*                      iMsg��������Ϣ��1-���ſ�ʼ 2-���Ž��� 3-������ͣ 4-�ָ����� 5-����ֹͣ
*                      pUserData���û�����
*	����ֵ��      
*/
typedef void (__stdcall *pfnPlayMsgCallback)(long lPlayHandle, int iMsg, void* pUserData);

/*
 *	pfnDecodedDataCallback
 *	�ӿ�˵������Ƶ��������ݻص���������Ԥ�����ط�
 * ����˵����
 *                  lPlayHandle�� ���ž��
 *	                 pDataArray �����������ݣ����ַ������赱�ɶ�����������ʹ�ã�
 *	                 iDataLen�� ���ݳ���
 *	                 iWidth�� ͼ���ȣ���λ�����أ����֡��������Ƶ����Ϊ��Ƶ������
 *                  iHeight��ͼ��߶ȣ���λ�����أ����֡��������Ƶ����Ϊ��λ��
 *                  iFrameType��ͼ��yuv���ͣ�ȡֵ���ISMS_FRAME_TYPE_*
 *                  iTimeStamp��ʱ���
 *	                 pUserData�� �û��Զ�������
 */
typedef void (__stdcall* pfnDecodedDataCallback)(long lPlayHandle, const char* pDataArray, int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData);