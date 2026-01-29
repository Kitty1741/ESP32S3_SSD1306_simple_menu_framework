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
CREATE_MENU(test_engine,{
    {"设置char"  ,run_info  ,&TEST_SET_CHAR_INFO   },
    {"设置int"   ,run_info  ,&TEST_SET_INT_INFO    },
    {"设置double",run_info  ,&TEST_SET_DOUBLE_INFO },
})

display_info test_engine_menu_info = to_display_info( &test_engine_menu );


//LOADING
display_info loading_info = {
    .mode = DISPLAY_MODE_LOADING,
};


//菜单选项列表
CREATE_MENU(test ,{
    {"核心功能测试",run_info,&test_engine_menu_info},
    {"自定义函数测试",show_time,NULL},
    {"测试loading",run_info,&loading_info},
})
//对应显示信息
display_info test_menu_info = to_display_info( &test_menu );
