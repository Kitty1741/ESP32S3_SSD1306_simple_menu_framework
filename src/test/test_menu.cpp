#include <menu_API.h>

#include "test.h"
#include "test_func.h"

//test
//SET
//int
int64_t testint = 0;
setting TEST_SET_INT = {

    .name = "测试int",
    .MODE = SETTING_MODE_INT,
    .object = &testint,
    .min = -999999,
    .max = 2559999,
    
};
display_info TEST_SET_INT_INFO = to_display_info( &TEST_SET_INT );
//char
char testchar = '2';
setting TEST_SET_CHAR = {

    .name = "测试char",
    .MODE = SETTING_MODE_CHAR,
    .object = &testchar,
};
display_info TEST_SET_CHAR_INFO = to_display_info( &TEST_SET_CHAR );
//double
double testdouble = 0;
setting TEST_SET_DOUBLE = {

    .name = "测试double",
    .MODE = SETTING_MODE_DOUBLE,
    .object = &testdouble,
    .min = -PI,
    .max = 100000000*PI,
    
};
display_info TEST_SET_DOUBLE_INFO = to_display_info( &TEST_SET_DOUBLE );


//测试菜单选项列表
option TEST_MENU_ENGINE_LIST[] = {
    {"设置char"  ,run_info  ,&TEST_SET_CHAR_INFO   },
    {"设置int"   ,run_info  ,&TEST_SET_INT_INFO    },
    {"设置double",run_info  ,&TEST_SET_DOUBLE_INFO },
};
menu TEST_MENU_ENGINE = {
    /*标题*/.name = "设置测试",
    /*长度*/.length = lengthof(TEST_MENU_ENGINE_LIST),
    /*选项列表*/.menu_list = TEST_MENU_ENGINE_LIST,
};
display_info TEST_MENU_ENGINE_INFO = to_display_info( &TEST_MENU_ENGINE );


//LOADING
display_info LOADING_INFO = {
    .mode = DISPLAY_MODE_LOADING,
};


//菜单选项列表
option TEST_MENU_LIST[] = {
    {"核心功能测试",run_info,&TEST_MENU_ENGINE_INFO},
    {"自定义函数测试",show_time,NULL},
    {"测试loading",run_info,&LOADING_INFO},
};
/*菜单选项格式如下*/
/*选项名(数组)*///*回调函数*///*传入参数(没有可以不写)*/
//菜单
menu TEST_MENU = {
    /*标题*/.name = "测试菜单",
    /*长度*/.length = lengthof(TEST_MENU_LIST),
    /*选项列表*/.menu_list = TEST_MENU_LIST,
};
//对应显示信息
display_info TEST_MENU_INFO = to_display_info( &TEST_MENU );
