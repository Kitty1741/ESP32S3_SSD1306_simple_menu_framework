#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu\menu.h>


//这个文件放用来计算菜单和列表显示的函数







/*
    函数名字：set_cursor
    函数功能：根据接口里的键值，设置光标
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        MENU
        类型：menu*
        作用：告诉函数菜单的长度和用来设置谁的光标
*///
bool set_cursor( menu *MENU ){

  static int key;

  //检测按键是否松开
  if( MainEventManager.keybord_status->key_enum != KEY_NULL ){//如果没有松开
    key = MainEventManager.keybord_status->key_enum;//记录此时的值
  }else{//如果松开了
    
    //根据输入的键值确定光标移动/其他操作
    switch( key ){
      case KEY_NULL:break;
      case KEY_UP_NUM:{//光标上移
        MENU->cursor != 0 ?
        MENU->cursor -- : MENU->cursor = MENU->length - 1 ;
      }break;
      case KEY_OK_NUM:{//进入光标所指选项
        MENU->list[MENU->cursor].fun();
        menu_init();//完事还原默认设置
      }break;
      case KEY_DOWN_NUM:{//光标下移
        MENU->cursor != MENU->length -1 ?
        MENU->cursor ++ : MENU->cursor = 0 ;
      }break;
      case KEY_BACK_NUM:{//返回
        MENU->cursor = 0;
        return true;
      }break;
    }key = KEY_NULL;
  }
  return false;
}