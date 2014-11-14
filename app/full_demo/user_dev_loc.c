/*! \file 
  \brief      Module specific to user defined implmentation of LWM2M location object
   
   Contains the logic with customized implementation of resource access for the LWM2M location object.
*/

#include <lwm2m_client.h>
int dev_loc_oper_latitude (INT16S, INT8U, void*);

LWM2M_OBJECT_RES_INFO user_dev_loc_res_info [LWM2M_USER_DEV_LOC_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_LATITUDE),
    dev_loc_oper_latitude
  }
};
INT8U u8_location [LWM2M_OMA_LOC_LATITUDE_MAX_RANGE] = "1.234";


int dev_loc_oper_latitude(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
   strcpy (((char*)ptr_value), (const char *)u8_location);
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    strcpy ((char *)u8_location, (const char *)((INT8U*)ptr_value));
  }
  return 0;
}
