#include <WiFi.h>
#include <menu_API.h>
#include <WLAN/WLAN.h>
#include <HTTPClient.h> // 关键库，用于HTTP协议



option WLAN_LIST[] = {
    {"ssid",do_nothing},
    {"连接",do_nothing},
};
menu WLAN_MENU = {
    /*标题*/.name = "WLAN",
    /*长度*/.length = sizeof(WLAN_LIST)/sizeof(WLAN_LIST[0]),
    /*选项列表*/.menu_list = WLAN_LIST,
};
display_info WLAN_MENU_INFO = menu_to_display_info( &WLAN_MENU );
