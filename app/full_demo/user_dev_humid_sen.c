/*! \file 
  \brief      Module specific to user defined implmentation of IPSO humidity sensor object
   
   Contains the logic with customized implementation of resource access for the IPSO humidity sensor object.
*/

#include <lwm2m_client.h>
int  dev_humid_sen_oper_sen_value (INT16S, INT8U, void *);

LWM2M_OBJECT_RES_INFO user_dev_humid_sen_res_info [LWM2M_USER_DEV_HUMID_SEN_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_SENSOR_VALUE), 
    dev_humid_sen_oper_sen_value
  }
};
FRACTION humid_sen =  (FRACTION)33.04;
 

int  dev_humid_sen_oper_sen_value (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  int total_len;
  FRACTION f_value; 
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	{
	  q2a(ptr_value, humid_sen);
	} 
    #endif
    #if FLOAT_POINT
	{
      (*(FRACTION *)ptr_value) = humid_sen; 
	} 
    #endif
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    #if  FIXED_POINT
    {
      f_value = a2q((FRACTION *)ptr_value);
	  humid_sen = f_value;
	  return 0;
	}
	#endif  
    #if  FLOAT_POINT
	{ 
	  total_len = strlen(( INT8U*)ptr_value);
      f_value = str_to_float(ptr_value, total_len);
	  humid_sen = f_value;
	  return 0;
	}
    #endif     
  }
  return 0;
}
