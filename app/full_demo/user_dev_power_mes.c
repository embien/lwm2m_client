/*! \file 
  \brief      Module specific to user defined implmentation of IPSO power measurement object
   
   Contains the logic with customized implementation of resource access for the IPSO power measurement object.
*/

#include <lwm2m_client.h>
int  dev_power_mes_oper_inst_act_power(INT16S, INT8U, void *);

LWM2M_OBJECT_RES_INFO user_dev_power_mes_res_info [LWM2M_USER_DEV_POWER_MES_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_INSTANTANEOUS_ACTIVE_POWER), 
    dev_power_mes_oper_inst_act_power
  }
};
FRACTION power_mes = (FRACTION)33.05;
 

int  dev_power_mes_oper_inst_act_power (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  FRACTION f_value;
  int total_len;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	{
	  q2a(ptr_value, power_mes);
	} 
    #endif
    #if FLOAT_POINT
	{
      (*(FRACTION *)ptr_value) = power_mes; 
	} 
    #endif
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    #if  FIXED_POINT
    {
      f_value = a2q((FRACTION *)ptr_value);
	  power_mes  = f_value;
	  return 0;
	}
	#endif  
    #if  FLOAT_POINT
	{ 
	  total_len = strlen(( INT8U*)ptr_value);
      f_value = str_to_float(ptr_value, total_len);
	  power_mes  = f_value;
	  return 0;
	}
    #endif     
  }
  return 0;
}

