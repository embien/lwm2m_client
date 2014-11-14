/*! \file 
  \brief      Module specific to user defined implmentation of IPSO presence sensor object
   
   Contains the logic with customized implementation of resource access for the IPSO presence sensor object.
*/

#include <lwm2m_client.h>
int  dev_pres_sen_oper_dig_input_state (INT16S, INT8U, void *);

LWM2M_OBJECT_RES_INFO user_dev_pres_sen_res_info [LWM2M_USER_DEV_PRES_SEN_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_DIG_INPUT_STATE), 
    dev_pres_sen_oper_dig_input_state
  }
};
INT8U pres_sen = 0;
 

int dev_pres_sen_oper_dig_input_state(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT8U*)ptr_value) = pres_sen;
  }
  if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    pres_sen = *((INT8U*)ptr_value);
  }
  return 0;
}