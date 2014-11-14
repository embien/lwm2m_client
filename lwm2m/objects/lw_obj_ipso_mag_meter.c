/*! \file 
  \brief      Module implementing the LWM2M instance information for IPSO magnometer object
   
   Contains the logic for implementing the instances for IPSO magnometer  object 
*/

#include <lwm2m_client.h>

LWM2M_OBJECT_INST_INFO lw_obj_ipso_mag_meter_inst_list [LW_MAX_INST_IPSO_MAG_METER] = 
{
 { 
   LWM2M_OBJ_INST_VALID,
   0,
   1,
   user_dev_mag_meter_res_info
 },
};
