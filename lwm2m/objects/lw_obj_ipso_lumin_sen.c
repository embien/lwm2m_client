/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO luminosity sensor object
   
   Contains the logic for implementing the instances for IPSO luminosity sensor  object 
*/


#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_lumin_sen_inst_list [LW_MAX_INST_IPSO_LUMIN_SEN] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_lumin_sen_res_info
 }
};
