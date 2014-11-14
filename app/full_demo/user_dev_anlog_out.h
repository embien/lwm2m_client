/*! \file 
  \brief      Header implementing neccessary declarations for user specific IPSO analog output object 
   
   Contains macros, structures and declarations for the user specific implemtation of the IPSO analog output object implementation
*/
#ifndef USER_DEV_ANLOG_OUT_H
#define USER_DEV_ANLOG_OUT_H

#include <lwm2m_client.h>

#define LWM2M_USER_DEV_ANLOG_OUT_RES_MAX                2
#define LW_RES_ANLOG_INPUT_CURRENT_VALUE_MAX_RANGE      5

#define LWM2M_USER_DEV_FLOAT_MAX_SIZE         30
#define LWM2M_USER_DEV_STRING_MAX_RANGE       30
extern LWM2M_OBJECT_RES_INFO user_dev_anlog_out_res_info [LWM2M_USER_DEV_ANLOG_OUT_RES_MAX]; 

#endif