/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef PROCESS_XOR_OPER_H
#define PROCESS_XOR_OPER_H

extern int sc_get_next_command ();
extern void xor_app_task ();

typedef struct __skycase_xor_oper
{  
  INT8U  u8_registered;
  INT8U u8_xor_input_1;
  INT8U u8_xor_input_2;
  INT8U u8_update_inst;
  INT32U max_value;
  INT8U u8_register_count;
  int response_success_flag;
  INT32U resp_time_out_inst0;
  INT32U resp_time_out_inst1; 
} SKYCASE_XOR_OPER;
extern INT8U u8_last_request;
extern INT8U u8_last_process;

#define LWM2M_USER_DEV_DIG_IN_RES_MAX    1
#define LWM2M_USER_DEV_DIG_OUT_RES_MAX    1

#define LWM2M_OBJ_SUPPORT_IPSO_DIG_IN                         1  /*!< LWM2M client enable or disalbe the IPSO digital input objects */
#define LWM2M_OBJ_SUPPORT_IPSO_DIG_OUT                        1  /*!< LWM2M client enable or disalbe the IPSO digital */
#define LW_MAX_INST_IPSO_DIG_IN                               2  /*!< LWM2M  maximum instance list for IPSO digital input object */
#define LW_MAX_INST_IPSO_DIG_OUT                              1  /*!< LWM2M  maximum instance list for IPSO digital */

#define LWM2M_MAX_SUPPORTED_OBJECTS                           2 /*!< LWM2M maximum supported object list */

extern LWM2M_OBJECT_RES_INFO user_dev_dig_in_res_info [LWM2M_USER_DEV_DIG_IN_RES_MAX]; 
extern LWM2M_OBJECT_RES_INFO user_dev_dig_out_res_info [LWM2M_USER_DEV_DIG_OUT_RES_MAX]; 

#endif