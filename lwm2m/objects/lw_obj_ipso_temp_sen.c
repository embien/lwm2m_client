/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO temperature sensor object
   
   Contains the logic for implementing the instances for IPSO temperature sensor  object 
*/


#include <lwm2m_client.h>
LWM2M_OBJECT_INST_INFO lw_obj_ipso_temp_sen_inst_list [LW_MAX_INST_IPSO_TEMP_SEN] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_temp_sen_res_info
 }
};
