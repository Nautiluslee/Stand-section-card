#ifndef _H_IPC_USOCKET_H_
#define _H_IPC_USOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


#ifdef __cplusplus
extern "C"{
#endif

#define USOCKET_MSG_MAXLEN 180 //从100改到180，站节牌数据包长为接近160个字节
#define USOCKET_DATABUF_MAXLEN 80

#define USOCKET_DATA_WUHU_MAX 160
typedef struct UCSocket
{
    int is_serv_fd; /* client 使用的socket fd是不是本进程的server  socket fd。FALSE 表示不是，TRUE 表示是*/
    int socketfd;
    struct sockaddr_un address;
    
    int has_send_msg; /* 是否有需要发送的消息, FALSE 表示没有，TRUE 表示有*/
    unsigned char send_msg[USOCKET_MSG_MAXLEN];
    int send_len;
    
}UCSocket;

typedef struct UCSocket * UCsock_handle;

typedef struct USSocket
{
    int socketfd;
    struct sockaddr_un address;
    
    int has_recv_msg; /* 是否有接收到的消息, FALSE 表示没有，TRUE 表示有*/
    unsigned char recv_msg[USOCKET_MSG_MAXLEN];
    int recv_len;

    
}USSocket;

typedef struct USSocket * USsock_handle;


typedef struct IPC_USOCKSet
{
   
    USsock_handle hServS;
    
    UCsock_handle hClientBzS;
    UCsock_handle hClientInterfaceS;
    UCsock_handle hClientSysS;
    UCsock_handle hClientGprsS;
    UCsock_handle hClientWifiS;
    UCsock_handle hClientExtbzS;
    UCsock_handle hClientAvS;    
    UCsock_handle hClientStS;    
    UCsock_handle hClientKeypadS;    
    UCsock_handle hClientGpsS;  
    UCsock_handle hClientMcumsgS;
    UCsock_handle hClientBusdataS;
    UCsock_handle hClientDirectWifiS;
}IPC_USOCKSet;

typedef struct IPC_USOCKSet * IPC_USOCKSet_handle;

////////////////////////////////////////////////////////////////////
typedef enum US_PROCESS_ID
{
    ST_PROCESS = 0,
    AV_PROCESS,   
    KEYPAD_PROCESS,   
    SYS_PROCESS,
    BZ_PROCESS,
    LOG_PROCESS,
    WIFI_PROCESS,
    GPRS_PROCESS,
    GPS_PROCESS,
    RECORD_PROCESS,
    LIVE_PROCESS,
    INTERFACE_PROCESS,
    EXTBZ_PROCESS, 
    MCUMSG_PROCESS,
    BUSDATA_PROCESS,
    DIRECTWIFI_PROCESS,
    AUTOTEST_PROCESS
}US_PROCESS_ID;

typedef enum US_MSG_TYPE
{
    MSG_CMD =0,
    MSG_DATA  
}US_MSG_TYPE;


/* unix socket 公共消息头格式 */
typedef struct UsockMsgHeader
{
    US_PROCESS_ID source; /* 消息源进程 */
    US_PROCESS_ID dest; /* 消息目的进程 */
    US_MSG_TYPE     msg_type; /* 消息类型 */ 
}UsockMsgHeader;


typedef enum AV_STATE
{
    AV_IDLE = 0,
    AV_ERROR,
    AV_ENC,
    AV_DEC,
    V_LOOP,
    V_ENC,
    V_DEC,
    I_ENC,
    I_DEC,
    A_DEC,
    AV_GJ_MODE,
    AV_NULL,
}AV_STATE;

typedef enum AV_CODEC_ID
{
    CODEC_H264 = 0,
    CODEC_MPEG4,
    CODEC_MPEG2,
    CODEC_G711,
    CODEC_MSADPCM,
    CODEC_JPEG
}AV_CODEC_ID;



////####################################################////
//////////////////////////ST2AV/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum ST2AV_CMD_ID
{
    ST2AV_AV_ENC_STOP = 0,
    ST2AV_AV_DEC_STOP,
    ST2AV_AV_ENC_START,
    ST2AV_AV_DEC_START,
    ST2AV_V_LOOP_START,
    ST2AV_V_LOOP_STOP,
    ST2AV_V_ENC_START,
    ST2AV_V_ENC_STOP,
    ST2AV_V_DEC_START,
    ST2AV_V_DEC_STOP,
    ST2AV_I_ENC_START,
    ST2AV_I_ENC_STOP,
    ST2AV_I_DEC_START,
    ST2AV_I_DEC_STOP,
    ST2AV_A_DEC_START,
    ST2AV_A_DEC_STOP,
    ST2AV_AV_GJ_MODE_START,
    ST2AV_AV_GJ_MODE_STOP
}ST2AV_CMD_ID;

typedef struct UsockMsg_ST2AV_CMD
{
    ST2AV_CMD_ID st2av_cmd_id;  
    int has_video; 
    int has_speech; 
    int has_audio;
    int has_image;
    AV_CODEC_ID V_CODEC_ID;
    AV_CODEC_ID A_CODEC_ID;
    AV_CODEC_ID S_CODEC_ID;
    AV_CODEC_ID I_CODEC_ID;
    int v_target_bitrate;
    int i_target_bitrate;
    int v_resolution;
    int i_resolution;

}UsockMsg_ST2AV_CMD;



//////////////////////////MCUMSG2INTERFACE//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Mcumsg2Interface_CMD_ID
{
    MCUMSG_IR = 0,
    MCUMSG_WUHU
}Mcumsg2Interface_CMD_ID;

typedef struct UsockMsg_MCUMSG2INTERFACE_CMD
{
    Mcumsg2Interface_CMD_ID mcumsg2interface_cmd_id;  
    int buf[USOCKET_DATA_WUHU_MAX/4];
    
}UsockMsg_MCUMSG2INTERFACE_CMD;

//////////////////////////MCUMSG2GPS//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Mcumsg2Gps_CMD_ID
{
    MCUMSG2GPS_GPS_GPRMC = 0,
}Mcumsg2Gps_CMD_ID;

typedef struct UsockMsg_MCUMSG2GPS_CMD
{
    Mcumsg2Gps_CMD_ID mcumsg2gps_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_MCUMSG2GPS_CMD;

//////////////////////////MCUMSG2BUSDATA//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Mcumsg2Busdata_CMD_ID
{
    MCUMSG2BUSDATA_GPS_GPRMC = 0,
    MCUMSG2BUSDATA_ACCEL_DATA,
}Mcumsg2Busdata_CMD_ID;

typedef struct UsockMsg_MCUMSG2BUSDATA_CMD
{
    Mcumsg2Busdata_CMD_ID mcumsg2busdata_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_MCUMSG2BUSDATA_CMD;

///////////////////////// MCUMSG2KEYPAD  /////////////////////////////////
////////////////////////////////////////////////////////////////////////


//////////////////////////MCUMSG2KEYPAD//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Mcumsg2Keypad_CMD_ID
{
    MCUMSG2KEYPAD_SPEAKER_INFO = 0,
    MCUMSG2KEYPAD_TURNING_STATE,
    MCUMSG2KEYPAD_BRAKE_STATE,
    MCUMSG2KEYPAD_TURNING_LEDMSG_STATE,
    MCUMSG2KRYPAD_WUHU_SHOWPIC_STATE
}Mcumsg2Keypad_CMD_ID;

typedef struct UsockMsg_MCUMSG2KEYPAD_CMD
{
    Mcumsg2Keypad_CMD_ID mcumsg2keypad_cmd_id;  
    int buf[2*USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_MCUMSG2KEYPAD_CMD;

////####################################################////
//////////////////////////EXTBZ2KEYPAD//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Extbz2Keypad_CMD_ID
{
    EXT_BZ = 0,
}Extbz2Keypad_CMD_ID;

typedef struct UsockMsg_EXTBZ2KEYPAD_CMD
{
    Extbz2Keypad_CMD_ID extbz2keypad_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_EXTBZ2KEYPAD_CMD;

////####################################################////
//////////////////////////INTERFACE2SYS//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Interface2Sys_CMD_ID
{
    INTERFACE2SYS_DO_RESTORE = 0,
}Interface2Sys_CMD_ID;

typedef struct UsockMsg_INTERFACE2SYS_CMD
{
    Interface2Sys_CMD_ID interface2sys_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_INTERFACE2SYS_CMD;


//////////////////////////INTERFACE2WIFI//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Interface2Wifi_CMD_ID
{
    INTERFACE2WIFI_START_CHECK_WIFI_QUALITY = 0,
    INTERFACE2WIFI_STOP_CHECK_WIFI_QUALITY,
    INTERFACE2WIFI_START_WIFI_PUBLIC_ACCESS,
    INTERFACE2WIFI_STOP_WIFI_PUBLIC_ACCESS,
}Interface2Wifi_CMD_ID;

typedef struct UsockMsg_INTERFACE2WIFI_CMD
{
    Interface2Wifi_CMD_ID interface2wifi_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_INTERFACE2WIFI_CMD;

//////////////////////////INTERFACE2GPS//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Interface2Gps_CMD_ID
{
    INTERFACE2GPS_START_CHECK_GPS_QUALITY = 0,
    INTERFACE2GPS_STOP_CHECK_GPS_QUALITY,
}Interface2Gps_CMD_ID;

typedef struct UsockMsg_INTERFACE2GPS_CMD
{
    Interface2Gps_CMD_ID interface2gps_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_INTERFACE2GPS_CMD;


//////////////////////////INTERFACE2BZ//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Interface2Bz_CMD_ID
{
    INTERFACE2BZ_CHECK_AUTOBZ_TEST_STATE = 0,
}Interface2Bz_CMD_ID;

typedef struct UsockMsg_INTERFACE2BZ_CMD
{
    Interface2Bz_CMD_ID interface2bz_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_INTERFACE2BZ_CMD;


////####################################################////
//////////////////////////BZ2INTERFACE//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Bz2Interface_CMD_ID
{
    BZ2INTERFACE_SHOW_BZ_IMG = 0,
    BZ2INTERFACE_HIDE_BZ_IMG
}Bz2Interface_CMD_ID;

typedef struct UsockMsg_BZ2INTERFACE_CMD
{
    Bz2Interface_CMD_ID bz2interface_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_BZ2INTERFACE_CMD;

//////////////////////////BZ2MCUMSG//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Bz2Mcumsg_CMD_ID
{
    BZ2MCUMSG_LED_TEXT_MSG = 0,
    BZ2MCUMSG_ZJP_LED_MSG 
}Bz2Mcumsg_CMD_ID;

typedef struct UsockMsg_BZ2MCUMSG_CMD
{
    Bz2Mcumsg_CMD_ID bz2mcumsg_cmd_id;  
    int buf[2*USOCKET_DATABUF_MAXLEN/4]; //站节牌最大接近160个字节
    
}UsockMsg_BZ2MCUMSG_CMD;

////####################################################////
//////////////////////////ST2INTERFACE//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum St2Interface_CMD_ID
{
    ST2INTERFACE_SHOW_SUB_IMG = 0,
    ST2INTERFACE_HIDE_SUB_IMG,
    ST2INTERFACE_ADD_ADS_TEXT
}St2Interface_CMD_ID;

typedef struct UsockMsg_ST2INTERFACE_CMD
{
    St2Interface_CMD_ID st2interface_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_ST2INTERFACE_CMD;

//////////////////////////ST2GPRS//////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum St2Gprs_CMD_ID
{
    ST2GPRS_PLAYINGLOG = 0,
}St2Gprs_CMD_ID;

typedef struct UsockMsg_ST2GPRS_CMD
{
    St2Gprs_CMD_ID st2gprs_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_ST2GPRS_CMD;

////####################################################////
//////////////////////////WIFI2SYS//////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Wifi2Sys_CMD_ID
{
    WIFI2SYS_CONNECT_FAILURE = 0,
    WIFI2SYS_NO_USEFUAL_APS,        
    WIFI2SYS_UPDATE_OK,
    WIFI2SYS_UPDATE_SLEEP,
    WIFI2SYS_UPDATE_SW_START,
    WIFI2SYS_RESET_SYSTEM,
    WIFI2SYS_MOD_PARAMS,

}Wifi2Sys_CMD_ID;

typedef struct UsockMsg_WIFI2SYS_CMD
{
    Wifi2Sys_CMD_ID wifi2sys_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_WIFI2SYS_CMD;

//////////////////////////WIFI2ST//////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef enum DWifi2St_CMD_ID
{
    WIFI2ST_NEW_PLAYERLIST = 0,
    
}Wifi2St_CMD_ID;

typedef struct UsockMsg_WIFI2ST_CMD
{
    Wifi2St_CMD_ID wifi2st_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_WIFI2ST_CMD;

////####################################################////
//////////////////////////GPS2GPRS//////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef struct Usock_GPS_INFO
{
    double latitude;/*纬度数据 */
    double longitude;/*经度数据*/
    unsigned char east_or_west;/*精度标志[1][2]：1代表东经，2代表西经*/
    unsigned char south_or_north;/*纬度标志[1][2]：1代表南 纬，2代表北纬*/
    float speed;
    float direction;

}Usock_GPS_INFO;

typedef struct Usock_BZGPS_INFO
{
    double latitude;/*纬度数据 */
    double longitude;/*经度数据*/
    unsigned char east_or_west;/*精度标志[1][2]：1代表东经，2代表西经*/
    unsigned char south_or_north;/*纬度标志[1][2]：1代表南 纬，2代表北纬*/
    float speed;
    float direction;
    int station; /* 报站站点，取值范围0-99 */
    char down_up; /* 上/下行标志0表示下行，1表示上行 */
    char in_out; /* 进/出站表示，1表示进站，2表示出站 */
    
}Usock_BZGPS_INFO;

typedef enum Gps2Gprs_CMD_ID
{
    GPS2GPRS_GPS_DATA = 0,
    GPS2GPRS_BZGPS_DATA,
}Gps2Gprs_CMD_ID;

typedef struct UsockMsg_GPS2GPRS_CMD
{
    Gps2Gprs_CMD_ID gps2gprs_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPS2GPRS_CMD;

//////////////////////////GPS2ST//////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Gps2St_CMD_ID
{
    GPS2ST_GPS_DATA = 0,
}Gps2St_CMD_ID;

typedef struct UsockMsg_GPS2ST_CMD
{
    Gps2St_CMD_ID gps2st_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPS2ST_CMD;

//////////////////////////GPS2KEYPAD//////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef enum GPS2KEYPAD_GPS_STATE
{
    GPS_RECORD_DATA_BEGIN = 0, /*GPS发送给按键通知其坐标采集开始，数码管显示RS00*/
    GPS_RECORD_DATA_END, /*GPS发送给按键通知其坐标采集结束，数码管显示RE00*/
    GPS_RECORD_DATA_SUCCESS, /*本次站点坐标采集成功LIGHT0连亮两下*/
    GPS_SINGAL_GOOD,
    GPS_SINGAL_BAD
    
}GPS2KEYPAD_GPS_STATE;

#define KP2GPS_STOP_ATUOBZ 0X06 /*按键发送给GPS，暂时关闭GPS自动报站功能*/

typedef enum Gps2Keypad_CMD_ID
{
    GPS2KEYPAD_AUTO_SPEECH_BZ = 0,
    GPS2KEYPAD_AUTO_SERVICE_BZ,
    GPS2KEYPAD_GPS_STATE_INFO,    
    GPS2KEYPAD_TURN_SPEECH_BZ,
}Gps2Keypad_CMD_ID;

typedef struct UsockMsg_GPS2KEYPAD_CMD
{
    Gps2Keypad_CMD_ID gps2keypad_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4]; /* 确保为4字节对齐 */
    
}UsockMsg_GPS2KEYPAD_CMD;

typedef enum BUS_RUNNING_STATE_E
{
    RUNNING_ON_ROAD = 0,/*非转弯播报的GPS区域*/
    RUNNING_IN_STATION,/*在进站GPS区域*/
    RUNNING_OUT_STATION,/*在出站GPS区域*/
    RUNNING_AREA_PREV,/*转弯播报的GPS区域外部播报点*/
    RUNNING_AREA_START,/*转弯播报的GPS区域开始点*/
    RUNNING_AREA_STOP,/*转弯播报的GPS区域结束*/
}BUS_RUNNING_STATE_E;


////####################################################////
//////////////////////////GPRS2SYS//////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum Gprs2Sys_CMD_ID
{
    GPRS2SYS_ERROR_DIAL_FAILURE = 0,
    GPRS2SYS_ERROR_CREATUSOCK_FAILURE,
    GPRS2SYS_AUDIO_SET,
    GPRS2SYS_SYSTIME_SET,
    GPRS2SYS_MOD_PARAMS,
}Gprs2Sys_CMD_ID;

typedef struct AUDIO_SET
{
    int channel; /* 0 车外报站，1车内报站，2广告音频 */
    int inc_dec; /* 0 减少，1增加 */
}AUDIO_SET;

typedef struct UsockMsg_GPRS2SYS_CMD
{
    Gprs2Sys_CMD_ID gprs2sys_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPRS2SYS_CMD;

//////////////////////////GPRS2BZ/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Gprs2Bz_CMD_ID
{
    GPRS2BZ_ADS_TEXT_IFNO = 0,
}Gprs2Bz_CMD_ID;

typedef struct UsockMsg_GPRS2BZ_CMD
{
    Gprs2Bz_CMD_ID gprs2bz_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPRS2BZ_CMD;

//////////////////////////GPRS2KEYPAD/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Gprs2Keypad_CMD_ID
{
    WARNING_WARN_SEND_OK = 0,
    TV_WARN_SEND_OK,
    WARNING_WARN_SEND_FAILURE,
    TV_WARN_SEND_FAILURE,

}Gprs2Keypad_CMD_ID;

typedef struct UsockMsg_GPRS2KEYPAD_CMD
{
    Gprs2Keypad_CMD_ID gprs2keypad_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPRS2KEYPAD_CMD;

//////////////////////////GPRS2ST/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Gprs2St_CMD_ID
{
    GPRS2ST_AV_DEC_STOP = 0,
    GPRS2ST_AV_DEC_START,
    GPRS2ST_PLAY_NOW_A_AVI, 
    GPRS2ST_START_PLAYINGLOG, 
    GPRS2ST_STOP_PLAYINGLOG, 
    
}Gprs2St_CMD_ID;

typedef struct UsockMsg_GPRS2ST_CMD
{
    Gprs2St_CMD_ID gprs_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];

}UsockMsg_GPRS2ST_CMD;


//////////////////////////GPRS2GPS/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Gprs2Gps_CMD_ID
{
    GPRS2GPS_NEED_GPS_DATA = 0,
}Gprs2Gps_CMD_ID;

typedef struct UsockMsg_GPRS2GPS_CMD
{
    Gprs2Gps_CMD_ID gprs2gps_cmd_id;  

}UsockMsg_GPRS2GPS_CMD;

//////////////////////////GPRS2INTERFACE/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Gprs2Interface_CMD_ID
{
    GPRS2INTERFACE_ADD_ADS_TEXT = 0, 
}Gprs2Interface_CMD_ID;

typedef struct UsockMsg_GPRS2INTERFACE_CMD
{
    Gprs2Interface_CMD_ID gprs2interface_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_GPRS2INTERFACE_CMD;



////####################################################////
//////////////////////////KEYPAD2BZ/////////////////////////////////////
////////////////////////////////////////////////////////////////////////
typedef enum KeyPad2BZ_CMD_ID
{
    KEYPAD2BZ_BZMP3_START = 0,
    KEYPAD2BZ_BZMP3_STOP,
    KEYPAD2BZ_BZOSD_START,
    KEYPAD2BZ_BZOSD_STOP,
    KEYPAD2BZ_VOLUME_OUT_SET,
    KEYPAD2BZ_TURNINGMP3_START,
    KEYPAD2BZ_TURNINGMP3_STOP,
    KEYPAD2BZ_BZTTS_START,
    KEYPAD2BZ_BZTTS_STOP,
    KEYPAD2BZ_TURNINGTTS_START,
    KEYPAD2BZ_TURNINGTTS_STOP,
    KEYPAD2BZ_BRAKE_START,
    KEYPAD2BZ_BRAKE_STOP,
    KEYPAD2BZ_TURNING_LED_START,
    KEYPAD2BZ_TURNING_LED_STOP,
    KEYPAD2BZ_CHANGE_ROAD,
    KEYPAD2BZ_NUMEND,


    KEYPAD2BZ_WUHU_SHOWPIC_START = 0x81,

}KeyPad2BZ_CMD_ID;

typedef enum TURNING_TYPE_E
{
    TURNING_NULL = 0,
    TURNING_LEFT,
    TURNING_RIGHT,
    TURNING_PREV,
    TURNING_ON_ROAD,
    TURNING_IN,
    TURNING_OUT,
    TURNING_LEFT_LEDMSG,
    TURNING_RIGHT_LEDMSG,

}TURNING_TYPE_E;

typedef enum VOLUME_OUT_TYPE
{
	AV_VOL = 0,
	BZ_IN_VOL,
	BZ_OUT_VOL,
	ALL_VOL
		
}VOLUME_OUT_TYPE;

typedef struct UsockMsg_KEYPAD2BZ_CMD
{
    KeyPad2BZ_CMD_ID keypad_cmd_id;  /* KEY 进程发送给st 进程的命令字*/

    /*报站相关*/
    int osd_enable; /* 是否需要进行图片报站 */
    int bz_type; /* 报站语音类型, 0 表示报站语音，1表示服务语音 */    
    int roadline; /* 线路，取值范围1-3 */
    int station; /* 报站站点，取值范围0-99 */
    int down_up; /* 上/下行标志0表示下行，1表示上行 */
    int in_out; /* 进/出站表示，1表示进站，2表示出站 */
    int serv_num; /* 服务用语编号 ，取值范围1-3*/
    TURNING_TYPE_E TurningType;
    VOLUME_OUT_TYPE volume_out_set_type; /* 0: 广告音频，1：车内报站音频，2：车外报站音频，3：调整所有的声道 */
    int volume; /* 有效取值范围为0到80，值越大声音也越大 */
    
}UsockMsg_KEYPAD2BZ_CMD;

//////////////////////////KEYPAD2GPRS//////////////////////////////////
///////////////////////////////////////////////////////////////////////


typedef enum KeyPad2Gprs_CMD_ID
{
    KEYPAD2GPRS_GPS_INFO = 0,
    KEYPAD2GPRS_MANNUL_WARNING

}KeyPad2Gprs_CMD_ID;

typedef struct UsockMsg_KEYPAD2GPRS_CMD
{
    KeyPad2Gprs_CMD_ID keypad2gprs_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_KEYPAD2GPRS_CMD;


//////////////////////////KEYPAD2INTERFACE/////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum KeyPad2Interface_CMD_ID
{
    KEYPAD2INTERFACE_KEY = 0,
    KEYPAD2INTERFACE_IR_KEY,

}KeyPad2Interface_CMD_ID;

typedef struct UsockMsg_KEYPAD2INTERFACE_CMD
{
    KeyPad2Interface_CMD_ID keypad2interface_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];

}UsockMsg_KEYPAD2INTERFACE_CMD;

//////////////////////////KEYPAD2SYS/////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum KeyPad2Sys_CMD_ID
{
    KEYPAD2SYS_MANNUL_WARNING = 0,

}KeyPad2Sys_CMD_ID;

typedef struct UsockMsg_KEYPAD2SYS_CMD
{
    KeyPad2Sys_CMD_ID keypad2sys_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];

}UsockMsg_KEYPAD2SYS_CMD;

//////////////////////////KEYPAD2GPS/////////////////////////////
///////////////////////////////////////////////////////////////////////

typedef struct KEYPAD_INFO
{
    int is_reset;/*是否复位*/
    int bz_type;/*服务类型*/
    int roadline; /* 线路，取值范围1-3 */
    int station; /* 报站站点，取值范围0-99 */
    int down_up; /* 上/下行标志0表示下行，1表示上行 */
    int in_out; /* 进/出站表示，1表示进站，2表示出站 */
    int server_num;/*服务语音*/
    
}KEYPAD_INFO;

typedef enum KeyPad2Gps_CMD_ID
{
    KEYPAD2GPS_KEYPAD_INFO = 0,
    KEYPAD2GPS_SET_LINE_NUMBER,
    KEYPAD2GPS_SET_DOWNUP,
}KeyPad2Gps_CMD_ID;

typedef struct UsockMsg_KEYPAD2GPS_CMD
{
    KeyPad2Gps_CMD_ID keypad2gps_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];

}UsockMsg_KEYPAD2GPS_CMD;

//////////////////////////KEYPAD2MCUMSG/////////////////////////////
///////////////////////////////////////////////////////////////////////

typedef enum Keypad2Mcumsg_CMD_ID
{
    KEYPAD2MCUMSG_SPEAKER_INFO = 0,
}Keypad2Mcumsg_CMD_ID;

typedef struct UsockMsg_KEYPAD2MCUMSG_CMD
{
    Keypad2Mcumsg_CMD_ID keypad2mcumsg_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
    
}UsockMsg_KEYPAD2MCUMSG_CMD;


////####################################################///
//////////////////////////SYS2MCUMSG/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Mcumsg_CMD_ID
{
    SYS2MSCMUSG_SET_RTC = 0,
    SYS2MSCMUSG_POWERDOWN,
    SYS2MSCMUSG_POWERSLEEP,
    SYS2MSCMUSG_MONITORMODE,
    

}Sys2Mcumsg_CMD_ID;

typedef struct UsockMsg_SYS2MCUMSG_CMD
{
    Sys2Mcumsg_CMD_ID sys2mcumsg_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2MCUMSG_CMD;

//////////////////////////SYS2ST/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2St_CMD_ID
{
    SYS2ST_EXIT = 0,

}Sys2St_CMD_ID;

typedef struct UsockMsg_SYS2ST_CMD
{
    Sys2St_CMD_ID sys2st_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2ST_CMD;

//////////////////////////SYS2GPRS/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Gprs_CMD_ID
{
    SYS2GPRS_DEVICE_INFO = 0,
    SYS2GPRS_EXIT,
    SYS2GPRS_PARAMS_UPDATE_OK,
    SYS2GPRS_PARAMS_UPDATE_FAILUE,

}Sys2Gprs_CMD_ID;

typedef struct UsockMsg_SYS2GPRS_CMD
{
    Sys2Gprs_CMD_ID sys2gprs_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2GPRS_CMD;


//////////////////////////SYS2WIFI//////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Wifi_CMD_ID
{
    SYS2WIFI_DEVICE_INFO = 0,
    SYS2WIFI_KEY_CLOSED,
    SYS2WIFI_EXIT,
    SYS2WIFI_UPDATE_SW_DONE,

}Sys2Wifi_CMD_ID;

typedef struct UsockMsg_SYS2WIFI_CMD
{
    Sys2Wifi_CMD_ID sys2wifi_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2WIFI_CMD;

//////////////////////////SYS2DIRECTWIFI//////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2DirectWifi_CMD_ID
{
    SYS2DIRECTWIFI_KEY_CLOSED = 0,

}Sys2DirectWifi_CMD_ID;

typedef struct UsockMsg_SYS2DIRECTWIFI_CMD
{
    Sys2DirectWifi_CMD_ID sys2directwifi_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2DIRECTWIFI_CMD;


//////////////////////////SYS2BUSDATA//////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Busdata_CMD_ID
{
    SYS2BUSDATA_KEY_CLOSED = 0,
    SYS2BUSDATA_EXIT,
}Sys2Busdata_CMD_ID;

typedef struct UsockMsg_SYS2BUSDATA_CMD
{
    Sys2Busdata_CMD_ID sys2busdata_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2BUSDATA_CMD;


//////////////////////////SYS2GPS/////////////////    /////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Gps_CMD_ID
{
    SYS2GPS_GPS_SLEEP = 0,
    SYS2GPS_GPS_WAKEUP,

}Sys2Gps_CMD_ID;

typedef struct UsockMsg_SYS2GPS_CMD
{
    Sys2Gps_CMD_ID sys2gps_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2GPS_CMD;

//////////////////////////SYS2INTERFACE//////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum Sys2Interface_CMD_ID
{
    SYS2INTERFACE_IR_CODE = 0,
    SYS2INTERFACE_SD_STATE_NO,
    SYS2INTERFACE_SD_STATE_OK,
    SYS2INTERFACE_REBOOT_SYS,
}Sys2Interface_CMD_ID;

typedef struct UsockMsg_SYS2INTERFACE_CMD
{
    Sys2Interface_CMD_ID sys2interface_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_SYS2INTERFACE_CMD;

////####################################################////
//////////////////////////AUTOTEST/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum AUTOTEST2KEYPAD_CMD_ID
{
    /* FOR KEYPAD INTERFACE */
    KEYPAD_KEY_BZ = 0,
    KEYPAD_KEY_REPEAT,
    KEYPAD_KEY_SERV_1,
    KEYPAD_KEY_SERV_2,
    KEYPAD_KEY_SERV_3,
}AUTOTEST2KEYPAD_CMD_ID;

typedef enum AUTOTEST2GPRS_CMD_ID
{
   /* FOR GPRS INTERFACE */
    GPRS_INC_OUTBZ_AUDIO = 0,
    GPRS_DEC_OUTBZ_AUDIO,
    GPRS_INC_INBZ_AUDIO,
    GPRS_DEC_INBZ_AUDIO,  
    GPRS_INC_AV_AUDIO,
    GPRS_DEC_AV_AUDIO,
    GPRS_SET_SYSTIME,
    GPRS_ADD_ADS_TEXT,
    GPRS_PLAY_NOW_A_AVI,
    GPRS_CMD_NUM
}AUTOTEST2GPRS_CMD_ID;


typedef struct UsockMsg_AUTOTEST2ANY_CMD
{
    int autotest2any_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
   
    
}UsockMsg_AUTOTEST2ANY_CMD;


////####################################################///
//////////////////////////DIRECTWIFI2ST/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef enum DirectWifi2St_CMD_ID
{
    DIRECTWIFI2ST_NEW_PLAYERLIST = 0,
    
}DirectWifi2St_CMD_ID;

typedef struct UsockMsg_DIRECTWIFI2ST_CMD
{
    DirectWifi2St_CMD_ID directwifi2st_cmd_id;  
    int buf[USOCKET_DATABUF_MAXLEN/4];
}UsockMsg_DIRECTWIFI2ST_CMD;



////####################################################////
//////////////////////////ANY2LOG///////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#define MAX_LOG_LEN 80
typedef enum ANY2LOG_CMD_ID
{
    ANY2LOG_WARNING_INFO = 0,
    ANY2LOG_ERROR_INFO,        
    ANY2LOG_STATIC_PARAM_MOD_INFO,      
}ANY2LOG_CMD_ID;

typedef struct UsockMsg_ANY2LOG_CMD
{
    ANY2LOG_CMD_ID any2log_cmd_id;
    US_PROCESS_ID process_id; /* 发出log信息的进程名称*/
    char log_info[MAX_LOG_LEN];
}UsockMsg_ANY2LOG_CMD;



////####################################################////
////////////////////////////////////////////////////////////////////////
//  FOR RECORD PART
//
////////////////////////////////////////////////////////////////////
typedef enum RECORD2AV_CMD_ID
{
    RECORD2AV_AV_ENC_STOP = 0,
    RECORD2AV_AV_ENC_START,
    RECORD2AV_V_LOOP_START,
    RECORD2AV_V_LOOP_STOP,
    RECORD2AV_V_ENC_START,
    RECORD2AV_V_ENC_STOP,
    RECORD2AV_I_ENC_START,
    RECORD2AV_I_ENC_STOP,
    RECORD2AV_V_4CIF_START,
    RECORD2AV_V_4CIF_STOP
}RECORD2AV_CMD_ID;

typedef struct UsockMsg_RECORD2AV_CMD
{
    RECORD2AV_CMD_ID record2av_cmd_id;  
    int has_video; 
    int has_speech; 
    int has_audio;
    int has_image;
    AV_CODEC_ID V_CODEC_ID;
    AV_CODEC_ID A_CODEC_ID;
    AV_CODEC_ID S_CODEC_ID;
    AV_CODEC_ID I_CODEC_ID;
    int v_target_bitrate;
    int i_target_bitrate;
    int v_resolution;
    int i_resolution;

}UsockMsg_RECORD2AV_CMD;


////////////////////////////////////////////////////////////////////
typedef enum LIVE2RECORD_CMD_ID
{
    LIVE2RECORD_AV_ENC_START = 0,
    LIVE2RECORD_AV_ENC_STOP,
    LIVE2RECORD_V_ENC_START,
    LIVE2RECORD_V_ENC_STOP,
    LIVE2RECORD_I_ENC_START,
    LIVE2RECORD_I_ENC_STOP,
    LIVE2RECORD_V_4CIF_START,
    LIVE2RECORD_V_4CIF_STOP
}LIVE2RECORD_CMD_ID;

typedef struct UsockMsg_LIVE2RECORD_CMD
{
    LIVE2RECORD_CMD_ID live_cmd_id;  
    int has_video; 
    int has_speech; 
    int has_audio;
    int has_image;
    AV_CODEC_ID V_CODEC_ID;
    AV_CODEC_ID A_CODEC_ID;
    AV_CODEC_ID S_CODEC_ID;
    AV_CODEC_ID I_CODEC_ID;
    int v_target_bitrate;
    int i_target_bitrate;
    int v_resolution;
    int i_resolution;

}UsockMsg_LIVE2RECORD_CMD;

////////////////////////////////////////////////////////////////////
typedef struct UsockMsg_AV2ST_CMD
{
    AV_STATE av_state;  /* encodedecode 进程工作状态*/
    int heart; /* encodedecode 进程心跳 */
    int error_no; /*  encodedecode 进程错误状态*/

}UsockMsg_AV2ST_CMD;



USsock_handle CreateUServSocket(const char * ServerName);

void DeleteUServSocket(USsock_handle Hus);

UCsock_handle CreateUClientSocket(const char * ClientName, int servsocketfd);

void DeleteUClientSocket(UCsock_handle Hus);

int SendMsgByUClientsocket(UCsock_handle Hus);

int SendMsgByUClientsocketNoblock(UCsock_handle Hus);

int ReadMsgByUServsocket(USsock_handle Hus, struct timeval * timeout);

int ReadUnixMsg(USsock_handle Hus);

int PackMsgForSend(UCsock_handle Hus, UsockMsgHeader * pMsgHeader, 
                                                        void * pMsgData, int MsgDataLen);
int UnpackMsgForRead(USsock_handle Hus, UsockMsgHeader * pMsgHeader, 
                                                        void * pMsgData, int * MsgDataLen);

int SendUnixMsg(UCsock_handle hClient, US_PROCESS_ID src, US_PROCESS_ID dest, void * cmd_buf, int len);

int SendUnixMsgNoblock(UCsock_handle hClient, US_PROCESS_ID src, US_PROCESS_ID dest, void * cmd_buf, int len);

int CreateIPCUsock(IPC_USOCKSet_handle hIPCUSock, US_PROCESS_ID src);

void DeleteIPCUsock(IPC_USOCKSet_handle hIPCUSock);

#ifdef __cplusplus
}
#endif

#endif //_H_IPC_USOCKET_H_
