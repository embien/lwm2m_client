/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO load control object
   
   Contains the logic for implementing the instances for IPSO load control  object 
*/


#include <lwm2m_client.h>
LWM2M_OBJECT_INST_INFO lw_obj_ipso_load_con_inst_list [LW_MAX_INST_IPSO_LOAD_CON] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_load_con_res_info
 }
};



