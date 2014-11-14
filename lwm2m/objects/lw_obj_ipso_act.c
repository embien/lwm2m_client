
/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO actuation object
  
   Contains the logic for implementing the instances for IPSO actuation object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_act_inst_list [LW_MAX_INST_IPSO_ACT] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_act_res_info
 }
};
