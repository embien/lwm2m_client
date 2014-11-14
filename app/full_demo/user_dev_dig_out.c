/*! \file 
  \brief      Module specific to user defined implmentation of IPSO digital output object
   
   Contains the logic with customized implementation of resource access for the IPSO digital output object.
*/

#include <lwm2m_client.h>
int dev_dig_out_oper_dig_output_state(INT16S , INT8U , void *);
LWM2M_OBJECT_RES_INFO user_dev_dig_out_res_info [LWM2M_USER_DEV_DIG_OUT_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_DIG_OUTPUT_STATE),
    dev_dig_out_oper_dig_output_state
  }
};
INT8U u8_digital_output =  0;
 
int dev_dig_out_oper_dig_output_state(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT8U*)ptr_value) = u8_digital_output;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    u8_digital_output =*((INT8U*)ptr_value);
  }
  return 0;
}