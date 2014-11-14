/*! \file 
  \brief      Module specific to user defined implmentation of IPSO barometer object
  
   Contains the logic with customized implementation of resource access for the IPSO barometer object.
*/

#include <lwm2m_client.h>
int dev_baro_meter_oper_sen_value (INT16S, INT8U, void*);
LWM2M_OBJECT_RES_INFO user_dev_baro_meter_res_info [LWM2M_USER_DEV_BARO_METER_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_SENSOR_VALUE),
    dev_baro_meter_oper_sen_value
  }
};




FRACTION u32_baro_meter_sen_value = (FRACTION)33.15; //float point 
//FRACTION u32_fixed_number = 3456122;  //fixed point number


int dev_baro_meter_oper_sen_value (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  int total_len;
  FRACTION  f_value;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	  {
	    q2a(ptr_value, u32_baro_meter_sen_value);
	  }
    #endif
    #if FLOAT_POINT
	  {
      *((FRACTION *)ptr_value) = u32_baro_meter_sen_value; 
	  } 
    #endif
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    #if  FIXED_POINT
    {
      f_value = a2q((FRACTION *)ptr_value);
	  u32_baro_meter_sen_value = f_value;
	  return 0;
	}
	#endif
    #if  FLOAT_POINT
	{ 
	  total_len = strlen(( INT8U*)ptr_value);
      f_value = str_to_float(ptr_value, total_len);
	  u32_baro_meter_sen_value = f_value;
	  return 0;
	}
    #endif     
  }
  return 0;
}

