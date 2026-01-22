#include <menu_API.h>

#include "test.h"

//test
display_info loading = {
    .mode = DISPLAY_MODE_LOADING,
};
/*菜单选项格式如下*/
/*选项名(数组)*///*回调函数*///*传入参数(没有可以不写)*/
//测试菜单选项列表
option TEST_MENU_LIST[] = {
    {"测试循环",do_nothing},
    {"自定义函数测试",do_nothing},
    {"测试loading",run_info,&loading},
};
//菜单
menu TEST_MENU = {
    /*标题*/.name = "测试菜单",
    /*长度*/.length = sizeof(TEST_MENU_LIST)/sizeof(TEST_MENU_LIST[0]),
    /*选项列表*/.menu_list = TEST_MENU_LIST,
};
//对应显示包
display_info TEST_MENU_INFO = menu_to_display_info( &TEST_MENU );