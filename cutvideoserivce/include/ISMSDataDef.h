#pragma once
#include <string.h>
////////////////////////////////////////////// 错误码定义 ///////////////////////////////////////////////////////
#define ISMS_ERR_FAIL                                          -1     // 失败
#define ISMS_ERR_NOERROR                                0      // 成功
#define ISMS_ERR_PARAM                                    1      // 参数错误
#define ISMS_ERR_NET_EXCEPTION                      2      // 网络异常
#define ISMS_ERR_APPLY_MEMORY                     3      // 申请内存失败
#define ISMS_ERR_BUFFER_SMALL                       4      // 申请内存不足
#define ISMS_ERR_NOT_INIT                                5      // 未初始化
#define ISMS_ERR_WS_INIT                                  6      // webservice初始化失败
#define ISMS_ERR_DEV_NO_RSP                          7     // 设备无响应
#define ISMS_ERR_STREAM_DLL_INIT                  8      // 流媒体库启动失败
#define ISMS_ERR_USER_HANDLE_NO_RLS         9      // 用户句柄未释放而进行反初始化
#define ISMS_ERR_USER_HANDLE_INVALID        10      // 用户句柄无效
#define ISMS_ERR_CREATE_THREAD                    11      // 创建线程失败
#define ISMS_ERR_CONNECT_SERVER                 12      // 无法连接服务器
#define ISMS_ERR_NOERR_BUT_NODATA           13      // 调接口成功，但无数据

// 登入相关错误
#define ISMS_ERR_LOGIN                                     100      // 登入失败
#define ISMS_ERR_NOT_LOGIN                            101      // 未登入
#define ISMS_ERR_LOGOUT                                  102      // 登出失败
#define ISMS_ERR_PASSWORD                             103      // 密码错误
#define ISMS_ERR_USER_ALREADY_LOGIN           104      // 用户已登入
#define ISMS_ERR_USER_EXPIRED                         105      // 用户已过期
#define ISMS_ERR_NOT_ACTIVE                            106     // 用户未激活
#define ISMS_ERR_USER_MULTI                            107     // 用户名不唯一
#define ISMS_ERR_USER_DELETE                           108      // 用户已删除
#define ISMS_ERR_USER                                        109     // 用户名不存在
#define ISMS_ERR_USER_ID                                   110      // 无此用户会话ID

// 权限错误
#define ISMS_ERR_QUERY_RIGHT                          201     // 查询权限失败
#define ISMS_ERR_NO_CTRL_RIGHT                      202     // 用户无控制权限
#define ISMS_ERR_NO_CONFIG_RIGHT                 203     // 用户无配置权限
#define ISMS_ERR_NO_REALPLAY_RIGHT              204     // 用户无预览权限
#define ISMS_ERR_NO_PLAYBACK_RIGHT             205     // 用户无回放权限
#define ISMS_ERR_NO_RESOURCE                         206     // 无此资源

// 获取资源错误
#define ISMS_ERR_GET_CTRLUNIT                         301     // 获取控制中心失败
#define ISMS_ERR_GET_REGION                             302     // 获取区域失败
#define ISMS_ERR_GET_PRESET                              303     // 获取预置点失败
#define ISMS_ERR_GET_RECPLAN                           304     // 获取录像计划失败
#define ISMS_ERR_GET_SERVER                              305    // 获取服务器信息失败
#define ISMS_ERR_GET_RECORD                            306     // 查询录像文件失败
#define ISMS_ERR_GET_DEVICE                              307     // 获取设备失败
#define ISMS_ERR_GET_CAMERA                           308     // 获取监控点失败
#define ISMS_ERR_GET_PICTURE                            309     // 获取图片失败
#define ISMS_ERR_GETPLAYTIME                           310     // 获取回放时间失败
#define ISMS_ERR_GETIMGPARAM                        311     // 获取视频图像参数失败
#define ISMS_ERR_GET_STREAMTRACETYPE          312     // 查询取流路径失败
#define ISMS_ERR_GET_STREAMTYPE                     313    // 查询主子码流类型失败
#define ISMS_ERR_GET_VIDEODETAILINFO            314    // 查询视频详细信息失败

