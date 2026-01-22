#ifndef __API_FUNCTION_H__
#define __API_FUNCTION_H_

//包含下层文件
#include "3_display/display_struct.h"

display_info image_to_display_info( image* IMAGE , ...);
display_info menu_to_display_info(  menu *MENU );
display_info list_to_display_info(  list *LIST );
void link_info(display_info* A,display_info* B);

#endif