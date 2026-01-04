#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>
#include <display/u8g2_print.h>

extern menu MAIN_MENU;

char test_str_01[40];
uint32_t millis_num = 0;

static bool meow = false;

//测试菜单选项列表
option TEST_MENU_LIST[] = {

    {"测试",do_nothing,NULL},
    {"测试00",do_nothing,NULL},
    {"test",test_print_num,&millis_num},

};
//测试菜单
menu TEST_MENU = {

    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(TEST_MENU_LIST)/sizeof(TEST_MENU_LIST[0]),
    /*光标初始化*/.cursor = 0,
    /*选项列表*/.menu_list = TEST_MENU_LIST,

};
display_info TEST_MENU_INFO = config_menu_display_info( &TEST_MENU );

//测试函数，检测这玩意能不能跑
void test_loop(){

    millis_num = millis();

    sprintf( test_str_01 , "%d" , millis() );
    set_menu_cursor( TEST_MENU_INFO.data.menu_t );
    u8g2_print_display_info( &TEST_MENU_INFO );
}
