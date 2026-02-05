#include <Arduino.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <menu_API.h>

#include "connection_internal.h"
#include "connection.h"

char wifi_ssid[32][32];//储存wifi名字的数组

CREATE_MENU(connection,{
    {"刷新",scan_wifi,NULL},
    {wifi_ssid[ 0],show_wifi_info,(void*) 0},{wifi_ssid[ 1],show_wifi_info,(void*) 1},
    {wifi_ssid[ 2],show_wifi_info,(void*) 2},{wifi_ssid[ 3],show_wifi_info,(void*) 3},
    {wifi_ssid[ 4],show_wifi_info,(void*) 4},{wifi_ssid[ 5],show_wifi_info,(void*) 5},
    {wifi_ssid[ 6],show_wifi_info,(void*) 6},{wifi_ssid[ 7],show_wifi_info,(void*) 7},
    {wifi_ssid[ 8],show_wifi_info,(void*) 8},{wifi_ssid[ 9],show_wifi_info,(void*) 9},
    {wifi_ssid[10],show_wifi_info,(void*)10},{wifi_ssid[11],show_wifi_info,(void*)11},
    {wifi_ssid[12],show_wifi_info,(void*)12},{wifi_ssid[13],show_wifi_info,(void*)13},
    {wifi_ssid[14],show_wifi_info,(void*)14},{wifi_ssid[15],show_wifi_info,(void*)15},
    {wifi_ssid[16],show_wifi_info,(void*)16},{wifi_ssid[17],show_wifi_info,(void*)17},
    {wifi_ssid[18],show_wifi_info,(void*)18},{wifi_ssid[19],show_wifi_info,(void*)19},
    {wifi_ssid[20],show_wifi_info,(void*)20},{wifi_ssid[21],show_wifi_info,(void*)21},
    {wifi_ssid[22],show_wifi_info,(void*)22},{wifi_ssid[23],show_wifi_info,(void*)23},
    {wifi_ssid[24],show_wifi_info,(void*)24},{wifi_ssid[25],show_wifi_info,(void*)25},
    {wifi_ssid[26],show_wifi_info,(void*)26},{wifi_ssid[27],show_wifi_info,(void*)27},
    {wifi_ssid[28],show_wifi_info,(void*)28},{wifi_ssid[29],show_wifi_info,(void*)29},
    {wifi_ssid[30],show_wifi_info,(void*)30},{wifi_ssid[31],show_wifi_info,(void*)31},
})
CREATE_NODE(connection_menu)

//初始化
void connection_init(){
    for(uint8_t i=0;i<32;i++)
    wifi_ssid[i][0] = '\n';
}
INIT(connection)

//这个函数用来刷新wifi并写入数组
void scan_wifi( void* no_param ){

    //扫描
    uint8_t wifi_num = WiFi.scanNetworks(true);//异步
    
    while( WiFi.scanComplete() == -1 ){
        vTaskDelay(20);//等待扫描完成
        display_set( &loading );
        display_refresh();
    }
        
    
    if( WiFi.scanComplete() == -2 ){
        strcpy( wifi_ssid[0] , "! 扫描失败 !" );
        return;
    }
        
    //设置最多存储32wifi
    wifi_num > 32 ? wifi_num = 32 : wifi_num ;

    //写入数组
    for (uint8_t i=0;i<wifi_num;i++){
        strncpy( wifi_ssid[i] , WiFi.SSID(i).c_str() , 32 );
    }
}

//输入密码的函数
//在参数中返回密码
void enter_password( String pwd , bool* if_return ){

    char c_pwd[17] = {52,52,52,52,52,52,52,52,32,32,32,32,32,32,32,32,0};
    uint8_t cursor = 0;
    CREATE_SETTING(
        pwd,
        SETTING_MODE_UCHAR,
        &c_pwd[cursor],
        32,126
    )CREATE_NODE(pwd_setting)

    bool if_break = false;
    while( !if_break ){
        //打印
        M_DISPLAY(

            char str[2] = {0,0};

            u8g2.drawUTF8( 4 , 2 , "请输入密码" );
            for( uint8_t j=0;j<16;j++ ){
                str[0] = c_pwd[j];
                u8g2.drawUTF8( 4 + 7*j , 20 , str );
                if( j == cursor )
                    u8g2.drawBox( 3+7*j , 29 , 8 , 2 );
            }
            u8g2.drawUTF8( 4 , 50 , "长按.2确认密码" );
        )

        //按键检测
        switch( get_last_key() ){
            case KEY_UP_NUM:
                cursor > 0 ?
                cursor--:cursor;
            break;
            case KEY_DOWN_NUM:
                cursor < 15 ?
                cursor++:cursor;
            break;
            case KEY_OK_NUM:{
                if( get_last_press_time() > LONG_PRESS_THRESHOLD ){//长按确认输入
                    if_break = true;break;
                }
                //短按输入单个密码
                set_setting_object(&pwd_setting,&c_pwd[cursor]);
                run_node(&pwd_setting_node);break;
            }break;
            case KEY_BACK_NUM:
                if_break = true;
                *if_return = true;
            break;
        }
        vTaskDelay(20);
    }

    for(uint8_t j=0;j<16;j++){
        if(c_pwd[j]==32)c_pwd[j]='\0';
    }pwd = c_pwd;
}

