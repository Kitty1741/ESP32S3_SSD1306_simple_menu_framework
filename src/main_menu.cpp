#include <menu_API.h>

//这个文件专门用来定义主菜单

//主菜单选项列表
option MAIN_MENU_LIST[] = {

    {"WLAN",do_nothing},
};
//主菜单
menu MAIN_MENU = {

    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(MAIN_MENU_LIST)/sizeof(MAIN_MENU_LIST[0]),
    /*选项列表*/.menu_list = MAIN_MENU_LIST,

};
//对应显示包
display_info MAIN_MENU_INFO = config_menu_display_info( &MAIN_MENU );