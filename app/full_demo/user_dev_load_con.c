/*! \file 
  \brief      Module specific to user defined implmentation of IPSO load control object
   
   Contains the logic with customized implementation of resource access for the IPSO load control object.
*/

#include <lwm2m_client.h>
int dev_load_con_oper_event_ident (INT16S, INT8U, void*);
int dev_load_con_oper_duration_in_min(INT16S, INT8U , void *);
LWM2M_OBJECT_RES_INFO user_dev_load_con_res_info [LWM2M_USER_DEV_LOAD_CON_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_EVENT_IDENTIFIER),
    dev_load_con_oper_event_ident
  },
  {
     LWM2M_RES_PROP(LW_RES_DURATION_IN_MIN),
	 dev_load_con_oper_duration_in_min
	}      
};

INT8U u8_load_con [LWM2M_IPSO_LOAD_CON_EV_IDENT_MAX_RANGE] = "3310";
int load_dur = 255; 
 
int dev_load_con_oper_event_ident(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   strcpy (((char*)ptr_value), (const char *)u8_load_con);
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    strcpy ((char *)u8_load_con, (const char *)((INT8U*)ptr_value));
  }
  return 0;
}
int dev_load_con_oper_duration_in_min(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   *(INT32U *)ptr_value =  load_dur;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    load_dur = *(INT32U*)ptr_value;
  }
  return 0;
}
