#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>

//这个文件专门用来定义菜单


//主菜单选项列表
option MAIN_MENU_LIST[] = {

    {"测试",do_nothing},
    {"测试00",do_nothing},
    {"test",do_nothing},
    {"meow",do_nothing},
    {"测试05",do_nothing},
    {"测试06",do_nothing},

};
//主菜单
menu MAIN_MENU = {

    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(MAIN_MENU_LIST)/sizeof(MAIN_MENU_LIST[0]),
    /*选项列表*/.list = MAIN_MENU_LIST,

};


