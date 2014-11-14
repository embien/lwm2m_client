/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO presence   sensor object
   
   Contains the logic for implementing the instances for IPSO presence sensor  object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_pres_sen_inst_list [LW_MAX_INST_IPSO_PRES_SEN] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_pres_sen_res_info
 }
};
