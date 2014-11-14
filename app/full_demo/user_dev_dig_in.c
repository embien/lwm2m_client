/*! \file 
  \brief      Module specific to user defined implmentation of IPSO digital input object
   
   Contains the logic with customized implementation of resource access for the IPSO digital input object.
*/

#include <lwm2m_client.h>
int dev_dig_in_oper_dig_input_state (INT16S, INT8U, void*);
LWM2M_OBJECT_RES_INFO user_dev_dig_in_res_info [LWM2M_USER_DEV_DIG_IN_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_DIG_INPUT_STATE),
    dev_dig_in_oper_dig_input_state
  }
};
INT8U digital_inp = 1;
 
int dev_dig_in_oper_dig_input_state(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    //EBMJ
    if (u16_inst_id == 0)
      *((INT8U*)ptr_value) = 1;
    else
      *((INT8U*)ptr_value) = 1;
  }
  if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    digital_inp = *((INT8U*)ptr_value);
  }
  return 0;
}