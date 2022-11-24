#ifndef _LEDMANAGERSHOW_H_
#define _LEDMANAGERSHOW_H_

#ifdef __cplusplus
extern "C" {
#endif

#define INT32 int32_t 

#define LED_MANAGER_FUNCTION_BEGIN printf("<LED_MANAGER> %s %d line begin \n",__FUNCTION__,__LINE__);
#define LED_MANAGER_FUNCTION_END   printf("<LED_MANAGER> %s %d line end \n",__FUNCTION__,__LINE__);

typedef struct _LED_MANAGER_PTHREAD_OBJ_T
{
    pthread_t led_status_tid;
    pthread_t led_strip_tid;
}LED_MANAGER_PTHREAD_OBJ_T;

typedef struct _LED_MANAGER_STATUE_OBJ_T
{
    int bootupWorking;
    int wifiConnected;
    int connected_to_internet;
    int bt_connect;
    int batteryWorking;
    int batteryLow;
}LED_MANAGER_STATUE_OBJ_T;

typedef enum
{
    LED_MANAGER_AVAILABLE,
    LED_MANAGER_UNAVAILABLE,
    LED_MANAGER_PREEMPT
}LED_MANAGER_STATUE_E;

typedef enum
{
    LED_STATUS_READY_AND_WORKING_NORMALLY = 0x00,
    LED_STATUS_BOOTUP,
    LED_STATUS_WIFI_CONNECTED,
    LED_STATUS_IDLE,
    LED_STATUS_CHIME_EVENT,
    LED_STATUS_WAIT_USER_RESPONSE,
    LED_STATUS_AI_DETECTION,
    LED_STATUS_BLE_PROVISIONING,
    LED_STATUS_BLE_DISCONNECT,
    LED_STATUS_REBOOT,
    LED_STATUS_DEMO,

    LED_STRIP_COLOR_BLACK = 0x30,
    LED_STRIP_COLOR_WHITE,
    LED_STRIP_COLOR_RED,
    LED_STRIP_COLOR_GREEN,
    LED_STRIP_COLOR_BLUE,
    LED_STRIP_COLOR_YELLOW,
    LED_STRIP_COLOR_MAGENTA,
    LED_STRIP_COLOR_PURPLE,
    LED_STRIP_COLOR_ORANGE,
    LED_STRIP_COLOR_CYAN,
}LED_MANAGER_MSG_T;

#define LED_STATUS_READY_STR                "Ready"
#define LED_STATUS_BOOTING_UP_STR           "BootingUp"
#define LED_STATUS_WIFI_CONNECTED_STR       "WiFiConnected"
#define LED_STATUS_IDLE_STR                 "Idle"
#define LED_STATUS_CHIME_EVENT_STR          "PressButton"
#define LED_STATUS_WAIT_USER_RESPONSE_STR   "WaitUserResponse"
#define LED_STATUS_AI_DETECTION_STR         "AiDetect"
#define LED_STATUS_BLE_PROVISIONING_STR     "BleProvisioning"
#define LED_STATUS_BLE_DISCONNECT_STR       "BleDisconnect"
#define LED_STATUS_REBOOT_STR               "Reboot"
#define LED_STATUS_DEMO_STR                 "LEDDemo"

#define LED_STRIP_COLOR_BLACK_STR           "BlackColorStrip"
#define LED_STRIP_COLOR_WHITE_STR           "WhiteColorStrip"
#define LED_STRIP_COLOR_RED_STR             "RedColorStrip"
#define LED_STRIP_COLOR_GREEN_STR           "GreenColorStrip"
#define LED_STRIP_COLOR_BLUE_STR            "BlueColorStrip"
#define LED_STRIP_COLOR_YELLOW_STR          "YellowColorStrip"
#define LED_STRIP_COLOR_MAGENTA_STR         "MagentaColorStrip"      
#define LED_STRIP_COLOR_PURPLE_STR          "PurpleColorStrip"
#define LED_STRIP_COLOR_ORANGE_STR          "OrangeColorStrip"
#define LED_STRIP_COLOR_CYAN_STR            "CyanColorStrip"

//------------------------------------------------------------------------------
int ledManagerStop(void);
int ledManagerHandleMsg(const char *msg_text);
int ledManagerGetStatus(char szStatus[]);
void ledManagerSetBoardType(const int boardt_ype);
int ledManagerInit(void);

#ifdef __cplusplus
}
#endif

#endif // _LEDMANAGERSHOW_H_
