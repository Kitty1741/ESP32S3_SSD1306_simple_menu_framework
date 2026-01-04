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
      MENU->list[MENU->cursor].fun();
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
  }menu_key = KEY_NULL;

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
    函数名字：get_key_value
    函数功能：返回接口里的键值，使代码易读
    返回值：
        类型：int
        意义：接口里的键值
    参数：没有
*///
uint8_t get_key_value(){
  return MainEventManager.keybord_status->key_enum;
}




/*
    函数名字：get_last_key
    函数功能：检测是否松手并返回最近一次松手时按键的值（多线程用不了），然后销毁这个值
    返回值：
        类型：int
        意义：接口里的最近一次松手时按键的值（没松手/没动静都返回0）
    参数：没有
*///
uint8_t get_last_key(){

  static int key;
  static int last_key;

  key = get_key_value();
  //检测按键是否松开
  if( key != (int)KEY_NULL ){//如果没有松开
    last_key = key;//记录此时的值
    return 0;
  }else{//如果松开了
    key = last_key;//初始化
    last_key = 0;
    return key;
  }
}




/*
    函数名字：image_to_display_info
    函数功能：把128x64的char图片数组塞进一个display_info类型的结构里
    返回值：
        类型：display_info
        意义：返回需要渲染的图片
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
void do_nothing(){
  
}