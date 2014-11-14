/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO set point object 
  
   Contains macros, structures and declarations for the user specific implemtation of the IPSO set point object implementation
*/

#ifndef USER_DEV_SET_POINT_H
#define USER_DEV_SET_POINT_H

#include <lwm2m_client.h>

#define LWM2M_USER_DEV_SET_POINT_RES_MAX    2


#define LWM2M_USER_DEV_FLOAT_MAX_SIZE    30

extern LWM2M_OBJECT_RES_INFO user_dev_set_point_res_info [LWM2M_USER_DEV_SET_POINT_RES_MAX]; 

#endif