// 资源控制错误
#define ISMS_ERR_RES_CONTROL                           701     // 资源控制失败
#define ISMS_ERR_PTZ_CONTROL                           702     // 云台控制失败
#define ISMS_ERR_PTZ_CTRL_LOCK                         703     // 云台抢占失败
#define ISMS_ERR_REALPLAY                                   704     // 预览失败
#define ISMS_ERR_PLAYBACK                                  705     // 回放失败
#define ISMS_ERR_STOPPLAY                                  706     // 停止预览失败
#define ISMS_ERR_STOPPLAYBACK                         707     // 停止回放失败
#define ISMS_ERR_PLAYCTRL                                   708     // 播放控制失败
#define ISMS_ERR_STARTTALK                                709     // 对讲失败
#define ISMS_ERR_STOPTALK                                  710     // 停止对讲失败
#define ISMS_ERR_SNAP                                          711     // 抓图失败
#define ISMS_ERR_MANUALRECORD                      712     // 手动录像失败
#define ISMS_ERR_DOWNLOAD                              713     // 录像下载失败
#define ISMS_ERR_STOP_DOWNLOAD                    714     // 停止录像下载失败
#define ISMS_ERR_OPER_PRESET                             715     // 预置点操作失败
#define ISMS_ERR_SETIMGPARAM                          716     // 设置视频图像参数失败
#define ISMS_ERR_OPER_SOUND                            717     // 声音操作失败
#define ISMS_ERR_RECORD                   718  // 录像失败

////////////////////////////////////////////// 枚举定义 /////////////////////////////////////////////////////////

// 资源更新类型枚举
typedef enum enUpdateType
{
    TYPE_UPDATE_UNKNOWN = 0,
    TYPE_UPDATE_ADDMOD = 1,  // 资源增加或修改
    TYPE_UPDATE_DELETE = 2,   // 资源删除
}ISMS_UPDATE_TYPE_EN;

// 码流数据类型枚举
typedef enum enStreamDataType
{
    TYPE_HEADER = 1,   // 码流头部
    TYPE_DATA = 2,     // 码流数据
    TYPE_TAIL = 3,       // 码流尾部
}ISMS_STREAM_DATA_TYPE_EN;

