#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>
#include "user_defined.h"


//这个文件用来写用户定义的函数
//测试用函数
bool test_print_num( void* num_address ){

    uint32_t num = *(uint32_t*)num_address;

    int key;
    char str[64];
    sprintf( str , "%d" , millis() );
    static list NUM_LIST;
    NUM_LIST.list[0] = str;
    NUM_LIST.list[1] = "meow";
    static display_info NUM_LIST_INFO;
    NUM_LIST_INFO = config_list_display_info( &NUM_LIST );
    NUM_LIST_INFO.x = 50;
    NUM_LIST_INFO.y = 20;

    u8g2_print_display_info( &NUM_LIST_INFO );

    key = get_last_key();
    if(key == KEY_BACK_NUM)
    return true ; return false ;
}