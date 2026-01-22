#ifndef __TO_DISPLAY_INFO_PRIVATE__
#define __TO_DISPLAY_INFO_PRIVATE__

//包含下层结构声明
#include "3_display/display_struct.h"

display_info image_to_display_info( image* IMAGE , uint8_t x , uint8_t y);
display_info menu_to_display_info(  menu *MENU );
display_info list_to_display_info(  list *LIST );

#endif