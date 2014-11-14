/*! \file 
  \brief      Module implementing the LWM2M instance information for LWM2M  location object
   
   Contains the logic for implementing the instances for LWM2M  location object 
*/


#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_oma_loc_inst_list [LW_MAX_INST_OMA_LOCATION] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_loc_res_info
 }
};
