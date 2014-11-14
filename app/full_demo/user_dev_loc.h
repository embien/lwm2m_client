/*! \file 
  \brief      Header implementing neccessary declarations for user specific LWM2M location object 
  
   Contains macros, structures and declarations for the user specific implemtation of the LWM2M location object implementation
*/

#ifndef USER_DEV_LOC_H
#define USER_DEV_LOC_H
#include <lwm2m_object.h>

#define LWM2M_USER_DEV_LOC_RES_MAX                        1
#define LWM2M_OMA_LOC_LATITUDE_MAX_RANGE            30 
 

extern LWM2M_OBJECT_RES_INFO user_dev_loc_res_info [LWM2M_USER_DEV_LOC_RES_MAX]; 

#endif