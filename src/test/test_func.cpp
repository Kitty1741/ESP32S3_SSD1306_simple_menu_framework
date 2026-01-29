

#include "menu_API.h"


bool show_time( void* no_param ){

  //初始化
  
  bool if_break = false;
  static char time_init;
  static unsigned int time_zzl;//变量名冲突的无奈之举
  static unsigned int add_num;
  unsigned int num;
  char str[20];

  while( get_key_value() );//防止进来就不小心改了时间

  if(time_init != 1){
    time_init = 1;
    add_num = 0;
    time_zzl = 0;
  }

  if( add_num > 3600*24 ){
    add_num -= 3600*24;
  }

  while(1){

    time_zzl = millis() / 1000;//运行的秒数


    u8g2.setDrawColor(1); //设置颜色,0透显,1实显,2XOR (drawCircle,drawDisc,drawEllipse和drawFilledEllipse不支持XOR模式)
    u8g2.clearBuffer();    // 清Buffer缓冲区的数据

    u8g2.setFont(u8g2_font_ncenB08_tr);  // 设置字体:cite[5]
    u8g2.setFont(u8g2_font_wqy12_t_gb2312); // 设置文泉驿点阵宋体12px:cite[2]

    u8g2.drawUTF8(3 ,3 ,"时间" );
    u8g2.drawFrame(0, 1, 128, 16); //画空心矩形
    u8g2.drawUTF8( 70 ,50 ,"4.退出" );

    u8g2.setFont(u8g2_font_ncenB14_tr);  // 设置大一点的字号
    
    
    for(int i=0;i<3;i++){

      num = time_zzl + add_num;

      switch(i){
        case 0:{//显示小时
          num = num/3600%24;
        };break;
        case 1:{//显示分钟
          num = num/60%60;
        };break;
        case 2:{//显示秒
          num = num%60;
        };break;
      }

      sprintf(str,"%02u",num);//把num转换为字符串后写入str
      u8g2.drawUTF8(6+36*i ,24 ,str );
    } u8g2.drawUTF8( 32 ,24 ,":" );
      u8g2.drawUTF8( 68 ,24 ,":" );

    u8g2.sendBuffer();    // 将Buffer帧缓冲区的内容发送到显示器,发送刷新消息

    switch( get_first_key() ){
        case KEY_NULL:break;
        case KEY_UP_NUM:add_num ++;break;
        case KEY_OK_NUM:add_num += 60;break;
        case KEY_DOWN_NUM:add_num += 3600;break;
        case KEY_BACK_NUM:if_break = true;break;
    }if(if_break)break;
  }
  u8g2_print_init();
  return true;
}