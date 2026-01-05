#include <Arduino.h>
#include <driver/timer.h>
#include <Ticker.h>

#include <keybord/keybord.h>
#include <global.h>


extern int (* user_scan_once)();//单次扫描，返回键值，通常在user_scan_keybord中被调用一次(没有也行)
extern void (* user_scan_keybord)();//定时中断调用的扫描函数,直接更改系统键值
extern void (* user_init_keybord)();//初始化键盘的硬件

#if ( use_which_timer == 4 )
Ticker keyScanner;
#endif

void init_keybord_timer();

//这个程序只定义了一个初始化函数，里面塞上了所有和键盘有关的初始化函数
void keybord_setup(){

    //初始化扫键盘的定时器的函数
    init_keybord_timer();

    //用户自定义的初始化函数
    user_init_keybord();
}




//初始化定时器(setting.h里指定的定时器)
//这个别改
void init_keybord_timer(){

  hw_timer_t *timer = NULL;
  switch(use_which_timer){
    case 5:break;
    case 4:{//选择软件定时器
      #if ( use_which_timer == 4 )
      keyScanner.attach_ms( 20 , user_scan_keybord );//每20ms执行一次“scan_keybord”对应的函数
      #endif
    }break;
    default:{//选择硬件定时器
      timer = timerBegin( use_which_timer , 80 , true );//初始化对应硬件定时器
      timerAttachInterrupt( timer , user_scan_keybord, false );//用于将中断处理函数与特定的定时器关联起来
      timerAlarmWrite( timer, 40000 , true );//用于设置定时器的计数值
      timerAlarmEnable(timer);  // 启动定时器！
    }break;            /*对于40000↑说明：0.02s*(160MHZ/分频系数)*/
  }
}





/*
    函数名字：get_key_value
    函数功能：返回接口里的键值，使代码易读
    返回值：
        类型：uint8_t
        意义：接口里的键值
    参数：没有
*///
uint8_t get_key_value(){
  return MainEventManager.keybord_status->key_enum;
}


/*
    函数名字：get_press_time
    函数功能：返回接口里的按键按下时间，使代码易读
    返回值：
        类型：uint8_t
        意义：接口里的按键按下时间(单位毫秒)
    参数：没有
*///
uint8_t get_press_time(){
  return MainEventManager.keybord_status->press_time;
}




/*
    函数名字：get_last_key
    函数功能：检测是否松手并返回最近一次松手时按键的值（多线程用不了），然后销毁这个值
    返回值：
        类型：uint8_t
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
