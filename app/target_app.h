/*! \file 
  \brief      Header implementing neccessary inclusion of the header file 
  
  Contains header file for whole project
*/

#ifndef TARGET_APP_H
#define TARGET_APP_H

#if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_FULL_DEMO
#include "full_demo/console_demo.h"
#endif
#if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_XOR_DEMO
#include "xor_demo/process_xor_demo.h"
#endif

int init_target_app ();
void target_app_task ();

#endif 
