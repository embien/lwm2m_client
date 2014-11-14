/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO humidity sensor object
  
   Contains the logic for implementing the instances for IPSO humidity sensor  object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_humid_sen_inst_list [LW_MAX_INST_IPSO_HUMID_SEN] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_humid_sen_res_info
 }
};
