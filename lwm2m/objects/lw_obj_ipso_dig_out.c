/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO digital output object
  
   Contains the logic for implementing the instances for IPSO digital output object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_dig_out_inst_list [LW_MAX_INST_IPSO_DIG_OUT] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_dig_out_res_info
 }
};
