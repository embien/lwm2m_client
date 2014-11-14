#include <lwm2m_client.h> 

#if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_FULL_DEMO
#include "full_demo/console_demo.c"
#endif
#if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_XOR_DEMO
#include "xor_demo/process_xor_demo.c"
#endif

int init_target_app ()
{
  #if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_FULL_DEMO
  return init_console_app_task (); 
  #endif
  #if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_XOR_DEMO
  return init_xor_app_task (); 
  #endif

}
void target_app_task ()
{
  #if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_FULL_DEMO
  console_app_task ();    
  #endif
  #if LWM2M_CLIENT_MAIN_APP == LWM2M_CLIENT_MAIN_APP_XOR_DEMO
  xor_app_task(); 
  #endif
}
