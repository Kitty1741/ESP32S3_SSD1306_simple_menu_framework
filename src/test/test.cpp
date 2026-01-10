#include <menu_API.h>

#include "image.h"

void test_init(){
    Serial.println("test");
    link_info( &MAIN_MENU_INFO , &image_info );
    link_info( &MAIN_MENU_INFO , &cat1_info );
}
INIT(test);