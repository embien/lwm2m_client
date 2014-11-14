/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO analog output object
  
   Contains the logic for implementing the instances for IPSO analog output object 
*/

#include <lwm2m_client.h>


LWM2M_OBJECT_INST_INFO lw_obj_ipso_anlog_out_inst_list [LW_MAX_INST_IPSO_ANLOG_OUT] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   2,
   user_dev_anlog_out_res_info
 }
};
