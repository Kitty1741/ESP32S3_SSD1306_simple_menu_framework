#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//menu.h
typedef struct option_t option;
typedef struct menu_t menu;
typedef struct list_t list;
#include <keybord/keybord.h>

//这个头文件定义了各种用于模块信息交换的数据类型
//使用本菜单时请先看看

/*键盘*/
/*
用一个定时器定时扫描键盘
下面的结构用于记载定时返回的按键信息
*/


//菜单里的五个键值
typedef enum KEY_VALUE_t{

    KEY_NULL,//没有按键按下
    KEY_UP_NUM,//“上”键
    KEY_OK_NUM,//确认键
    KEY_DOWN_NUM,//“下”键
    KEY_BACK_NUM,//返回键

}KEY_VALUE;

//键盘的结构体
typedef struct menu_keybord_t{

    int key_enum;
    int key_value;
    int press_time;

}menu_keybord;



/*显示*/
/*
这里的几种结构告诉显示器输出什么

*/
//固定的几种屏幕输出模式
typedef enum{
    DISPLAY_MODE_NONE,      // 不显示
    DISPLAY_MODE_LOADING,   // 加载中
    DISPLAY_MODE_INFO,      // 信息显示（简单信息）
    DISPLAY_MODE_MENU,      // 菜单显示
    DISPLAY_MODE_LIST,      // 文字列表
    DISPLAY_MODE_IMAGE,     // 图片显示
}PRINT_MODE;

//定义图片类型用来存储图片
typedef struct image_t{
    char image_data[1024];//正好存储128*64个点的数据
}image;

//可能出现的信息类型
typedef union{
    char* str[64];//字符串指针列表信息,文字类型
    menu* menu_t;//菜单类型
    image* img;//图片类型
    list* list_t;//列表类型
}display_data;

//用来传值打印内容的结构
typedef struct display_info_t{

    PRINT_MODE mode;//输出内容的类型
    display_data data;//内含一个和类型对应的结构的指针(内含信息)
    unsigned char x;//在屏幕上的坐标
    unsigned char y;//（只对一部分选项生效）
    struct display_info_t *next;//链表结构，方便叠加图层

}display_info;



//这里定义了一个用于数据交换的结构
//不同功能只能以此为接口进行最低耦合的开发
////
//最简实现:先来依托大的
//仅仅定义几种数据结构来使各个模块通信
//模块需要就自取信息
typedef struct menu_event_t{

    menu_keybord *keybord_status;
    display_info *display;
    
}menu_event;

//全局时间管理器声明
extern menu_event MainEventManager;
//初始化事件管理器
void init_MainEventManager();

#endif