#include <Arduino.h>

#include "1_driver/driver.h"

#include "menu_setting.h"
#include "menu_struct.h"
#include "menu.h"

//这个文件放用来计算菜单和列表运行逻辑的函数


/*
    函数名字：task_loop
    函数功能：进入死循环，反复调用回调函数
    返回值：没有
    参数：
      function
      类型：bool (*)(void*)
      作用：告诉函数要调用哪个函数
      param
      类型：void*
      作用：告诉函数调用函数的参数填什么

*///
void task_loop( bool (*function)(void*) , void* param ){

    if (!function) return;//防炸

    while(1){
        if( function(param) == true )
        break;
        vTaskDelay(0);
    }
}




/*
    函数名字：set_menu_cursor
    函数功能：根据接口里的键值，设置菜单光标
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        MENU
        类型：menu*
        作用：告诉函数菜单的长度和用来设置谁的光标
*///
bool set_menu_cursor( menu *MENU ){

    #if( IF_DEBUG_2 == true )//debug
    Serial.println("set_menu_cursor()");
    #endif

    uint8_t menu_key;

    menu_key = get_last_key();//检测松手键值

    //根据输入的键值确定光标移动/其他操作
    switch( menu_key ){
        case KEY_NULL:break;
        case KEY_UP_NUM:{//光标上移
            MENU->cursor != 0 ?
            MENU->cursor -- : MENU->cursor = MENU->length - 1 ;
        }break;
        case KEY_OK_NUM:{//进入光标所指选项
            task_loop(
                MENU->menu_list[MENU->cursor].callback ,
                MENU->menu_list[MENU->cursor].param
            );
        }break;
        case KEY_DOWN_NUM:{//光标下移
            MENU->cursor != MENU->length -1 ?
            MENU->cursor ++ : MENU->cursor = 0 ;
        }break;
        case KEY_BACK_NUM:{//返回
            MENU->cursor = 0;
            return true;
        }break;
    }
    menu_key = KEY_NULL;

    return false;
}