#ifndef __U8G2_PRINT_STRUCT_H__
#define __U8G2_PRINT_STRUCT_H__

#include <Arduino.h>
//下级结构声明
#include "2_engine/engine_struct.h"

/*  显示  */
/*
这里定义打印函数作为参数的结构
该结构内部包含了各种类型
*/
//固定的几种屏幕输出模式
typedef enum PRINT_MODE_t{
    DISPLAY_MODE_NONE,      // 不显示
    DISPLAY_MODE_LOADING,   // 加载中
    DISPLAY_MODE_TEXT,      // 信息显示（简单信息）
    DISPLAY_MODE_MENU,      // 菜单显示
    DISPLAY_MODE_LIST,      // 文字列表
    DISPLAY_MODE_IMAGE,     // 图片显示
    DISPLAY_MODE_SETTING,   // 设置界面显示
}PRINT_MODE;

//存储数据的共用体
typedef union{
    char* str[6];//简单文本类型
    menu* menu_t;//菜单类型
    image* img;//图片类型
    list* list_t;//列表类型
    setting* setting_t;//设置类型
}display_data;

//用来传值打印内容的结构
typedef struct display_info_t{

    PRINT_MODE mode;//输出内容的类型
    display_data data;//内含一个和类型对应的结构的指针(内含信息)
    uint8_t x;//在屏幕上的坐标
    uint8_t y;//（只对一部分选项生效）
    display_info_t *next;//链表结构，方便叠加图层

}display_info;

#endif