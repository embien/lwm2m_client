/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO power measurement object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO power measurement object implementation
*/

#ifndef USER_DEV_POWER_MES_H
#define USER_DEV_POWER_MES_H

#include <lwm2m_client.h>
#define LWM2M_USER_DEV_POWER_MES_RES_MAX    1

#define LWM2M_USER_DEV_FLOAT_MAX_SIZE    30

extern LWM2M_OBJECT_RES_INFO user_dev_power_mes_res_info [LWM2M_USER_DEV_POWER_MES_RES_MAX]; 

#endif 
 






