/*! \file 
  \brief      Module specific to user defined implmentation of IPSO power control  object
   
   Contains the logic with customized implementation of resource access for the IPSO power control  object.
*/

#include <lwm2m_client.h>
int dev_power_con_oper_on_off(INT16S, INT8U, void *);
int dev_power_con_oper_dimmer (INT16U, INT8U, void *);
int dev_power_con_oper_cummulative_active_power (INT16S, INT8U, void *);

INT8U power_on_val = 0;
int dim_value =567;
FRACTION active_power = (FRACTION)12.34; 

LWM2M_OBJECT_RES_INFO user_dev_power_con_res_info [LWM2M_USER_DEV_POWER_CON_RES_MAX] = 
{ 
  {
    LWM2M_RES_PROP(LW_RES_ON_OFF),
    dev_power_con_oper_on_off
  },
   {
    LWM2M_RES_PROP(LW_RES_DIMMER),
    dev_power_con_oper_dimmer
  },
   {
    LWM2M_RES_PROP(LW_RES_CUMULATIVE_ACTIVE_POWER),
    dev_power_con_oper_cummulative_active_power
  }
};
 
int dev_power_con_oper_on_off(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT8U*)ptr_value) =  power_on_val;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    power_on_val  =*((INT8U*)ptr_value);
    return 0;
  }
  else
  {
    return -1;
  }
  return 0;
}
int dev_power_con_oper_dimmer (INT16U u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT32U*)(ptr_value)) = dim_value;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    dim_value =  *((INT32U*)(ptr_value));
  }
  return 0;
}
int dev_power_con_oper_cummulative_active_power (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  FRACTION f_value;
  int total_len;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	  {
	    q2a(ptr_value, active_power);
	  }
    #endif
    #if FLOAT_POINT
	  {
      *((FRACTION *)ptr_value) = active_power; 
	  } 
    #endif
  } 
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
     #if  FIXED_POINT
	 {
       f_value = a2q((FRACTION *)ptr_value);
	   active_power = f_value;
	   return 0;
	   }
	 }
     #endif
     #if  FLOAT_POINT
	 { 
	   total_len = strlen(( INT8U*)ptr_value);
       f_value = str_to_float(ptr_value, total_len);
	   active_power = f_value;
	   return 0;
	 }
     #endif     
   }
  return 0;
}

