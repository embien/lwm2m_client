/*! \file 
  \brief      Module specific to user defined implmentation of IPSO light control object
   
   contains the logic with customized implementation of resource access for the IPSO light control object.
*/

#include <lwm2m_client.h>
int dev_light_con_oper_on_off (INT16S, INT8U, void*);
LWM2M_OBJECT_RES_INFO user_dev_light_con_res_info [LWM2M_USER_DEV_LIGHT_CON_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_ON_OFF),
    dev_light_con_oper_on_off
  }
};

INT8U u8_light_con = 1;
 
int dev_light_con_oper_on_off (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   *((INT8U*)ptr_value) = u8_light_con;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    if (*(INT8U*)ptr_value <= LW_RES_ON_OFF_MAX_RANGE)
    {
      u8_light_con =*((INT8U*)ptr_value);
	  return 0;
    }
	else
	{
      return -1;
	}
  }
  
  return 0;
}
#if 0
int dev_inc_light_oper_dimmer (INT16U u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT32U*)(ptr_value)) = value;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    value =  *((INT32U*)(ptr_value));
  }
  return 0;
}
#endif
