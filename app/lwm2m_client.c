/*! \file 
  \brief      Module implementing initialisation and starting communication with selected server
  
   Contains the logic for selecting communication and recursivly running the client task 
*/

#include <lwm2m_client.h>
#define SLEEP_DELAY_MS      10   /*!< Delay between two requests*/

/*! \fn        int lwm2m_client_main ()
    \brief     Initialise the selected communication and process accordingly for user command
    \param[in] None 
    \return    int         Zero on success  or error code on failure
*/
int lwm2m_client_main ()
{
  init_hal ();
  printf ("LWM2M Cllient Library for SkyCase/CoAP\r\n");
  #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
  init_lwm2m_udp_client ();  
  #endif
  #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
  init_lwm2m_http_client ();  
  #endif 
  init_target_app ();
  while (1)
  {
    #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
    lwm2m_udp_client_task ();
    #endif
    #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
    lwm2m_http_client_task ();
    #endif 
    target_app_task ();
    //lwm2m_client_resource_observe_task (2);
    lw_sleep_ms (SLEEP_DELAY_MS);
  }
}