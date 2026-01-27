#include <menu_API.h>

#include "test.h"

//test
//SET
double_t test_f = 0;
setting TEST_SET = {

    .name = "测试",
    .MODE = SETTING_MODE_DOUBLE,
    .object = &test_f,
    .min = -3.0F,
    .max = 30.0F,
    
};
display_info TEST_SET_INFO = to_display_info( &TEST_SET );


//LOADING
display_info LOADING_INFO = {
    .mode = DISPLAY_MODE_LOADING,
};


//测试菜单选项列表
option TEST_MENU_LIST[] = {
    {"设置测试",run_info,&TEST_SET_INFO},
    {"自定义函数测试",do_nothing},
    {"测试loading",run_info,&LOADING_INFO},
};
/*菜单选项格式如下*/
/*选项名(数组)*///*回调函数*///*传入参数(没有可以不写)*/
//菜单
menu TEST_MENU = {
    /*标题*/.name = "测试菜单",
    /*长度*/.length = sizeof(TEST_MENU_LIST)/sizeof(TEST_MENU_LIST[0]),
    /*选项列表*/.menu_list = TEST_MENU_LIST,
};
//对应显示信息
display_info TEST_MENU_INFO = to_display_info( &TEST_MENU );
