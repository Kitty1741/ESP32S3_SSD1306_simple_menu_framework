#include <Arduino.h>
#include <global.h>
#include <keybord\keybord.h>
#include <setting.h>
#include <Ticker.h>
#include <driver/timer.h>

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