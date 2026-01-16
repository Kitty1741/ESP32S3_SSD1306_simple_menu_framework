#include <menu_API.h>
#include "WLAN/WLAN.h"
#include "test/test.h"

//这个文件专门用来定义主菜单



/*菜单选项格式如下*/
/*
{  选项名(数组) , 回调函数 , 传入参数(没有可以不写)  }
*/
//主菜单选项列表
option MAIN_MENU_LIST[] = {
    {"WLAN",run_info,&WLAN_MENU_INFO},
    {"test",run_info,&TEST_MENU_INFO},
    {"中文测试",do_nothing},
    {"回调函数-菜单测试",run_info,NULL},
    {"多行测试",do_nothing},
    {"多行测试",do_nothing},
};
//主菜单
menu MAIN_MENU = {
    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(MAIN_MENU_LIST)/sizeof(MAIN_MENU_LIST[0]),
    /*选项列表*/.menu_list = MAIN_MENU_LIST,
};
//对应显示包
display_info MAIN_MENU_INFO = menu_to_display_info( &MAIN_MENU );