//打印连接wifi的状态
void print_conn_status(){

    bool if_break = false;
    while( !if_break ){
        //打印
        M_DISPLAY(
            u8g2.drawUTF8( 4 , 2 , "尝试连接..." );
            switch( WiFi.status() ){
                case WL_IDLE_STATUS       :u8g2.drawUTF8( 4 , 16 , "尝试连接" );break;
                case WL_NO_SSID_AVAIL	  :u8g2.drawUTF8( 4 , 16 , "找不到WiFi/密码错误" );break;
                case WL_SCAN_COMPLETED	  :u8g2.drawUTF8( 4 , 16 , "扫描完成" );break;
                case WL_CONNECTED	      :u8g2.drawUTF8( 4 , 16 , "连接成功" );break;
                case WL_CONNECT_FAILED	  :u8g2.drawUTF8( 4 , 16 , "连接失败" );break;
                case WL_CONNECTION_LOST	  :u8g2.drawUTF8( 4 , 16 , "连接丢失/距离过远" );break;
                case WL_DISCONNECTED	  :u8g2.drawUTF8( 4 , 16 , "未连接" );break;
            }   
        )

        //按键检测
        switch( get_last_key() ){
            case KEY_OK_NUM:
            case KEY_BACK_NUM:if_break = true;break;
        }
        vTaskDelay(20);
    }
}

//设置连接wifi 
//wifi索引,是否输入密码
void connect_wifi( String ssid , bool if_pwd = false){

    String pwd = "";
    bool if_return = false;

    //输入密码
    if( if_pwd ){
        enter_password( pwd , &if_return );
        if( if_return ) 
            return;
    }
        
    

    //连接
    WiFi.begin( ssid , pwd );
    print_conn_status();
}

//这个函数用来查看当前wifi
//param:列表中第几个wifi(不是指针)
void show_wifi_info( void* param ){
    
    uint32_t wifi_index = (uint32_t)param;
    char rssi[32];
    uint8_t encrypt_mode = WiFi.encryptionType(wifi_index);

    //刷新信息
    sprintf( rssi , "信号强度: %d" , WiFi.RSSI(wifi_index) );
    strcat( rssi , "dBm" );

    while(1){

        //打印
        M_DISPLAY(
            u8g2.drawUTF8( 4 , 2 , wifi_ssid[wifi_index] );
            u8g2.drawUTF8( 4 , 16 , rssi );
            switch(encrypt_mode){
                case WIFI_AUTH_OPEN:         u8g2.drawUTF8( 4 , 30 , "开放");break;
                case WIFI_AUTH_WEP:          u8g2.drawUTF8( 4 , 30 , "WEP");break;
                case WIFI_AUTH_WPA_PSK:      u8g2.drawUTF8( 4 , 30 , "WPA");break;
                case WIFI_AUTH_WPA2_PSK:     u8g2.drawUTF8( 4 , 30 , "WPA2");break;
                case WIFI_AUTH_WPA_WPA2_PSK: u8g2.drawUTF8( 4 , 30 , "WPA/WPA2");break;
                default: u8g2.drawUTF8( 4 , 30 , "未知加密类型");
            }
    
            u8g2.drawUTF8( 4 , 50 , "2.连接   4.退出" );
        )

        //按键检测
        
        switch( get_last_key() ){
            case KEY_OK_NUM:connect_wifi(
                wifi_ssid[wifi_index],
                (bool)encrypt_mode
            );
            case KEY_BACK_NUM:while( get_key_value() )vTaskDelay(20);return;
        }
    }
}