// 事件类型枚举
typedef enum enEventType
{
    EVENT_TYPE_UNKNOWN = 0,
    //监控点报警
    EVENT_TYPE_CAMERA_LOST = 0x00020101,   //视频丢失
    EVENT_TYPE_CAMERA_COVER = 0x00020102,   //视频遮挡
    EVENT_TYPE_CAMERA_MOVING = 0x00020103,   //移动侦测
	EVENT_TYPE_PIR_ALARM = 0x00020104,    // PIR报警
	EVENT_TYPE_WIRELES_ALARM = 0x00020105,    // 无线报警
	EVENT_TYPE_CALLING_ALARM = 0x00020106,    // 呼救报警
	EVENT_TYPE_AUDIO_INPUT_EXCEPTION = 0x00020107,    // 音频输入异常
	EVENT_TYPE_AUDIO_INPUT_MUTATION = 0x00020108,    // 音频输入突变
	EVENT_TYPE_CAMERA_OFFLINE = 0x00020109,    // 监控点掉线
	EVENT_TYPE_CAMERA_ONLINE = 0x0002010A,    // 监控点上线

    //智能报警
    EVENT_TYPE_SMART_CROSSING = 0x00020201,    // 穿越警戒面
    EVENT_TYPE_SMART_IN = 0x00020202,    // 进入区域
    EVENT_TYPE_SMART_OUT = 0x00020203,    // 离开区域
    EVENT_TYPE_SMART_REGION_INVASION = 0x00020204,     // 区域入侵
    EVENT_TYPE_SMART_PICUP = 0x00020205,    // 物品拿取放置
    EVENT_TYPE_SMART_HOVER = 0x00020206,    // 徘徊
    EVENT_TYPE_SMART_PARKING = 0x00020207,    // 停车
    EVENT_TYPE_SMART_MOVING_FAST = 0x00020208,    // 快速移动
    EVENT_TYPE_SMART_PERSON_AGGREGATION = 0x00020209,    // 人员聚集
    EVENT_TYPE_SMART_GOODS_BEHIND = 0x0002020A,    // 物品遗留
    EVENT_TYPE_SMART_GOODS_TAKING = 0x0002020B,    // 物品拿取
    EVENT_TYPE_SMART_VIOLENT_MOTION = 0x0002020C,    // 剧烈运动
	EVENT_TYPE_SMART_CLIMBING_DETECTION = 0x0002020D,    // 攀高检测
	EVENT_TYPE_SMART_GETTING_UP_DETECTION = 0x0002020E,    // 起身检测
	EVENT_TYPE_SMART_CLOSING_TO_ATM = 0x0002020F,    // 人靠近ATM
	EVENT_TYPE_SMART_OPERATION_TIMEOUT = 0x00020210,    // 操作超时
	EVENT_TYPE_SMART_STICKER_STRIP = 0x00020211,    // 贴纸条
	EVENT_TYPE_SMART_INSTALLING_CARDR_EADER = 0x00020212,    // 安装读卡器
	EVENT_TYPE_SMART_ABSENCE_DETECTION = 0x00020213,    // 离岗
	EVENT_TYPE_SMART_TRAILING_DETECTION = 0x00020214,    // 尾随
	EVENT_TYPE_SMART_FALLING_DETECTION = 0x00020215,    // 倒地检测
	EVENT_TYPE_SMART_SOUND_SUDDEN_CHANGE_DETECTION = 0x00020216,    // 声强突变检测
	EVENT_TYPE_SMART_BROKEN_LINE_CLIMBING = 0x00020217,    // 折线攀高
	EVENT_TYPE_SMART_WC_TIMEOUT = 0x00020218,    // 如厕超时
	EVENT_TYPE_SMART_PLAYGROUND_OVERSTAY = 0x00020219,    // 放风场滞留
	EVENT_TYPE_SMART_KEY_PERSON_GETTING_UP = 0x0002021A,    // 重点人员起身
	EVENT_TYPE_SMART_BROKEN_LINE_WARNING_SURFACE = 0x0002021B,    // 折线警戒面
	EVENT_TYPE_SMART_SCENE_CHANGE_ALARM = 0x0002021C,    // 场景变更报警
	EVENT_TYPE_SMART_DEFOCUS_ALARM = 0x0002021D,    // 虚焦报警
	EVENT_TYPE_SMART_FACE_RECOGNITION_RESULT = 0x0002021E,    // 人脸识别结果
	EVENT_TYPE_SMART_PASSENGER_FLOW_INFO = 0x00020220,    // 客流量信息
	EVENT_TYPE_SMART_PASSENGER_FLOW_FULL = 0x00020221,    // 客流量满员
	EVENT_TYPE_SMART_OVERCROWDING_ALARM = 0x00020222,    // 区域超员报警
	EVENT_TYPE_SMART_HEAT_MAP_INFO = 0x00020223,    // 热度图信息
	EVENT_TYPE_SMART_FACE_RECOGNITION_WHITE_LIST = 0x000202224,    // 人脸识别白名单
	EVENT_TYPE_SMART_FACE_DETECTION = 0x000202225,    // 人脸侦测
	EVENT_TYPE_SMART_VEHICLE_DETECTION = 0x00020226,    // 车辆侦测
	EVENT_TYPE_SMART_AUDIO_INPUT_EXCEPTION = 0x00020227,    // 音频输入异常
	EVENT_TYPE_SMART_AUDIO_INPUT_MUTATION = 0x00020228,    // 音频输入突变
	EVENT_TYPE_SMART_TEACHING = 0x00020229,    // 授课
	EVENT_TYPE_SMART_ANSWER_QUESTION = 0x0002022A,    // 回答问题
	EVENT_TYPE_SMART_PASSENGER_FLOW_DATA_TIMESPAN = 0x0002022B,    // 客流量数据-时间段
	EVENT_TYPE_SMART_PASSWNGER_FLOW_DATA_FRAME = 0x0002022C,    // 客流量数据-单帧
	EVENT_TYPE_SMART_HEAT_MAP_DATA_STATISTIC = 0x0002022D,    // 热度图数据-统计
	EVENT_TYPE_SMART_HEAT_MAP_DATA_ABOSOLTION = 0x0002022E,    // 热度图数据-绝对
	EVENT_TYPE_SMART_ABNORMAL_POPULATION = 0x0002022F,    // 人数异常
	EVENT_TYPE_SMART_ABNORMAL_INTEVAL = 0x00020230,    // 间隔异常
	EVENT_TYPE_SMART_PERSON_STANDING = 0x00020231,    // 人员站立
	EVENT_TYPE_SMART_FACE_CAPTURE_STATISTIC = 0x00020232,    // 人脸抓拍统计数据
	EVENT_TYPE_SMART_REGIONAL_ALARM = 0x00020233,    // 区域看防报警
	EVENT_TYPE_SMART_DOUBLE_GUARD_ALARM = 0x00020234,    // 双人值岗报警
	EVENT_TYPE_SMART_GUARD_DETECTION_ALARM = 0x00020235,    // 值岗检测报警
	EVENT_TYPE_SMART_BLACK_LIST_DEPLOYMENT = 0x00020236,    // 黑名单布控
	EVENT_TYPE_SMART_ILLEGAl_PARKING_ALARM = 0x00020237,    // 违停告警
	EVENT_TYPE_SMART_FACE_BLACK_LIST_ALARM_6200FA = 0x00020238,    // 6200FA人脸黑名单报警
	EVENT_TYPE_SMART_FACE_PICTURE_COMPARISON_ALARM = 0x00020254, // 人脸比对报警(脸谱、超脑人脸黑名单报警)

}ISMS_EVENT_TYPE_EN;

