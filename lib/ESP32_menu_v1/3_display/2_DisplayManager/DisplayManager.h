#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include "3_display/display_struct.h"

void DisplayManager_init();

bool display_set( display_info *INFO );
void display_refresh();

#endif