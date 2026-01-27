#include <Arduino.h>

#include "0_config/config.h"
#include "1_driver/driver.h"

#include "setting_struct.h"
#include "setting.h"


/*
    函数名字：set_int_setting
    函数功能：根据接口里的键值，设置整数类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：setting*
        作用：告诉函数调整哪个设置
*///
bool set_int_setting( setting* SET ){

    int64_t* ptr = (int64_t*)SET->object;
    uint64_t time_0 = get_time_ms();
    uint8_t speed = 0;//调整选项的速度
}


/*
    函数名字：set_char_setting
    函数功能：根据接口里的键值，设置char类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：setting*
        作用：告诉函数调整哪个设置
*///
bool set_char_setting( setting* SET ){

    char* ptr = (char*)SET->object;
    uint64_t time_0 = get_time_ms();
    uint8_t speed = 0;//调整选项的速度

    //长按检查
    if( get_press_time() > LONG_PRESS_THRESHOLD ){
        speed = get_press_time() - LONG_PRESS_THRESHOLD ;
    }else speed = 0;

    //调整值
    switch( get_key_value() ){
        case KEY_NULL:return false;
        case KEY_UP_NUM:{ 
            *ptr <= 32 ?
            *ptr = 126 : *ptr --;
        }break;
        case KEY_OK_NUM:{}return true;
        case KEY_DOWN_NUM:{
            *ptr >= 126 ?
            *ptr = 32 : *ptr ++;
        }break;
        case KEY_BACK_NUM:{}return true;
    }

    //改变延时来改变速度
    if( speed = 0 ) vTaskDelay( 400 );
    else            vTaskDelay( 400 / ( speed / 20 + 5 ) );

    return false;
}