// 事件等级枚举
typedef enum enEventLevel
{
    EVENT_LEVEL_UNKNOWN = 0, //未知错误
    EVENT_LEVEL_HIGH = 1, //高等级报警事件
    EVENT_LEVEL_MIDUME = 2, //中等级报警事件
    EVENT_LEVEL_LOW = 3, //低等级报警事件
    EVENT_LEVEL_NORAML = 4 //普通事件
}ISMS_EVENT_LEVEL_EN;

// 事件状态枚举
typedef enum enEventStatus
{
    EVENT_STATUS_UNKNOWN = 0, //未知状态
    EVENT_STATUS_INSTANT = 1, //瞬时事件，非持续性事件
    EVENT_STATUS_BEGIN = 2, //事件开始
    EVENT_STATUS_END = 3, //事件停止
    EVENT_STATUS_UPDATE = 4, //事件信息更新
	EVENT_STATUS_PULSE = 5   // 脉冲事件
}ISMS_EVENT_STATUS_EN;

// 数据变更类型枚举
typedef enum enDataChangeType
{
    DATA_CHANGE_TYPE_UNKNOWN = 0,
    DATA_CHANGE_TYPE_ADD = 1, //增加
    DATA_CHANGE_TYPE_MODIFY = 2, //修改
    DATA_CHANGE_TYPE_DELETE = 3, //删除
}ISMS_DATA_CHANGE_TYPE_EN;

// 资源类型枚举
typedef enum enRsrcType
{
    RESOURCE_TYPE_UNKNOWN = 0,
    RESOURCE_TYPE_ENCODER = 1, //视频编码设备
    RESOURCE_TYPE_CAMERA = 2,  //监控点
}ISMS_RESOURCE_TYPE_EN;

// 资源状态枚举
typedef enum enRsrcStatus
{
    RESOURCE_STATUS_UNKNOWN = 0,
    //IO资源状态
    RESOURCE_STATUS_IOOPEN = 9,  //IO打开
    RESOURCE_STATUS_IOCLOSE = 10,   //IO关闭
    //资源通用状态（视频设备）
    RESOURCE_STATUS_ONLINE = 11,  //在线
    RESOURCE_STATUS_OFFLINE = 12  //离线
}ISMS_RESOURCE_STATUS_EN;

// 设备类型
typedef enum enDeviceType
{
    DEVICE_TYPE_UNKNOWN = 0,
    DEVICE_TYPE_HIK = 1,     // hik设备
    DEVICE_TYPE_DAHUA = 2,  // 大华设备
}ISMS_DEVICE_TYPE_EN;

// 码流类型枚举
typedef enum enStreamType
{
    TYPE_ERROR_STREAM = -1,
    TYPE_DEFAULT_STREAM = 0,  // 默认码流类型，使用平台上配置值
    TYPE_MAIN_STREAM = 1,    // 主码流
    TYPE_SUB_STREAM = 2,     // 子码流
}ISMS_STREAM_TYPE_EN;

// 设备抓图尺寸枚举
typedef enum enImageSize
{
    SIZE_CIF = 0,           // CIF(352*288/352*240)
    SIZE_QCIF = 1,         // QCIF(176*144/176*120)
    SIZE_4CIF_OR_D1 = 2,  //4CIF(704*576/704*480)或D1(720*576/720*486)
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
    SIZE_Auto = 0xFF     //(使用当前码流分辨率)
}ISMS_IMAGE_SIZE_EN;

// 设备抓图质量枚举
typedef enum enImageQuality
{
    QUALITY_BEST = 0,
    QUALITY_GOOD = 1,
    QUALITY_NORMAL = 2
}ISMS_IMAGE_QUALITY_EN;

// 录像存储位置枚举
typedef enum enRecordLocation
{
    LOCATION_UNKNOWN = 0,
    LOCATION_DEVICE = 1,  //设备存储
    LOCATION_PCNVR = 2,   //PCNVR存储
    LOCATION_CVR = 3,      //CVR存储
    LOCATION_CVM = 4      //CVM存储
}ISMS_RECORD_LOCATION_EN;

