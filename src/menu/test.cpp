#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>
#include <menu\u8g2_print.h>

extern menu MAIN_MENU;

char test_str_01[40];
char test_str_02[40];
char test_str_03[40];


static bool meow = false;
void change_mode(){

    meow = !meow;

}

//测试菜单选项列表
option TEST_MENU_LIST[] = {

    {"测试",do_nothing},
    {"测试00",do_nothing},
    {"test",do_nothing},
    {"meow",change_mode},
    {"测试05",do_nothing},

};
//测试菜单
menu TEST_MENU = {

    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(TEST_MENU_LIST)/sizeof(TEST_MENU_LIST[0]),
    /*光标初始化*/.cursor = 0,
    /*选项列表*/.list = TEST_MENU_LIST,

};

list TEST_LIST = {
    .cursor = 0,
    .list = {
        test_str_01,
        test_str_02,
        test_str_03,
        "meow",
        "meow",
        "meow",
    },
};
display_info TEST_LIST_INFO = {
    .mode = DISPLAY_MODE_LIST,//输出内容的类型
    .data = { .list_t = &TEST_LIST },
    .x = 50,.y = 24,
    .next = NULL,//链表结构，方便叠加图层
};
display_info TEST_MENU_INFO = {
    .mode = DISPLAY_MODE_MENU,//输出内容的类型
    .data = { .menu_t = &TEST_MENU },
    .next = &TEST_LIST_INFO,//链表结构，方便叠加图层
};

//测试函数，检测这玩意能不能跑
void test_loop(){

    sprintf( test_str_01 , "%d" , millis() );
    sprintf( test_str_02 , "%d" , TEST_MENU_INFO.data.menu_t->cursor );
    sprintf( test_str_03 , "%d" , TEST_LIST_INFO.data.list_t->cursor );

    meow?
    set_list_cursor( TEST_LIST_INFO.data.list_t ):
    set_menu_cursor( TEST_MENU_INFO.data.menu_t );
    u8g2_print_display_info( &TEST_MENU_INFO );

    TEST_LIST_INFO.y = sin( millis()/666.66 )*16 + 20;
    TEST_LIST_INFO.x = cos( millis()/777.7777 )*10 + 60;
}
