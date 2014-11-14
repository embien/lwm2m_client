/*! \file 
  \brief    Header implementing neccessary declarations for console application 
  
  Contains macros, structures and declarations for CoAP message packet information
*/

#ifndef CONSOLE_DEMO_H
#define CONSOLE_DEMO_H

/*! structure member declaration for console application */
typedef struct __console_demo_app
{
  INT8U u8_state;
  /*INT8U u8_sc_cmd;
  INT8U current_level;
  INT8U u8_cmd_option;
  INT8U process;
  INT8U cmd_flag;
  INT8U cmd_mode;
  int last_level;
  int value;
  INT8U u8_dis_mode;*/
} CONSOLE_DEMO_APP;

#define LWM2M_OBJ_SUPPORT_IPSO_ACCE_METER                     0  /*!< LWM2M client enable or disalbe the IPSO accelerometer objects */ 
#define LWM2M_OBJ_SUPPORT_IPSO_ACT                            0  /*!< LWM2M client enable or disalbe the IPSO actuation objects */
#define LWM2M_OBJ_SUPPORT_IPSO_ANLOG_IN                       0  /*!< LWM2M client enable or disalbe the IPSO analog input  objects */
#define LWM2M_OBJ_SUPPORT_IPSO_ANLOG_OUT                      0  /*!< LWM2M client enable or disalbe the IPSO analog output objects */
#define LWM2M_OBJ_SUPPORT_IPSO_BARO_METER                     0  /*!< LWM2M client enable or disalbe the IPSO barometer objects */
#define LWM2M_OBJ_SUPPORT_IPSO_DIG_IN                         1  /*!< LWM2M client enable or disalbe the IPSO digital input objects */
#define LWM2M_OBJ_SUPPORT_IPSO_DIG_OUT                        1  /*!< LWM2M client enable or disalbe the IPSO digital output objects */
#define LWM2M_OBJ_SUPPORT_IPSO_GEN_SEN                        0  /*!< LWM2M client enable or disalbe the IPSO generic sensor objects */
#define LWM2M_OBJ_SUPPORT_IPSO_HUMID_SEN                      0  /*!< LWM2M client enable or disalbe the IPSO humidity sensor objects */
#define LWM2M_OBJ_SUPPORT_IPSO_LIGHT_CON              0  /*!< LWM2M client enable or disalbe the IPSO light control objects */
#define LWM2M_OBJ_SUPPORT_IPSO_LOAD_CON                  0  /*!< LWM2M client enable or disalbe the IPSO load control  objects */
#define LWM2M_OBJ_SUPPORT_IPSO_LUMIN_SEN                      0  /*!< LWM2M client enable or disalbe the IPSO luminosity sensor objects */
#define LWM2M_OBJ_SUPPORT_IPSO_MAG_METER                      0  /*!< LWM2M client enable or disalbe the IPSO magnometer  objects */
#define LWM2M_OBJ_SUPPORT_IPSO_POWER_CON                      0  /*!< LWM2M client enable or disalbe the IPSO power control  objects */
#define LWM2M_OBJ_SUPPORT_IPSO_POWER_MES                      0  /*!< LWM2M client enable or disalbe the IPSO power measurement objects */
#define LWM2M_OBJ_SUPPORT_IPSO_PRES_SEN                       0  /*!< LWM2M client enable or disalbe the IPSO presence sensor objects */
#define LWM2M_OBJ_SUPPORT_IPSO_SET_POINT                      0  /*!< LWM2M client enable or disalbe the IPSO set point objects */
#define LWM2M_OBJ_SUPPORT_IPSO_TEMP_SEN                       0  /*!< LWM2M client enable or disalbe the IPSO temperature sensor objects */
#define LWM2M_OBJ_SUPPORT_OMA_LOCATION                        0  /*!< LWM2M client enable or disalbe the IPSO location objects */

#define LWM2M_MAX_SUPPORTED_OBJECTS                           2 /*!< LWM2M maximum supported object list */

#define LW_MAX_INST_IPSO_ACCE_METER                           1  /*!< LWM2M  maximum instance list for IPSO accelerometer object */
#define LW_MAX_INST_IPSO_ACT                                  1  /*!< LWM2M  maximum instance list for IPSO actuation object */
#define LW_MAX_INST_IPSO_ANLOG_IN                             1  /*!< LWM2M  maximum instance list for IPSO analog input  object */
#define LW_MAX_INST_IPSO_ANLOG_OUT                            1  /*!< LWM2M  maximum instance list for IPSO analog output object */
#define LW_MAX_INST_IPSO_BARO_METER                           1  /*!< LWM2M  maximum instance list for IPSO barometer object */
#define LW_MAX_INST_IPSO_DIG_IN                               2  /*!< LWM2M  maximum instance list for IPSO digital input object */
#define LW_MAX_INST_IPSO_DIG_OUT                              1  /*!< LWM2M  maximum instance list for IPSO digital output object */
#define LW_MAX_INST_IPSO_GEN_SEN                              1  /*!< LWM2M  maximum instance list for IPSO generic sensor object */
#define LW_MAX_INST_IPSO_HUMID_SEN                            1  /*!< LWM2M  maximum instance list for IPSO humidity sensor object */
#define LW_MAX_INST_IPSO_LIGHT_CON                            1  /*!< LWM2M  maximum instance list for IPSO light control object */
#define LW_MAX_INST_IPSO_LOAD_CON                             1  /*!< LWM2M  maximum instance list for IPSO load control  object */
#define LW_MAX_INST_IPSO_LUMIN_SEN                            1  /*!< LWM2M  maximum instance list for IPSO luminosity sensor object */
#define LW_MAX_INST_IPSO_MAG_METER                            1  /*!< LWM2M  maximum instance list for IPSO magnometer  object */
#define LW_MAX_INST_IPSO_POWER_CON                            1  /*!< LWM2M  maximum instance list for IPSO power control  object */
#define LW_MAX_INST_IPSO_POWER_MES                            1  /*!< LWM2M  maximum instance list for IPSO power measurement object */
#define LW_MAX_INST_IPSO_PRES_SEN                             1  /*!< LWM2M  maximum instance list for IPSO presence sensor object */
#define LW_MAX_INST_IPSO_SET_POINT                            1  /*!< LWM2M  maximum instance list for IPSO set point object */
#define LW_MAX_INST_IPSO_TEMP_SEN                             1  /*!< LWM2M  maximum instance list for IPSO temperature sensor object */
#define LW_MAX_INST_OMA_LOCATION                              1  /*!< LWM2M  maximum instance list for IPSO location object */
 
#include "user_dev_objects.h"

int console_app_task ();
#endif