// 录像类型枚举
typedef enum enRecType
{
    RECORD_TYPE_UNKNOWN = 0, //未知类型
    RECORD_TYPE_PLAN = 0x01,     // 计划录像
    RECORD_TYPE_MOVE = 0x02,     // 移动录像
    RECORD_TYPE_ALARM = 0x04,    // 告警录像
    RECORD_TYPE_MANUAL = 0x10   // 手动录像
}ISMS_RECORD_TYPE_EN;

// 对讲通道类型枚举
typedef enum enTalkType
{
    TYPE_TALK_UNKNOWN = 0,
    TYPE_TALK_ANALOG = 1,     // 模拟通道对讲
    TYPE_TALK_DIGITAL = 2,     // 数字通道对讲
}ISMS_TALK_TYPE_EN;

typedef enum enPlayType
{
    PLAYTYPE_PREVIEW = 0,       // 预览
    PLAYTYPE_PLAYBACK = 1,    // 回放
}ISMS_PLAY_TYPE_EN;

// 取流路径枚举
typedef enum enStreamTraceType
{
    TYPE_TRACE_ERROR,
    TYPE_TRACE_CASC,         // 级联
    TYPE_TRACE_DEVICE,      // 直连设备
    TYPE_TRACE_VAG,          // 单过VAG
    TYPE_TRACE_SMS,          // 标准过流媒体不过VAG
    TYPE_TRACE_SMS_VAG,         // 标准过流媒体过VAG
    TYPE_TRACE_SMS_CASC,       // 流媒体级联不过VAG
    TYPE_TRACE_SMS_CASC_VAG,      // 流媒体级联过VAG
    TYPE_TRACE_UNKNOWN,
}ISMS_STRAM_TRACE_TYPE_EN;

/////////////////////////////////////////// 通用字符长度定义//////////////////////////////////////////////////////
#define MAX_COMMON_UUID_LENGTH 64          // 通用UUID字符串字节长度
#define MAX_COMMON_NAME_LENGTH 256        // 通用名称字符串字节长度
#define MAX_COMMON_TIME_LENGTH 32          // 通用日期时间字符串字节长度
#define MAX_COMMON_IP_LENGTH 32             // 通用IP字符串字节长度
#define MAX_COMMON_USER_LENGTH 64         // 通用用户名字符串字节长度
#define MAX_COMMON_PASSWORD_LENGTH 64     // 通用密码字符串字节长度
#define MAX_COMMON_DATA_NAME 128            // 通用数据变更名称字符串字节长度
#define MAX_COMMON_DESCRIPUTE_LENGTH 512   // 通用描述字符串字节长度
#define MAX_COMMON_URL_LENGTH 2038          // 通用URL字符串字节长度

//////////////////////////////////////////// 云台控制相关定义 /////////////////////////////////////////////////
#define ISMS_PTZ_UP                      21                    // 向上转动         
#define ISMS_PTZ_DOWN               22                    // 向下转动 
#define ISMS_PTZ_LEFT                   23                    // 向左转动
#define ISMS_PTZ_RIGHT                24                    // 向右转动
#define ISMS_PTZ_UP_LEFT             25                    // 向左上转动
#define ISMS_PTZ_UP_RIGHT          26                    // 向右上转动
#define ISMS_PTZ_DOWN_LEFT      27                    // 向左下转动
#define ISMS_PTZ_DOWN_RIGHT   28                    // 向右下转动
#define ISMS_PTZ_AUTO                 29                    // 自动扫描
#define ISMS_PTZ_ZOOM_IN          11                    // 镜头拉近
#define ISMS_PTZ_ZOOM_OUT      12                    // 镜头拉远
#define ISMS_PTZ_FOCUS_NEAR    13                    // 焦点前移
#define ISMS_PTZ_FOCUS_FAR       14                    // 焦点后移
#define ISMS_PTZ_IRIS_OPEN         15                    // 光圈扩大
#define ISMS_PTZ_IRIS_CLOSE        16                    // 光圈缩小
#define ISMS_PTZ_GOTO_PRESET   39                    // 调用预置点
#define ISMS_PTZ_SEL_ZOOM        99                    // 电子放大
#define ISMS_PTZ_LOCK                 200                  // 云台锁定
#define ISMS_PTZ_UNLOCK            201                  // 云台解锁
#define ISMS_PTZ_UNLOCK_ALL    202                  // 解除所有能够解锁的锁定
#define ISMS_PTZ_LOCK_CHECK     203                  // 锁定检查

#define ISMS_PTZ_ACTION_START  0    // 云台开始
#define ISMS_PTZ_ACTION_STOP    1    // 云台结束

