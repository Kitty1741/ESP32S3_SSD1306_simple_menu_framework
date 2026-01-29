#ifndef __WLAN_H__
#define __WLAN_H__

#include <menu_API.h>

//extern
extern display_info WLAN_menu_info;

//WLAN
// 定义WiFi信息结构体
typedef struct wifi_info{
    char ssid[40];      // WiFi名称
    int rssi;        // 信号强度（用整数更高效）
    int encryption; // 加密类型
} wifi_info;

typedef struct wifi_list{
    wifi_info *list;       // WiFi列表指针
    int length;            // WiFi列表长度
} wifi_list;

//extern
extern wifi_info WLAN_CONNECTION_OPTIONS_INFO;
extern option WLAN_MENU_OPTIONS[];

#endif