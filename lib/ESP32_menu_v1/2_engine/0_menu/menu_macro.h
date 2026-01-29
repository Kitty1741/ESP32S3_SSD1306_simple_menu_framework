#ifndef __MENU_MACRO_H__
#define __MENU_MACRO_H__

//定义了快速创建菜单的宏

#include "menu_struct.h"

#define CREATE_MENU(NAME, ... )                      \
static option NAME##_menu_options[] = __VA_ARGS__;   \
menu NAME##_menu = {                                 \
    .name = #NAME,                                   \
    .length = lengthof(NAME##_menu_options),         \
    .menu_list = NAME##_menu_options,                \
};

//eg.
/*
CREATE_MENU( test ,{
    {"option01",do_nothing,NULL},
    {"option02",do_nothing,NULL},
    {"中文",do_nothing,NULL},
})


意味着
创建一个叫 "test_menu" 的菜单 (菜单名 = 输入名字 + _menu)
并添加三个选项
第一个：名叫“option01”，选中后执行do_nothing，参数为NULL
第二个：名叫“option02”，选中后执行do_nothing，参数为NULL
第三个：名叫“中文”，选中后执行do_nothing，参数为NULL
*/

#endif