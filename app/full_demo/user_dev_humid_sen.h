/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO humidity sensor object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO humidity sensor object implementation
*/
#ifndef USER_DEV_HUMID_SEN_H
#define USER_DEV_HUMID_SEN_H

#include <lwm2m_client.h>

#define LWM2M_USER_DEV_HUMID_SEN_RES_MAX    1

#define LWM2M_USER_DEV_FLOAT_MAX_SIZE    30

extern LWM2M_OBJECT_RES_INFO user_dev_humid_sen_res_info [LWM2M_USER_DEV_HUMID_SEN_RES_MAX]; 

#endif 






