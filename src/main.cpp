#include <Arduino.h>
#include <menu_API.h>
#include <WLAN/WLAN.h>

extern display_info MAIN_MENU_INFO;

void setup() {

    //menu_API
    menu_API_init();
}

void loop(){
    //主菜单
    run_info( &MAIN_MENU_INFO );
}
