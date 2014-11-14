/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M state  process 
  
  Contains macros, structures and declarations for LWM2M state process 
*/

#ifndef LWM2M_COAP_TASK_H
#define LWM2M_COAP_TASK_H

#define LWM2M_CLIENT_IDLE                            0  /*!< LWM2M state process to send registration request  */
#define LWM2M_CLIENT_STATE_SEND_REG_REQ              1  /*!< LWM2M state process to send registration request  */
#define LWM2M_CLIENT_STATE_WAIT_FOR_REG_RESP         2  /*!< LWM2M state process to wait registration response */
#define LWM2M_CLIENT_STATE_COMM                      3  /*!< LWM2M state process to communicate between client and server */

//int init_lwm2m_client_task ();
//INT8U server_register_id;
#endif