/////////////////////////////////////////// 视频解码帧类型定义 //////////////////////////////////////////////////

// 视频数据，uyvy格式。“U0-Y0-V0-Y1-U2-Y2-V2-Y3….”，第一个像素位于图像左上角
#define ISMS_FRAME_TYPE_UYVY      1 

// 视频数据，yv12格式，当前解码后的视频格式。排列顺序“Y0-Y1-……”，“V0-V1….”，“U0-U1-…..”
#define ISMS_FRAME_TYPE_YV12             3 

// 视频数据。每个像素4个字节，排列方式与位图相似，“B-G-R-0 …”，第一个像素位于图像左下角
#define ISMS_FRAME_TYPE_RGB32           7

// 音频数据;采样率16khz，单声道，每个采样点16位表示；具体以解码出的音频信息为准
#define ISMS_FRAME_TYPE_AUDIO16      101

//////////////////////////////////////////// 结构体定义////////////////////////////////////////////////////////////
// 分页请求结构体
typedef struct stPageReq
{
    int iPageNo;  //请求页码（从1开始）
    int iPageRows;  //每页条数
    __int64 iLastUpdateTime;   // 上次更新数据的最新时间，如果传入0，表示全量获取数据，如果大于0，表示增量获取数据
    stPageReq() : iPageNo(0), iPageRows(400), iLastUpdateTime(0)  // 建议400条每页
    {
    }
}ISMS_PAGE_REQ, *PISMS_PAGE_REQ;

// 分页请求响应结构体
typedef struct stPageRsp
{
    int iPageNo; //当前页码（从1开始）
    int iPageRows;  //每页条数
    int iTotalPage;  // 总页数
    int iRealRows;   //当前页码返回记录数（最后一页存记录不一定满页）
    __int64 iUpdateTime;     //本次数据更新时间
    stPageRsp() : iPageNo (1), iPageRows (400), iTotalPage(0), iRealRows(0), iUpdateTime(-1)
    {
    }
}ISMS_PAGE_RSP, *PISMS_PAGE_RSP;

// 控制中心结构体
typedef struct stCtrlUnit
{
    ISMS_UPDATE_TYPE_EN updateType;                //资源更新类型
    char szCtrlUnitUuid[MAX_COMMON_UUID_LENGTH]; //控制中心UUID
    char szCtrlUnitName[MAX_COMMON_NAME_LENGTH]; //控制中心名称
    char szParentCtrlUnitUuid[MAX_COMMON_UUID_LENGTH];  // 父控制中心UUID，为空字符串时表示根节点

    stCtrlUnit() : updateType(TYPE_UPDATE_UNKNOWN)
    {
        memset(szCtrlUnitUuid, 0, sizeof(szCtrlUnitUuid));
        memset(szCtrlUnitName, 0, sizeof(szCtrlUnitName));
        memset(szParentCtrlUnitUuid, 0, sizeof(szParentCtrlUnitUuid));
    }
}ISMS_CTRLUNIT, *PISMS_CTRLUNIT;

// 区域结构体
typedef struct stRegion
{
    ISMS_UPDATE_TYPE_EN updateType;                //资源更新类型
    char szRegionUuid[MAX_COMMON_UUID_LENGTH]; //区域UUID
    char szRegionName[MAX_COMMON_NAME_LENGTH]; //区域名称
    char szParentRegionUuid[MAX_COMMON_UUID_LENGTH]; //父区域UUID
    char szParentCtrlUnitUUid[MAX_COMMON_UUID_LENGTH]; //父控制中心UUID

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
    int iAnalogTalkChanSize;  // 模拟对讲通道数
    int iDigitalTalkChanSize;  // 数字对讲通道数
    ISMS_RESOURCE_STATUS_EN status;                // 设备状态
    ISMS_UPDATE_TYPE_EN updateType;                //资源更新类型
    char szDeviceUuid[MAX_COMMON_UUID_LENGTH]; // 设备UUID
    char szDeviceName[MAX_COMMON_NAME_LENGTH]; 
    ISMS_DEVICE_TYPE_EN enDevType;                         // 设备类型
    char szCtrlUnitUuid[MAX_COMMON_UUID_LENGTH]; // 控制中心UUID

    stDevice() : iAnalogTalkChanSize(0), iDigitalTalkChanSize(0), enDevType(DEVICE_TYPE_HIK), updateType(TYPE_UPDATE_UNKNOWN), status(RESOURCE_STATUS_UNKNOWN)
    {
        memset(szDeviceUuid, 0, sizeof(szDeviceUuid));
        memset(szDeviceName, 0, sizeof(szDeviceName));
        memset(szCtrlUnitUuid, 0, sizeof(szCtrlUnitUuid));
    }
}ISMS_DEVICE, *PISMS_DEVICE;

