

#include "menu_API.h"

#include "WLAN/WLAN.h"
#include "test/test.h"

//这个文件专门用来定义主菜单

/*菜单选项格式如下*/
/*
{  选项名(数组) , 回调函数 , 传入参数(没有可以不写)  }
*/
//主菜单选项列表
CREATE_MENU(main,{
    {"WLAN",run_info,&WLAN_menu_info},
    {"test",run_info,&test_menu_info},
    {"中文测试",do_nothing},
    {"回调函数-菜单测试",run_info,NULL},
    {"多行测试",do_nothing},
    {"多行测试",do_nothing},
})
//对应显示包
display_info main_menu_info = to_display_info( &main_menu );