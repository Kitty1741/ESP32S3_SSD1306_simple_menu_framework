#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>


//这个文件放用来计算菜单和列表运行逻辑的函数


/*
    函数名字：set_cursor
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

    static uint8_t menu_key;

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
            menu_init_u8g2();//完事还原默认设置
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

    static uint8_t list_key;
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
        yield();
    }
}