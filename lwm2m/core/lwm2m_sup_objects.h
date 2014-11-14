/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M objects  
  
  Contains macros, structures and declarations for user specific LWM2M objects 
*/

#ifndef LWM2M_SUP_OBJECTS_H
#define LWM2M_SUP_OBJECTS_H
 
#if LWM2M_OBJ_SUPPORT_IPSO_ACCE_METER
#define LWM2M_OBJ_ID_IPSO_ACCE_METER 			                    3313   /*< LWM2M accelerometer object id */
#include <lw_obj_ipso_acce_meter.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_ACT
#define LWM2M_OBJ_ID_IPSO_ACT                                  3306  /*< LWM2M actuation object id */
#include <lw_obj_ipso_act.h>
#endif 

#if LWM2M_OBJ_SUPPORT_IPSO_ANLOG_IN  
#define LWM2M_OBJ_ID_IPSO_ANLOG_IN 			                       3202    /*< LWM2M analog input object id */
#include <lw_obj_ipso_anlog_in.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_ANLOG_OUT  
#define LWM2M_OBJ_ID_IPSO_ANLOG_OUT 			                      3203    /*< LWM2M analog output object id */
#include <lw_obj_ipso_anlog_out.h>
#endif


#if LWM2M_OBJ_SUPPORT_IPSO_BARO_METER
#define LWM2M_OBJ_ID_IPSO_BARO_METER 			                      3315   /*< LWM2M barometer object id */
#include <lw_obj_ipso_baro_meter.h>
#endif


#if LWM2M_OBJ_SUPPORT_IPSO_DIG_IN  
#define LWM2M_OBJ_ID_IPSO_DIG_IN 			                  3200    /*< LWM2M digital input object id */
#include <lw_obj_ipso_dig_in.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_DIG_OUT  
#define LWM2M_OBJ_ID_IPSO_DIG_OUT 			                  3201    /*< LWM2M digital output object id */
#include <lw_obj_ipso_dig_out.h>
#endif
 
#if LWM2M_OBJ_SUPPORT_IPSO_GEN_SEN  
#define LWM2M_OBJ_ID_IPSO_GEN_SEN 			                  3300  /*< LWM2M generic sensor object id */
#include <lw_obj_ipso_gen_sen.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_HUMID_SEN  
#define LWM2M_OBJ_ID_IPSO_HUMID_SEN 			                  3304  /*< LWM2M humidity sensor object id */
#include <lw_obj_ipso_humid_sen.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_LIGHT_CON 
#define LWM2M_OBJ_ID_IPSO_LIGHT_CON				                    3311 /*< LWM2M light control object id */
#include <lw_obj_ipso_light_con.h>
#endif


#if LWM2M_OBJ_SUPPORT_IPSO_LOAD_CON 
#define LWM2M_OBJ_ID_IPSO_LOAD_CON				                    3310 /*< LWM2M load control  object id */
#include <lw_obj_ipso_load_con.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_LUMIN_SEN  
#define LWM2M_OBJ_ID_IPSO_LUMIN_SEN 			                   3301  /*< LWM2M luminosity sensor object id */
#include <lw_obj_ipso_lumin_sen.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_MAG_METER
#define LWM2M_OBJ_ID_IPSO_MAG_METER 			                    3314   /*< LWM2M magnometer  object id */
#include <lw_obj_ipso_mag_meter.h>
#endif



#if LWM2M_OBJ_SUPPORT_IPSO_POWER_CON 
#define LWM2M_OBJ_ID_IPSO_POWER_CON 			                    3312   /*< LWM2M power control  object id */
#include <lw_obj_ipso_power_con.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_POWER_MES
#define LWM2M_OBJ_ID_IPSO_POWER_MES                          3305  /*< LWM2M power measurement object id */
#include <lw_obj_ipso_power_mes.h>
#endif 
#if LWM2M_OBJ_SUPPORT_IPSO_PRES_SEN  
#define LWM2M_OBJ_ID_IPSO_PRES_SEN 			                  3302  /*< LWM2M presence sensor object id */
#include <lw_obj_ipso_pres_sen.h>
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_SET_POINT                
#define LWM2M_OBJ_ID_IPSO_SET_POINT                           3308 /*< LWM2M set point object id */
#include <lw_obj_ipso_set_point.h>
#endif  

#if LWM2M_OBJ_SUPPORT_IPSO_TEMP_SEN  
#define LWM2M_OBJ_ID_IPSO_TEMP_SEN 			                  3303  /*< LWM2M temperature sensor object id */
#include <lw_obj_ipso_temp_sen.h>
#endif  


#if LWM2M_OBJ_SUPPORT_OMA_LOCATION  
#define LWM2M_OBJ_ID_OMA_LOCATION 			                  6  /*< LWM2M location object id */
#include <lw_obj_oma_loc.h>
#endif  

#endif