/*! \file 
  \brief      Module specific to user defined implmentation of IPSO actuation object
   
   Contains the logic with customized implementation of resource access for the IPSO actuation object
*/


#include <lwm2m_client.h>
int dev_act_oper_on_off (INT16S, INT8U, void*);
LWM2M_OBJECT_RES_INFO user_dev_act_res_info [LWM2M_USER_DEV_ACT_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_ON_OFF),
    dev_act_oper_on_off
  }
};
INT8U u8_act = 0;
int dev_act_oper_on_off (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   *((INT8U*)ptr_value) = u8_act;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    if (*(INT8U*)ptr_value <= LW_RES_ON_OFF_MAX_RANGE)
    {
      u8_act = *((INT8U*)ptr_value);
	  return 0;
    }
	else
	{
      return -1;
	}
  }
  return 0;
}