typedef struct stCamera
{
    int iChannelIndex; //在设备中所属通道号
    char szCameraUuid[MAX_COMMON_UUID_LENGTH]; //监控点UUID
    char szCameraName[MAX_COMMON_NAME_LENGTH]; //监控点名称
    ISMS_RESOURCE_STATUS_EN status;                //监控点状态
    ISMS_UPDATE_TYPE_EN updateType;                //资源更新类型
    char szDeviceUuid[MAX_COMMON_UUID_LENGTH]; //设备UUID
    char szRegionUuid[MAX_COMMON_UUID_LENGTH]; //区域UUID

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
    ISMS_RECORD_LOCATION_EN enLocation; //录像存储位置
    char szPlanUuid[MAX_COMMON_UUID_LENGTH]; //录像计划UUID
    char szPlanName[MAX_COMMON_NAME_LENGTH]; //录像计划名称

    stRecordPlan* pNext;
    stRecordPlan() : enLocation(LOCATION_UNKNOWN), pNext(NULL)
    {
        memset(szPlanUuid, 0, sizeof(szPlanUuid));
        memset(szPlanName, 0, sizeof(szPlanName));
    }
}ISMS_RECORD_PLAN, *PISMS_RECORD_PLAN;

// 录像片段结构体
typedef struct stRecordSection
{
    __int64 i64Start;  // 录像片段起点时间，单位：秒
    __int64 i64End;  // 录像片段起点时间，单位：秒
    ISMS_RECORD_TYPE_EN enSegRecType;    // 录像片段类型

    stRecordSection* pNext;
    stRecordSection() : i64Start(0), i64End(0), pNext(NULL), enSegRecType(RECORD_TYPE_UNKNOWN)
    {
    }
}ISMS_RECORD_SECTION, *PISMS_RECORD_SECTION;

// 预置点结构体
typedef struct stPreset
{
    int iPresetId;          // 预置点id
    char szName[MAX_COMMON_NAME_LENGTH]; //预置点名称
    stPreset* pNext;
    stPreset() : iPresetId(-1), pNext(NULL)
    {
        memset(szName, 0, sizeof(szName));
    }
}ISMS_PRESET_INFO, *PISMS_PRESET_INFO;

typedef struct stImageParam
{
    int iHue;      // 色调，取值范围：[1, 10]
    int iContrast;   // 对比度，取值范围：[1, 10]
    int iBright;    // 亮度，取值范围：[1, 10]
    int iSaturation; // 饱和度，取值范围：[1, 10]
    stImageParam () : iHue (0), iContrast (0), iBright(0), iSaturation(0)
    {
    } 
}ISMS_IMAGE_PARAM, *PISMS_IMAGE_PARAM;


