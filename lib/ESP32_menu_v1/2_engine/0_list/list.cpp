#include <Arduino.h>

#include "1_driver/driver.h"

#include "list_setting.h"
#include "list_struct.h"
#include "list.h"


/*
    函数名字：set_list_cursor
    函数功能：根据接口里的键值，设置列表光标
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        LIST
        类型：list*
        作用：告诉函数列表的长度和用来设置谁的光标
*///
bool set_list_cursor( list *LIST ){

    #if( IF_DEBUG_2 == true )//debug
    Serial.println("set_list_cursor()");
    #endif

    uint8_t list_key;
    list_key = get_last_key();//检测松手键值

    //根据输入的键值确定光标移动/其他操作
    switch( list_key ){
        case KEY_NULL:break;
        case KEY_UP_NUM:{//光标上移
            LIST->cursor != 0 ?
            LIST->cursor -- : LIST->cursor += 0 ;
        }break;
        case KEY_OK_NUM:break;
        case KEY_DOWN_NUM:{//光标下移
            LIST->list[ LIST->cursor +3 ] != NULL ?
            LIST->cursor ++ : LIST->list[ LIST->cursor +4 ] != NULL ?
            LIST->cursor ++ : LIST->cursor += 0 ;
        }break;
        case KEY_BACK_NUM:{//返回
            LIST->cursor = 0;
            return true;
        }break;
    }list_key = KEY_NULL;

    return false;
}