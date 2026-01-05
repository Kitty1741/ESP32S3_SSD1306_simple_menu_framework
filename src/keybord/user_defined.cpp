#include <Arduino.h>
#include <global.h>
#include <keybord/keybord.h>
#include "keybord/user_defined.h"

//用户可以自己定义的函数放在这里


//把你自己的单次键盘扫描函数放在这里                 |
//这里的函数由你自己调用，if你不用也可以空着         |
//只要你的扫描-传值函数正常工作就行了                ↓
int (* user_scan_once)() = default_scan_once_function;

//把你自己的完整键盘 扫描-传值 函数放在这里  |
//这里的函数会定时被timer中断执行           ↓
void (* user_scan_keybord)() = default_scan_function;

//把你自己的键盘初始化函数放在这|
//这里的函数会定时被setup()执行 ↓
void (* user_init_keybord)() = default_init_function;




//下面是默认的键盘扫描函数，用户根据自己需求修改

//简单的键盘扫描函数
//功能：在中断中扫描键盘然后赋值给MainEventManager.keybord_status
void default_scan_function(){
  static int key_value;//防止频繁入栈出栈影响性能
  static int press_time;

  //扫描和计时
  key_value = user_scan_once();
  key_value == KEY_NULL ?
  press_time = KEY_NULL :
  press_time += 20 ;

  //直接把数据打入公共结构
  MainEventManager.keybord_status->key_enum = key_value;
  MainEventManager.keybord_status->key_value = key_value;
  MainEventManager.keybord_status->press_time = press_time;

  return;
}

//初始化键盘引脚10 11 12 13
void default_init_function(){
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(13,INPUT_PULLUP);
}

//扫描键盘返回键值1 2 3 4
//键盘在10 11 12 13引脚上
int default_scan_once_function(){
  if     ( digitalRead(10) == 0 ){return (int)KEY_UP_NUM;}
  else if( digitalRead(11) == 0 ){return (int)KEY_OK_NUM;}
  else if( digitalRead(12) == 0 ){return (int)KEY_DOWN_NUM;}
  else if( digitalRead(13) == 0 ){return (int)KEY_BACK_NUM;}
  else{
    return KEY_NULL;
  }
}





