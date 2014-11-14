/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO load control  object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO load control  object implementation
*/


#ifndef USER_DEV_LOAD_CON_H
#define USER_DEV_LOAD_CON_H
#include <lwm2m_object.h>

#define LWM2M_USER_DEV_LOAD_CON_RES_MAX                        2
#define LWM2M_IPSO_LOAD_CON_EV_IDENT_MAX_RANGE                 30 
 

extern LWM2M_OBJECT_RES_INFO user_dev_load_con_res_info [LWM2M_USER_DEV_LOAD_CON_RES_MAX]; 

#endif