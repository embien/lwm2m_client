/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO digital input object
  
   Contains the logic for implementing the instances for IPSO digital input object 
*/

#include <lwm2m_client.h>
LWM2M_OBJECT_INST_INFO lw_obj_ipso_dig_in_inst_list [LW_MAX_INST_IPSO_DIG_IN] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_dig_in_res_info
 },
 { 
   LWM2M_OBJ_INST_VALID,
   1,
   1,
   user_dev_dig_in_res_info
 }
};
