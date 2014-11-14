/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO light control object
   
   Contains the logic for implementing the instances for IPSO light control object 
*/

#include <lwm2m_client.h>
LWM2M_OBJECT_INST_INFO lw_obj_ipso_light_con_inst_list [LW_MAX_INST_IPSO_LIGHT_CON] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   3,
   user_dev_light_con_res_info
 }
};
