#include <WiFi.h>
#include <menu_API.h>
//#include <WLAN/WLAN.h>
//#include <HTTPClient.h> // 关键库，用于HTTP协议


CREATE_MENU( WLAN , {
    {"ssid",do_nothing},
    {"连接",do_nothing},
})
display_info WLAN_menu_info = to_display_info( &WLAN_menu );