// 事件结构体
typedef struct stEvent            
{
    ISMS_EVENT_TYPE_EN enEvtType;             // 事件类型
    ISMS_EVENT_LEVEL_EN enEvtLevel;           // 事件等级：1-高 2-中 3-低 4-普通
    ISMS_EVENT_STATUS_EN enEvtStatus;         //事件状态
    const char* pszAdditionInfo;                             // 事件附加信息，以XML报文形式给出，保留
    char szEventTime[MAX_COMMON_TIME_LENGTH];     //发生时间，例：2018-12-12 10:11:12
    char szSrcUuid[MAX_COMMON_UUID_LENGTH];        // 事件源编号
    char szSrcName[MAX_COMMON_NAME_LENGTH];      // 事件源名称
    char szEventUuid[MAX_COMMON_UUID_LENGTH];      // 事件编号
    char szEventName[MAX_COMMON_NAME_LENGTH];    // 事件名称
    char szDescripute[MAX_COMMON_DESCRIPUTE_LENGTH];         // 事件描述
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

// 数据变更结构体
typedef struct stDataChange
{
    ISMS_DATA_CHANGE_TYPE_EN enChangeType;          // 通知类型
    char szSubsystemUuid[MAX_COMMON_DATA_NAME];     // 子系统UUID
    char szChangeDataName[MAX_COMMON_DATA_NAME]; //变更数据名称，"controlunit":控制中心，"region":区域，"device":设备信息，"camera":监控点
    stDataChange() : enChangeType(DATA_CHANGE_TYPE_UNKNOWN)
    {
        memset(szSubsystemUuid, 0, sizeof(szSubsystemUuid));
        memset(szChangeDataName, 0, sizeof(szChangeDataName));
    }
}ISMS_DATA_CHANGE, *PISMS_DATA_CHANGE;

// 资源状态变更结构体
typedef struct stResourceStatusChange
{
    ISMS_RESOURCE_TYPE_EN enRsourceType;    // 资源类型，
    char szResourceUuid[MAX_COMMON_UUID_LENGTH]; //资源UUID
    ISMS_RESOURCE_STATUS_EN enResourceStatus; //资源状态，如设备上线，掉线，异常
    char szStatusDescription[MAX_COMMON_DESCRIPUTE_LENGTH];    // 状态描述

    stResourceStatusChange() : enRsourceType (RESOURCE_TYPE_UNKNOWN), enResourceStatus(RESOURCE_STATUS_UNKNOWN)
    {
        memset(szResourceUuid, 0, sizeof(szResourceUuid));
        memset(szStatusDescription, 0, sizeof(szStatusDescription));
    }
}ISMS_RESOURCE_STATUS_CHANGE, *PISMS_RESOURCE_STATUS_CHANGE;

// 视频详细信息
typedef struct stVideoDetailInfo
{
    int iPicWidth;                    // 图像宽度
    int iPicHeight;                   // 图像高度
    unsigned __int64 ui64FrameRate;      // 帧率
    stVideoDetailInfo() : iPicWidth(0), iPicHeight(0), ui64FrameRate(0)
    {
    }
}ISMS_VIDEO_DETAIL_INFO, *PISMS_VIDEO_DETAIL_INFO;

////////////////////////////////////////////////// 回调定义 /////////////////////////////////////////////////////////////////
/*
*	pfnEventCallback
*	接口说明：  事件监听地址
*	参数说明：
*                      pstEvent：监听到的事件
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall* pfnEventCallback)(PISMS_EVENT pstEvent, void* pUserData);

/*
*	pfnDataChangeCallback
*	接口说明：  数据变更监听地址
*	参数说明：
*                      pstDataNotify：监听到的数据变更信息
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall* pfnDataChangeCallback)( PISMS_DATA_CHANGE pstDataNotify, void* pUserData);

/*
*	pfnResourceStatusCallback
*	接口说明：  资源状态变更监听地址
*	参数说明：
*                      pstResourceStatus：监听到的资源状态变更信息
*                      iResNum：资源个数
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall* pfnResourceStatusCallback)(PISMS_RESOURCE_STATUS_CHANGE pstResourceStatus, int iResNum, void* pUserData);

/*
*	pfnStreamCallback
*	接口说明：  码流回调地址
*	参数说明：
*                      lPlayHnadle：预览句柄
*                      enStreamType：用户数据
*                      pDataArray：码流数据（非字符串，需当成二进制数组来使用）
*                      iDataLen：码流数据长度
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall *pfnStreamCallback)(long lPlayHnadle, ISMS_STREAM_DATA_TYPE_EN enStreamDataType, const char* pDataArray, int iDataLen, void* pUserData);

/*
*	pfnProgressCallback
*	接口说明：  录像下载进度回调地址
*	参数说明：
*                      lDownloadHandle：录像下载句柄
*                      fPercent：录像下载进度
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall *pfnProgressCallback)(long lDownloadHandle, float fPercent, void* pUserData);

/*
*	pfnPlayMsgCallback
*	接口说明：  播放消息回调，可用于预览、回放
*	参数说明：
*                      lPlayHandle：录像下载句柄
*                      iMsg：播放消息，1-播放开始 2-播放结束 3-播放暂停 4-恢复播放 5-播放停止
*                      pUserData：用户数据
*	返回值：      
*/
typedef void (__stdcall *pfnPlayMsgCallback)(long lPlayHandle, int iMsg, void* pUserData);

/*
 *	pfnDecodedDataCallback
 *	接口说明：视频解码后数据回调，可用于预览、回放
 * 参数说明：
 *                  lPlayHandle： 播放句柄
 *	                 pDataArray ：解码后的数据（非字符串，需当成二进制数组来使用）
 *	                 iDataLen： 数据长度
 *	                 iWidth： 图像宽度，单位：像素，如果帧类型是音频，则为音频声道数
 *                  iHeight：图像高度，单位：像素，如果帧类型是音频，则为样位率
 *                  iFrameType：图像yuv类型，取值详见ISMS_FRAME_TYPE_*
 *                  iTimeStamp：时间戳
 *	                 pUserData： 用户自定义数据
 */
typedef void (__stdcall* pfnDecodedDataCallback)(long lPlayHandle, const char* pDataArray, int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData);