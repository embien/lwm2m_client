/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO power measurement object
   
   Contains the logic for implementing the instances for IPSO power measurement  object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_power_mes_inst_list [LW_MAX_INST_IPSO_POWER_MES] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_power_mes_res_info
 }
};
