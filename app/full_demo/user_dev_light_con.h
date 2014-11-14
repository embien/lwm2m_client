/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO light control object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO light control object implementation
*/


#ifndef USER_DEV_LIGHT_CON_H
#define USER_DEV_LIGHT_CON_H

#include <lwm2m_client.h>                  

#define LWM2M_USER_DEV_LIGHT_CON_RES_MAX    1
#define LW_RES_ON_OFF_MAX_RANGE             1 

 

extern LWM2M_OBJECT_RES_INFO user_dev_light_con_res_info [LWM2M_USER_DEV_LIGHT_CON_RES_MAX]; 

#endif