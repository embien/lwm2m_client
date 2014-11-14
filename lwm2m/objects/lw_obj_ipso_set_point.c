/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO set point object
   
   Contains the logic for implementing the instances for IPSO set point  object 
*/

#include <lwm2m_client.h>
LWM2M_OBJECT_INST_INFO lw_obj_ipso_set_point_inst_list [LW_MAX_INST_IPSO_SET_POINT] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_set_point_res_info
 }
};
