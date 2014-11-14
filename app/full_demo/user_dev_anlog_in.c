/*! \file 
  \brief      Module specific to user defined implmentation of IPSO analog input object
   
   Contains the logic with customized implementation of resource access for the IPSO analog input object.
*/


#include <lwm2m_client.h>
int  dev_anlog_in_oper_anlog_in_curr_value (INT16S, INT8U, void *);
LWM2M_OBJECT_RES_INFO user_dev_anlog_in_res_info [LWM2M_USER_DEV_ANLOG_IN_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_ANLOG_INPUT_CURRENT_VALUE),
    dev_anlog_in_oper_anlog_in_curr_value
  }
};
FRACTION f_anlog_curr = (FRACTION)2.02;
int  dev_anlog_in_oper_anlog_in_curr_value (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  FRACTION range;
  int total_len;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	{
	  q2a(ptr_value, f_anlog_curr);
	} 
    #endif
    #if FLOAT_POINT
	{
      (*(FRACTION *)ptr_value) = f_anlog_curr; 
	} 
    #endif
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    #if  FIXED_POINT
	{
      range = a2q((FRACTION *)ptr_value);
	  if (range <= LW_RES_ANLOG_INPUT_CURRENT_VALUE_MAX_RANGE)
	  {
        f_anlog_curr = range;
	    return 0; 
	  }
	  else
      {
        return -1;
      }
	}   
    #endif
    #if  FLOAT_POINT
	{ 
	  total_len = strlen(( INT8U*)ptr_value);
      range = str_to_float(ptr_value, total_len);
	  if (range <= LW_RES_ANLOG_INPUT_CURRENT_VALUE_MAX_RANGE)
	  {
        f_anlog_curr = range;
	    return 0; 
	  }
	  else
      {
        return -1;
      }
	}
    #endif
  }
  return 0;
}
