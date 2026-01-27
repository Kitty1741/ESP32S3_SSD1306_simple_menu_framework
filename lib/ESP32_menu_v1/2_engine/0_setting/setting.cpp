#include <Arduino.h>

#include "0_config/config.h"
#include "1_driver/driver.h"

#include "setting_struct.h"
#include "setting.h"


/*
    函数名字：set_double_setting
    函数功能：根据接口里的键值，设置小数类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：setting*
        作用：告诉函数调整哪个设置
*///
bool set_double_setting( setting* SET ){

    double_t* ptr = (double_t*)SET->object;
    double_t minus = SET->max - SET->min;//最大值-最小值的差
    double_t adjust_num = 0;//决定调整速度

    //长按检查/调整调整速度
    bool if_long_press = false;
    if( get_press_time() > LONG_PRESS_THRESHOLD ){
        if_long_press = true;
        adjust_num = ( get_press_time() - LONG_PRESS_THRESHOLD );//得到长按的时间
        adjust_num = ( adjust_num/50000 +0.005 ) * minus;//调整速度随时间线性增加
    }else adjust_num = minus * 0.005;

    //按键响应
    uint8_t key = get_key_value();
    if( if_long_press == true || get_first_key() == key )//当按下/松手更新
    switch( key ){
        case KEY_NULL:return false;
        case KEY_UP_NUM:{   //--
            *ptr -= adjust_num;
            if(*ptr < SET->min )
            *ptr = SET->min;
        }break;
        case KEY_OK_NUM:{}return true;
        case KEY_DOWN_NUM:{ //++
            *ptr += adjust_num;
            if(*ptr > SET->max )
            *ptr = SET->max;
        }break;
        case KEY_BACK_NUM:{}return true;
    }vTaskDelay(50);

    return false;
}

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
    uint8_t ex_time;//决定调整选项的速度
    uint64_t minus_num;//由按下时间计算改变幅度

    //长按检查
    ex_time = 0;//决定调整选项的速度
    if( get_press_time() > LONG_PRESS_THRESHOLD ){
        ex_time = get_press_time() - LONG_PRESS_THRESHOLD ;
    }else ex_time = 0;//ex_time = 超过长按阈值的时间

    //由按下时间计算改变幅度
    minus_num = SET->max - SET->min ;//最大值和最小值差
    minus_num = ( ex_time / 50000  + 0.005 ) * minus_num;//根据时间调整改变幅度

    //调整值
    switch( get_key_value() ){
        case KEY_NULL:return false;
        case KEY_UP_NUM:{   //--
            if(*ptr >= SET->min )*ptr -= minus_num;
        }break;
        case KEY_OK_NUM:{}return true;
        case KEY_DOWN_NUM:{ //++
            if(*ptr <= SET->max )*ptr += minus_num;
        }break;
        case KEY_BACK_NUM:{}return true;
    }

    vTaskDelay( 50 - ( get_time_ms() - time_0 ) );

    return false;
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
    }else speed = 0;//speed = 超过长按阈值的时间

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
    if( speed = 0 ) vTaskDelay( 500 );
    else            vTaskDelay( 400 / ( speed / 20 + 5 ) );

    return false;
}