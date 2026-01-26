#include <Arduino.h>

#include "keyboard.h"
#include "keyboard_struct.h"
#include "user_defined.h"

//用户自定义扫描函数


//把你自己的单次键盘扫描函数放在这里                 |
//这里的函数由你自己调用，if你不用也可以空着         |
//只要你的扫描-传值函数正常工作就行了                ↓
int (* user_scan_once)() = default_scan_once_function;

//把你自己的完整键盘 扫描-传值 函数放在这里  |
//这里的函数会定时被timer中断执行           ↓
void (* user_scan_keyboard)() = default_scan_function;

//把你自己的键盘初始化函数放在这|
//这里的函数会定时被setup()执行 ↓
void (* user_init_keyboard)() = default_init_function;


//存储扫描结果的结构体
menu_keyboard keyboard_status;

//下面是默认的键盘扫描函数，用户根据自己需求修改

//简单的键盘扫描函数
//功能：在中断中扫描键盘然后赋值给MainEventManager.keyboard_status
void default_scan_function(){
    static int key_value;//防止频繁入栈出栈影响性能
    static int press_time;

    //扫描和计时
    key_value = user_scan_once();
    key_value == KEY_NULL ?
    press_time = KEY_NULL :
    press_time += 20 ;

    //直接把数据打入公共结构
    keyboard_status.key_enum = key_value;
    keyboard_status.key_value = key_value;
    keyboard_status.press_time = press_time;

    return;
}

//初始化键盘引脚
void default_init_function(){
    pinMode( UP_NUM_IO   ,INPUT_PULLUP);
    pinMode( OK_NUM_IO   ,INPUT_PULLUP);
    pinMode( DOWN_NUM_IO ,INPUT_PULLUP);
    pinMode( BACK_NUM_IO ,INPUT_PULLUP);
}

//扫描键盘返回枚举键值
//默认键盘在10 11 12 13引脚上
int default_scan_once_function(){
    if     ( digitalRead( UP_NUM_IO   ) == 0 ){return (int)KEY_UP_NUM;}
    else if( digitalRead( OK_NUM_IO   ) == 0 ){return (int)KEY_OK_NUM;}
    else if( digitalRead( DOWN_NUM_IO ) == 0 ){return (int)KEY_DOWN_NUM;}
    else if( digitalRead( BACK_NUM_IO ) == 0 ){return (int)KEY_BACK_NUM;}
    else{
        return KEY_NULL;
    }
}





