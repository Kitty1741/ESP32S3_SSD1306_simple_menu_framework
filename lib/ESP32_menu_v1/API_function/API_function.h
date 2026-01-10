#ifndef __API_FUNCTION_H__
#define __API_FUNCTION_H_


display_info image_to_display_info( image* IMAGE , ...);
display_info menu_to_display_info(  menu *MENU );
display_info list_to_display_info(  list *LIST );
void link_info(display_info* A,display_info* B);

//recall
bool run_info_data(void* param);
bool run_list(void* param);
bool run_menu(void* param);
bool do_nothing( void* do_nothing );

#endif