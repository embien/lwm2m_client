/*! \file 
  \brief      Module specific to user defined implmentation of IPSO set point object
   
   Contains the logic with customized implementation of resource access for the IPSO set point object.
*/

#include <lwm2m_client.h>

FRACTION u32_set_point_val= (FRACTION)10.99; //float point 
INT8U u32_set_point_colour [30]  = "RED";
int  dev_oper_set_point_value (INT16S , INT8U , void *);
int dev_oper_set_point_colour(INT16S, INT8U, void *);



LWM2M_OBJECT_RES_INFO user_dev_set_point_res_info [LWM2M_USER_DEV_SET_POINT_RES_MAX] = 
{ 
  {
    LWM2M_RES_PROP(LW_RES_SET_POINT_VALUE),
    dev_oper_set_point_value
  }
 };
 
int  dev_oper_set_point_value (INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
	int total_len;
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    #if  FIXED_POINT
	  {
	    q2a(ptr_value, u32_set_point_val);
	  }
    #endif
    #if FLOAT_POINT
	  {
      *((FRACTION *)ptr_value) = u32_set_point_val; 
	  } 
    #endif
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {  
    #if  FIXED_POINT
	  {
	    u32_set_point_val = a2q((FRACTION *)ptr_value);
	  }  
    #endif
    #if  FLOAT_POINT
	  { 
	    total_len = strlen(( INT8U*)ptr_value);
        u32_set_point_val = str_to_float((INT8U *)ptr_value, total_len);
	  }
    #endif
  }
  return 0; 
}
 
int dev_oper_set_point_colour(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   strcpy (((INT8U*)ptr_value), u32_set_point_colour);
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    strcpy (u32_set_point_colour, ((INT8U*)ptr_value));
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_EXECUTE)
  {
   printf ("executed sucessfully \n\r");
  }
  return 0;
}


