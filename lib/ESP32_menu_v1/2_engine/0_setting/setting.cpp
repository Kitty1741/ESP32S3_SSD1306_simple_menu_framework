//setting.cpp
#include <Arduino.h>

#include "0_config/config.h"
#include "1_driver/driver.h"

#include "setting_struct.h"
#include "setting.h"


/*
    函数名字：long_press_logic
    函数功能：处理按键按下改变变量的业务
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        num
        类型：double_t*
        作用：告诉函数设置哪个值
        min
        类型：double_t
        作用：告诉函数设置的最小值
        max
        类型：double_t
        作用：告诉函数设置的最大值
        mode
        类型：m_setting_mode
        作用：告诉函数设置的数据类型，方便控制单击加减
*///
bool set_setting_num( double_t* num , double_t min , double_t max , m_setting_mode mode ){

    #if(IF_DEBUG_2 == true)//debug
    Serial.println("set_setting_num()");
    #endif

    bool return_value = false;
    double_t minus = max - min;//最大值-最小值的差
    double_t adjust_num = 0;//决定调整速度

    //长按检测
    bool if_long_press = false;
    if( get_press_time() > LONG_PRESS_THRESHOLD )
    if_long_press = true;

    //调整调整速度
    if( if_long_press ){//长按
        adjust_num = ( get_press_time() - LONG_PRESS_THRESHOLD );//得到长按的时间
        adjust_num = ( adjust_num/20000 +0.01 ) * minus;//调整速度随时间线性增加
    }else switch( mode ){//单击
        case SETTING_MODE_INT:adjust_num = 1;break;
        case SETTING_MODE_CHAR:adjust_num = 1;break;
        case SETTING_MODE_DOUBLE:adjust_num = minus * 0.003;break;
    }

    //按键响应
    if( if_long_press || get_first_key() )
    switch( get_key_value() ){
        case KEY_NULL:return false;break;
        case KEY_UP_NUM:{   //--
            *num -= adjust_num;
            if(*num < min )
            *num = min;
        }break;
        case KEY_OK_NUM:return true;break;
        case KEY_DOWN_NUM:{ //++
            *num += adjust_num;
            if(*num > max )
            *num = max;
        }break;
        case KEY_BACK_NUM:return true;break;
    }vTaskDelay(50);

    return false;
}

/*
    函数名字：set_double_setting
    函数功能：根据接口里的键值，设置小数类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：m_setting_t*
        作用：告诉函数调整哪个设置
*///
bool set_double_setting( m_setting_t* SET ){

    //设置值
    bool return_value = set_setting_num( 
        (double_t*)SET->object,
        SET->min,
        SET->max,
        SET->MODE
    );

    //返回
    while( return_value && get_key_value() )
    vTaskDelay(50);//当退出时先阻塞线程直到松手，防止多次检测按键
    return return_value;
}

/*
    函数名字：set_int_setting
    函数功能：根据接口里的键值，设置整数类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：m_setting_t*
        作用：告诉函数调整哪个设置
*///
bool set_int_setting( m_setting_t* SET ){
    
    //初始化
    static double_t value;
    if( (int64_t)value != *(int64_t*)SET->object )
    value = *(int64_t*)SET->object;

    //设置值
    bool return_value = set_setting_num( 
        &value,
        SET->min,
        SET->max,
        SET->MODE
    );*(int64_t*)SET->object = value;

    //返回
    while( return_value && get_key_value() )
    vTaskDelay(50);//当退出时先阻塞线程直到松手，防止多次检测按键
    return return_value;
}


/*
    函数名字：set_char_setting
    函数功能：根据接口里的键值，设置char类型值
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        SET
        类型：m_setting_t*
        作用：告诉函数调整哪个设置
*///
bool set_char_setting( m_setting_t* SET ){
    //初始化
    static double_t value;
    if( (char)value != *(char*)SET->object )
    value = *(char*)SET->object;

    //设置值
    SET->min = -0x80;
    SET->max = 0x7f;
    bool return_value = set_setting_num( 
        &value,
        SET->min,
        SET->max,
        SET->MODE
    );*(char*)SET->object = (char)value;

    //返回
    while( return_value && get_key_value() )
    vTaskDelay(50);//当退出时先阻塞线程直到松手，防止多次检测按键
    return return_value;
}