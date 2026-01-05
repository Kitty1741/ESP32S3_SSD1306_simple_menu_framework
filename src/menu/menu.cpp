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
    函数名字：image_to_display_info
    函数功能：把128x64的char图片数组塞进一个display_info类型的结构里
    返回值：
        类型：display_info
        意义：返回需要渲染的图片的打印信息
    参数：
        IMAGE
        类型：char[1024]
        作用：传输需要打印的图片
*///
display_info image_to_display_info( char IMAGE[1024] ){

    display_info image_info;
    image_info.mode = DISPLAY_MODE_IMAGE;//图片打印模式
    strcpy(image_info.data.img->image_data , IMAGE );//给display_info赋值
    return image_info;
}

/*
    函数名字：do_nothing
    函数功能：没有,防止菜单报空指针
    返回值：没有
    参数：没有
*///
bool do_nothing( void* do_nothing ){
    return true;
}

/*
    函数名字：config_menu_display_info
    函数功能：用来把菜单转化为打印信息
    返回值：
      类型：display_info
      意义：包含一个菜单的打印信息
    参数：
      MENU
      类型：menu*
      作用：提供要配置的菜单的指针
*///
display_info config_menu_display_info(menu *MENU){
  
    display_info INFO;

    INFO.data.menu_t = MENU;
    INFO.mode = DISPLAY_MODE_MENU;
    INFO.next = NULL;

    return INFO;
}


/*
    函数名字：config_list_display_info
    函数功能：用来把列表转化为打印信息
    返回值：
      类型：display_info
      意义：包含一个列表的打印信息
    参数：
      LIST
      类型：list*
      作用：提供要配置的列表的指针
*///
display_info config_list_display_info(list *LIST){
  
    display_info INFO;

    INFO.data.list_t = LIST;
    INFO.mode = DISPLAY_MODE_LIST;
    INFO.next = NULL;
    INFO.x = 0;
    INFO.y = 0;

    return INFO;
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