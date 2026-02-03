#include <Arduino.h>
#include <driver/timer.h>

#include "keyboard.h"
#include "keyboard_struct.h"


//声明扫描结构体
extern m_keyboard_t keyboard_status;

extern int (* user_scan_once)();//单次扫描，返回键值，通常在user_scan_keyboard中被调用一次(没有也行)
extern void (* user_scan_keyboard)();//定时中断调用的扫描函数,直接更改系统键值
extern void (* user_init_keyboard)();//初始化键盘的硬件

#if ( use_which_timer == 4 )

/*
    函数名字：ManagerKeyboard
    函数功能：调用用户定义的扫描函数，上报数据管理器，由freeRTOS事件调用
    返回值：没有
    参数：
        no_param
        类型：void*
        意义：由freeRTOS调用的回调函数必须要有个void*参数
*///
void ManagerKeyboard( void* no_param ){
    __DEBUG_1("ManagerKeyboard()\n");
    while(1){
        user_scan_keyboard();
        vTaskDelay( pdMS_TO_TICKS(20) );
    }
}

TaskHandle_t KeyboardTask;

#endif

void init_keyboard_timer();

//这个程序只定义了一个初始化函数，里面塞上了所有和键盘有关的初始化函数
void keyboard_init(){

    //初始化扫键盘的定时器的函数
    init_keyboard_timer();

    //用户自定义的初始化函数
    user_init_keyboard();
}




//初始化定时器(setting.h里指定的定时器)
//这个别改
void init_keyboard_timer(){

    __DEBUG_1("init_keyboard_timer()\n");

    hw_timer_t *timer = NULL;
    switch(USE_TIMER){
        case 5:break;
        case 4:{//选择软件定时器
            #if ( use_which_timer == 4 )
            xTaskCreate(
                ManagerKeyboard,     // 任务函数指针
                "ManagerKeyboard",   // 任务名称（调试用）
                2560,               // 任务栈大小（字节）
                NULL,               // 传递给任务的参数（本例为空）
                8,                 // 任务优先级（1-24）
                &KeyboardTask      //任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
            );    
            #endif
        }break;
        default:{//选择硬件定时器
            timer = timerBegin( USE_TIMER , 80 , true );//初始化对应硬件定时器
            timerAttachInterrupt( timer , user_scan_keyboard, false );//用于将中断处理函数与特定的定时器关联起来
            timerAlarmWrite( timer, 20000 , true );//用于设置定时器的计数值
            timerAlarmEnable(timer);  // 启动定时器！
        }break;            /*对于20000↑说明：0.02s*(80MHZ/分频系数)*/
    }
}


/*
    函数名字：get_key_value
    函数功能：返回接口里的键值，使代码易读
    返回值：
        类型：uint8_t
        意义：接口里的键值
    参数：没有
*///
uint8_t get_key_value(){

    __DEBUG_1("get_key_value() = ")
    __DEBUG_1(keyboard_status.key_value ) __DEBUG_1('\n')

    return keyboard_status.key_value;
}


/*
    函数名字：get_press_time
    函数功能：返回接口里的按键按下时间，使代码易读
    返回值：
        类型：uint8_t
        意义：接口里的按键按下时间(单位毫秒)
    参数：没有
*///
uint16_t get_press_time(){

    __DEBUG_1("get_press_time() = ")
    __DEBUG_1(keyboard_status.press_time ) __DEBUG_1('\n')

    return keyboard_status.press_time;
}

/*
    函数名字：get_first_key
    函数功能：返回按下按键那一瞬间的值，没按返回KEY_NULL
    返回值：
        类型：uint8_t
        意义：按键的值
    参数：没有
*///
uint8_t get_first_key(){

    __DEBUG_1("get_first_key() = ")
    
    static uint8_t last_key;

    if( last_key == get_key_value() ){
        __DEBUG_1(KEY_NULL) __DEBUG_1('\n')
        return KEY_NULL;
    }
    else{
        last_key = get_key_value();
        __DEBUG_1(last_key) __DEBUG_1('\n')
        return last_key;
    }
}
