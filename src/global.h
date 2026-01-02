#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//这个头文件定义了各种用于模块信息交换的数据类型
//使用本菜单时请先看看

/*键盘*/
/*
用一个定时器定时扫描键盘
下面的结构用于记载定时返回的按键信息
*/


//菜单里的五个键值
typedef enum{

    KEY_NULL,//没有按键按下
    KEY_UP_NUM,//“上”键
    KEY_OK_NUM,//确认键
    KEY_DOWN_NUM,//“下”键
    KEY_BACK_NUM,//返回键

}KEY_VALUE;

//键盘的结构体
typedef struct menu_keybord_t{

    KEY_VALUE key_enum;
    int key_value;
    int press_time;

}menu_keybord;



/*显示*/
/*
这个菜单的一大特性就是：
只有显示模块才能用u8g2
把信息显示在屏幕上
其他的模块只能以特定格式
给显示模块信息
最大化降低耦合
输出格式标准规范
*/
//固定的几种屏幕输出模式(以叠加?)
typedef enum{

    NUL,//啥也不输出
    LOADING,//输出加载中
    EZ_INFO,//输出简单信息
    MENU,//输出菜单
    TEXT_LIST,//输出文字列表
    PICTURE,//输出图片

}PRINT_MODE;



//这里定义了一个用于数据交换的结构
//不同功能只能以此为接口进行最低耦合的开发
////
//最简实现:先来依托大的
//仅仅定义几种数据结构来使各个模块通信
//模块需要就自取信息
typedef struct menu_event_t{

    menu_keybord keybord_status;
    
}menu_event;

menu_event MainEventManager;

#endif