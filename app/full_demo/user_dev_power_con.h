/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO power control object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO power control object implementation
*/


#ifndef  USER_DEV_POWER_CON_H
#define  USER_DEV_POWER_CON_H

#include <lwm2m_client.h>
#define LWM2M_USER_DEV_POWER_CON_RES_MAX   3


extern LWM2M_OBJECT_RES_INFO user_dev_power_con_res_info[LWM2M_USER_DEV_POWER_CON_RES_MAX]; 

#endif