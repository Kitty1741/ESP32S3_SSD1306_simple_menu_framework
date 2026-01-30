#ifndef __MENU_STRUCT_H__
#define __MENU_STRUCT_H__

#include <Arduino.h>

//菜单选项结构体
typedef struct option_t{

    const char* name;          //选项名字
    bool (*callback)(void*);//这里放回调函数指针和回调函数参数
    void* param;            //task_loop的参数

}option;

//菜单结构体
typedef struct menu_t{

    const char *name;//菜单的标题
    uint16_t cursor;//菜单的光标位置
    uint16_t length;//菜单的列表长度
    option *menu_list;//菜单对应的选项列表

}menu;

#endif