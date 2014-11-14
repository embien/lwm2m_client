/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO accelerometer object 
  
   Contains macros, structures and declarations for the user specific implemtation of the IPSO accelerometer object implementation
*/


#ifndef USER_DEV_ACCE_METER_H
#define USER_DEV_ACCE_METER_H

#include <lwm2m_client.h>

#define LWM2M_USER_DEV_ACCE_METER_RES_MAX    1


#define LWM2M_USER_DEV_FLOAT_MAX_SIZE        30

extern LWM2M_OBJECT_RES_INFO user_dev_acce_meter_res_info [LWM2M_USER_DEV_ACCE_METER_RES_MAX];

#endif