#ifndef __API_FUNCTION_H__
#define __API_FUNCTION_H_


bool do_nothing( void* do_nothing );
display_info image_to_display_info( char IMAGE[1024] );
display_info menu_to_display_info(menu *MENU);
display_info list_to_display_info(list *LIST);

//recall
bool run_info(void* param);
bool run_list(void* param);
bool run_menu(void* param);

#endif