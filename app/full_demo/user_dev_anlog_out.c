/*! \file 
  \brief      Module specific to user defined implmentation of IPSO analog output object
   
   Contains the logic with customized implementation of resource access for the IPSO analog output object.
*/

#include <lwm2m_client.h>
int  dev_anlog_out_oper_anlog_out_curr_value (INT16S, INT8U, void *);
int  dev_anlog_out_oper_anlog_out_application_type (INT16S, INT8U, void *);
LWM2M_OBJECT_RES_INFO user_dev_anlog_out_res_info [LWM2M_USER_DEV_ANLOG_OUT_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_ANLOG_OUTPUT_CURRENT_VALUE),
    dev_anlog_out_oper_anlog_out_curr_value
  },
  {
    LWM2M_RES_PROP(LW_RES_APPLICATION_TYPE), 
    dev_anlog_out_oper_anlog_out_application_type
  }
};
INT8U u8_app_type [LWM2M_USER_DEV_STRING_MAX_RANGE] = "APP type";
FRACTION f_anlog_out = (FRACTION)3.3;
int  dev_anlog_out_oper_anlog_out_curr_value (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  int total_len;
  FRACTION range;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	{
	  q2a(ptr_value, f_anlog_out);
	} 
    #endif
    #if FLOAT_POINT
	{
      *(FRACTION *)ptr_value = f_anlog_out; 
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
		f_anlog_out = range;
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
		f_anlog_out = range;
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
    
int  dev_anlog_out_oper_anlog_out_application_type (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    strcpy (((char*)ptr_value), (const char *)u8_app_type);
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    strcpy ((char *)u8_app_type, (const char *)((INT8U*)ptr_value));
  }
  return 0;
}
