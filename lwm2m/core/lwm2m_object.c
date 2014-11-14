/*! \file 
  \brief      CodeReviewed Module implementing the LWM2M objects and processing the requests for lwm2m objects ,instances and resources  
 
  Contains the logic for impelmentation, validation, processing the LWM2M objects ,instances and resources 
*/

#include <lwm2m_client.h>
int lwm2m_prep_int8u_inst (INT16S, int , LWM2M_PROCESS_INFO *);
int lwm2m_prep_int_inst (INT16S, int, LWM2M_PROCESS_INFO *);
int lwm2m_prep_string_inst (INT16S, int, LWM2M_PROCESS_INFO *);
int lwm2m_prep_fraction_inst (INT16S, int, LWM2M_PROCESS_INFO *);

#if LWM2M_CLIENT_SUPPORT_OBSERVE
/*! Array to hold list of observed objects/instances/resources */
LWM2M_OBSERVE_INFO lwm2m_observed_items [LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS];
#endif

typedef int (*FN_PTR_PROCESS_RES_READ)( INT16S, int, LWM2M_PROCESS_INFO*);
FN_PTR_PROCESS_RES_READ fn_ptr_process_res_read [4] = 
{
  lwm2m_prep_int8u_inst,
  lwm2m_prep_int_inst,
  lwm2m_prep_string_inst,
  lwm2m_prep_fraction_inst,
};

/*! List of supported objects*/
LWM2M_OBJECT_INFO supported_object_list [LWM2M_MAX_SUPPORTED_OBJECTS] = 
{
#if LWM2M_OBJ_SUPPORT_IPSO_ACCE_METER	                  
  {
    LWM2M_OBJ_ID_IPSO_ACCE_METER,
    LW_MAX_INST_IPSO_ACCE_METER,
    lw_obj_ipso_acce_meter_inst_list 
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_ACT
  {
    LWM2M_OBJ_ID_IPSO_ACT,
    LW_MAX_INST_IPSO_ACT,
    lw_obj_ipso_act_inst_list
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_ANLOG_IN
{
  LWM2M_OBJ_ID_IPSO_ANLOG_IN,
  LW_MAX_INST_IPSO_ANLOG_IN,
  lw_obj_ipso_anlog_in_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_ANLOG_OUT
{
  LWM2M_OBJ_ID_IPSO_ANLOG_OUT,
  LW_MAX_INST_IPSO_ANLOG_OUT,
  lw_obj_ipso_anlog_out_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_BARO_METER
{
  LWM2M_OBJ_ID_IPSO_BARO_METER,
  LW_MAX_INST_IPSO_BARO_METER,
  lw_obj_ipso_baro_meter_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_DIG_IN
{
  LWM2M_OBJ_ID_IPSO_DIG_IN,
  LW_MAX_INST_IPSO_DIG_IN,
  lw_obj_ipso_dig_in_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_DIG_OUT
{
  LWM2M_OBJ_ID_IPSO_DIG_OUT,
  LW_MAX_INST_IPSO_DIG_OUT,
  lw_obj_ipso_dig_out_inst_list
},
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_GEN_SEN
{
  LWM2M_OBJ_ID_IPSO_GEN_SEN,
  LW_MAX_INST_IPSO_GEN_SEN,
  lw_obj_ipso_gen_sen_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_HUMID_SEN
{
  LWM2M_OBJ_ID_IPSO_HUMID_SEN,
  LW_MAX_INST_IPSO_HUMID_SEN,
  lw_obj_ipso_humid_sen_inst_list
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_LIGHT_CON 
  {
    LWM2M_OBJ_ID_IPSO_LIGHT_CON,
    LW_MAX_INST_IPSO_LIGHT_CON,
    lw_obj_ipso_light_con_inst_list
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_LOAD_CON 
  {
    LWM2M_OBJ_ID_IPSO_LOAD_CON,
    LW_MAX_INST_IPSO_LOAD_CON,
    lw_obj_ipso_load_con_inst_list   
	
  },
#endif
  #if LWM2M_OBJ_SUPPORT_OMA_LOCATION 
  {
    LWM2M_OBJ_ID_OMA_LOCATION,
    LW_MAX_INST_OMA_LOCATION,
    lw_obj_oma_loc_inst_list
  },
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_LUMIN_SEN
  {
    LWM2M_OBJ_ID_IPSO_LUMIN_SEN,
    LW_MAX_INST_IPSO_LUMIN_SEN,
    lw_obj_ipso_lumin_sen_inst_list   
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_MAG_METER 
  {
    LWM2M_OBJ_ID_IPSO_MAG_METER,
    LW_MAX_INST_IPSO_MAG_METER,
    lw_obj_ipso_mag_meter_inst_list
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_POWER_CON 
{
   LWM2M_OBJ_ID_IPSO_POWER_CON,
   LW_MAX_INST_IPSO_POWER_CON,
   lw_obj_ipso_power_con_inst_list    
},
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_POWER_MES 
{
   LWM2M_OBJ_ID_IPSO_POWER_MES,
   LW_MAX_INST_IPSO_POWER_MES,
   lw_obj_ipso_power_mes_inst_list    
},
#endif

#if LWM2M_OBJ_SUPPORT_IPSO_PRES_SEN 
{
   LWM2M_OBJ_ID_IPSO_PRES_SEN,
   LW_MAX_INST_IPSO_PRES_SEN,
   lw_obj_ipso_pres_sen_inst_list    
},
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_SET_POINT 
  {
   LWM2M_OBJ_ID_IPSO_SET_POINT,
   LW_MAX_INST_IPSO_SET_POINT,
   lw_obj_ipso_set_point_inst_list    
  },
#endif
#if LWM2M_OBJ_SUPPORT_IPSO_TEMP_SEN
{
  LWM2M_OBJ_ID_IPSO_TEMP_SEN,
  LW_MAX_INST_IPSO_TEMP_SEN,
  lw_obj_ipso_temp_sen_inst_list
}
#endif
};

/*! \fn       int lwm2m_obj_validate_obj_id (INT16U u16_req_obj_id)
    \brief     Validates the requested LWM2M object id  
    \param[in] u16_req_obj_id Requested LWM2M object id   
    \return     int   Index of the supported object on success or negative value on failure
*/
int lwm2m_obj_validate_obj_id (INT16U u16_req_obj_id)
{
  int index;
  for (index = 0; index < LWM2M_MAX_SUPPORTED_OBJECTS; index ++)
  {
    if (supported_object_list [index].u16_obj_id == u16_req_obj_id)
     return index;
  }
  return -1;
}

/*! \fn       int lwm2m_obj_validate_inst_id (INT16U u16_req_inst_id, int obj_index)
    \brief     Validates the requested LWM2M instance id  
    \param[in] u16_req_obj_id Requested LWM2M instance id   
    \param[in] obj_index      Index of object in supported object list
    \return     int           Index of the instance on success or negative value on failure
*/
int lwm2m_obj_validate_inst_id (INT16U u16_req_inst_id, int obj_index)
{
  LWM2M_OBJECT_INST_INFO *ptr_inst_list;
  INT8U u8_max_num_inst;
  int index;
  ptr_inst_list = supported_object_list [obj_index].ptr_inst_list;
  u8_max_num_inst = supported_object_list [obj_index].u8_max_num_inst;
  for (index = 0; index < u8_max_num_inst; index ++)
  { 
    if ((ptr_inst_list + index)->u8_inst_state & LWM2M_OBJ_INST_STATE_VALID)
    {
	  if ((ptr_inst_list +index)->u16_inst_id == u16_req_inst_id)
        return index;
	}
  }
  return -1;
}

/*! \fn     int lwm2m_obj_validate_res_id (INT16U u16_req_res_id, int inst_index, int obj_index)
    \brief     Validates  the requested LWM2M resource id  
    \param[in] u16_req_res_id  requested LWM2M resource id         
    \param[in] obj_index       Index of objects in supported object list
    \param[in] inst_index      Index of the instance in instances list
    \return     int            Index of the resources on success or negative value on failure
*/
int lwm2m_obj_validate_res_id (INT16U u16_req_res_id, int inst_index, int obj_index)
{
  int index;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info;
  INT8U u8_max_num_res;
  ptr_instance_info = supported_object_list [obj_index].ptr_inst_list;//lw_obj_ipso_light_con_inst_list
  u8_max_num_res = ptr_instance_info [inst_index].u8_max_res;//LW_MAX_INST_IPSO_LIGHT_CON
  ptr_obj_res_info = ptr_instance_info [inst_index].ptr_res_list;
  ptr_res_info = ptr_obj_res_info->ptr_resource_info;
  for (index = 0 ;index < u8_max_num_res; index ++)
  {
    if (ptr_obj_res_info [index].ptr_resource_info->u16_res_id == u16_req_res_id) 
    {
      return index;
    }
  }
  return -1;
}

/*! \fn   int lwm2m_prep_int8u_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief     Fetches the 8-bit unsigned value of given resource
    \param[in] u16_req_inst_id  Requested instance id
    \param[in] res_index        Index of the resources in the instance
    \param[out] ptr_proc_req    Information of the request being processed containing the buffer to return the read value
    \return     int        Zero on success or error code on failure
*/
int lwm2m_prep_int8u_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
{
  int write_index;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_proc_req->u16_inst_id_index].ptr_res_list;
  ptr_res_info = (ptr_obj_res_info + res_index)->ptr_resource_info;
  write_index = ptr_proc_req->u8_value_len;
  ptr_proc_req->value [write_index ++] = LWM2M_OBJ_RES_FORMAT_INT8U;
  ptr_proc_req->value [write_index ++] = (ptr_res_info + res_index)->u16_res_id >> 8 ; // msb 
  ptr_proc_req->value [write_index ++] = (INT8U)(ptr_res_info + res_index)->u16_res_id;  // lsb
  (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	  &ptr_proc_req->res_val.u8_value);
  ptr_proc_req->value [write_index ++] = ptr_proc_req->res_val.u8_value;
  ptr_proc_req->u8_value_len = (INT8U)(write_index);
  return 0;
}

/*! \fn   int lwm2m_prep_int_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief      Fetches the 32-bit unsigned value of given resource
    \param[in] u16_req_inst_id Requested instance id
    \param[in] res_index    Index of the resources in the instance
    \param[out] ptr_proc_req  Information of the request being processed containing the buffer to return the read value
    \return     int        zero on success or error code on failure
*/
int lwm2m_prep_int_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
{
  int write_index;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_proc_req->u16_inst_id_index].ptr_res_list;
  ptr_res_info = (ptr_obj_res_info + res_index)->ptr_resource_info;
  write_index = ptr_proc_req->u8_value_len;
  ptr_proc_req->value [write_index ++] =  LWM2M_OBJ_RES_FORMAT_INT;	
  ptr_proc_req->value [write_index ++] = ptr_res_info->u16_res_id >> 8 ; 
  ptr_proc_req->value [write_index ++] = (INT8U)ptr_res_info->u16_res_id; 
 (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	 &ptr_proc_req->res_val.u32_value);
  ptr_proc_req->value [write_index ++] = (INT8U)(ptr_proc_req->res_val.u32_value >> 24);
  ptr_proc_req->value [write_index ++] = (INT8U)(ptr_proc_req->res_val.u32_value >> 16);
  ptr_proc_req->value [write_index ++] = (INT8U)(ptr_proc_req->res_val.u32_value >> 8);
  ptr_proc_req->value [write_index ++] = (ptr_proc_req->res_val.u32_value & 0xff);
  ptr_proc_req->u8_value_len = (INT8U)write_index;
  return 0;
}

/*! \fn   int lwm2m_prep_string_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief     Fetches the string value of given resource
    \param[in] u16_req_inst_id Requested instance id
    \param[in] res_index  Index of the resources in the instance
    \param[out] ptr_proc_req Information of the request being processed containing the buffer to return the read value
    \return     int        zero on success of error code on failure
*/
int lwm2m_prep_string_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
{
	
  int write_index;
  INT8U value_len;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_proc_req->u16_inst_id_index].ptr_res_list;
  ptr_res_info = (ptr_obj_res_info + res_index)->ptr_resource_info;
  write_index = ptr_proc_req->u8_value_len; 
  (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	 (ptr_proc_req->res_val.str));
  value_len = (INT8U) strlen ((const char *)(ptr_proc_req->res_val.str));
  if (value_len < 8)
  {
    ptr_proc_req->value [write_index ++] =  LWM2M_OBJ_HEADER_TYPE_FIELD | value_len;
	  ptr_proc_req->value [write_index ++] = ((ptr_res_info + res_index)->u16_res_id) >> 8;
    ptr_proc_req->value [write_index ++] = (INT8U)(ptr_res_info + res_index)->u16_res_id;
  }
  else if (value_len < 64)
  {
    ptr_proc_req->value [write_index ++] = LWM2M_OBJ_HEADER_TYPE_FIELD;	
    ptr_proc_req->value [write_index ++] = (ptr_res_info ->u16_res_id) >> 8;
    ptr_proc_req->value [write_index ++] = (INT8U)(ptr_res_info->u16_res_id);
	  ptr_proc_req->value [write_index ++] = value_len;
  } 
  strcpy ((char *)(ptr_proc_req->value + write_index), (const char *)(ptr_proc_req->res_val.str));
  ptr_proc_req->u8_value_len = (INT8U)(write_index + value_len);
  return 0;
}

/*! \fn   int lwm2m_prep_fraction_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief      Fetches the float value of given resource 
    \param[in] u16_req_inst_id Requested instance id
    \param[in] res_index   Index of the resources in instance 
    \param[out] ptr_proc_req Information of the request being processed containing the buffer to return the read value
    \return     int        zero on success or error code on failure
*/
int lwm2m_prep_fraction_inst (INT16S u16_req_inst_id, int res_index, LWM2M_PROCESS_INFO *ptr_proc_req)
{
  FRACTION float_value;
  INT32U u32_value;
  int write_index;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_proc_req->u16_inst_id_index].ptr_res_list;
  ptr_res_info = (ptr_obj_res_info + res_index)->ptr_resource_info;
  write_index = ptr_proc_req->u8_value_len;
  ptr_proc_req->value [write_index ++] =  LWM2M_OBJ_RES_FORMAT_FRAC;	
  ptr_proc_req->value [write_index ++] = ptr_res_info->u16_res_id >> 8 ; 
  ptr_proc_req->value [write_index ++] = (INT8U)ptr_res_info->u16_res_id; 
 (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
 &float_value);
  u32_value = *(INT32U*)(&float_value);
  printf ("float =%f, u32_value = %x \r\n",float_value,u32_value);
  ptr_proc_req->value [write_index ++] = (INT8U)(u32_value >> 24);
  ptr_proc_req->value [write_index ++] = (INT8U)(u32_value  >> 16);
  ptr_proc_req->value [write_index ++] = (INT8U)(u32_value  >> 8);
  ptr_proc_req->value [write_index ++] =(INT8U)u32_value;
  ptr_proc_req->u8_value_len = (INT8U)write_index;
  return 0;
}



/*! \fn   int lwm2m_prepare_inst_read_resp (INT16S u16_req_inst_id, LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief     Fetches one or more resource values in the requested instance
    \param[in] u16_req_inst_id Requested instance id
    \param[out] ptr_proc_req   Information of the processed request continaing the buffer to return the data
    \return     int        Zero on success or error code on failure
*/
int lwm2m_prepare_inst_read_resp (INT16S u16_req_inst_id, LWM2M_PROCESS_INFO *ptr_proc_req)
{
  int write_index, max_res;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  int res_index;
  write_index = ptr_proc_req->u8_value_len;
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  max_res = ptr_instance_info [u16_req_inst_id].u8_max_res;
  ptr_obj_res_info = ptr_instance_info [u16_req_inst_id].ptr_res_list;
  for (res_index = 0; res_index < max_res; res_index ++)
  {
    ptr_res_info = (ptr_obj_res_info + res_index)->ptr_resource_info;
	  fn_ptr_process_res_read [ptr_res_info->u8_type] (u16_req_inst_id, res_index, ptr_proc_req);
  } 
  ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_SUCCESS;
  ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_CONTENT;
  write_index = (ptr_proc_req->u8_value_len);
  return write_index;
}

/*! \fn  int lwm2m_process_request_obj (LWM2M_PROCESS_INFO *ptr_proc_req)
    \brief  Process the read/write/execute requests for the given objects/instances/resources
    \param[out] ptr_proc_req Information of the processing requests in LWM2M objects
    \return     int        Zero on success
*/
int lwm2m_process_request_obj (LWM2M_PROCESS_INFO *ptr_proc_req)
{
  int ret_index, res_index, inst_max, inst_index, res_format, write_index = 0, ret_value = 0;
  INT8U u8_value,*ptr_end;
   FRACTION float_value;
  INT32U u32_value;
  INT8U str_val [LWM2M_MAX_VALUE_LEN];
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  ptr_proc_req->u8_value_len = 0; 
  if (ptr_proc_req->u8_num_path_elements >= 1)
  {
    ret_index = lwm2m_obj_validate_obj_id  (ptr_proc_req->object_path [LWM2M_PATH_INDEX_OBJECT]);
    if (ret_index < 0)
	  {
      goto bad_request;     
    }
    ptr_proc_req->u16_obj_id_index = (INT16S)ret_index;
  }
  if (ptr_proc_req->u8_num_path_elements >= 2)
  {
    ret_index = lwm2m_obj_validate_inst_id (ptr_proc_req->object_path [LWM2M_PATH_INDEX_INST],ptr_proc_req->u16_obj_id_index);
    if (ret_index < 0)
    {
      goto bad_request;
    }
    ptr_proc_req->u16_inst_id_index = (INT16S)ret_index;
  }
  if (ptr_proc_req->u8_num_path_elements >= 3)
  {
    ret_index = lwm2m_obj_validate_res_id (ptr_proc_req->object_path [LWM2M_PATH_INDEX_RES],\
    ptr_proc_req->u16_inst_id_index, ptr_proc_req->u16_obj_id_index);
    if ( ret_index < 0)
    { 
      goto bad_request;
    }
    ptr_proc_req->u16_res_id_index = (INT16S)ret_index;
  }
  ptr_instance_info = supported_object_list [ptr_proc_req->u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_proc_req->u16_inst_id_index].ptr_res_list;
  ptr_res_info = ptr_obj_res_info [ptr_proc_req->u16_res_id_index].ptr_resource_info; 
  res_index = ptr_proc_req->u16_res_id_index;
  if (ptr_proc_req->u8_request == LWM2M_PROCESS_REQ_READ)
  {
    if (ptr_proc_req->u8_num_path_elements >= 3)
    {
      if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_BOOL)
	    {
	      (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	       &u8_value);
		    sprintf ((char *)(ptr_proc_req->value), (const char *)"%d", u8_value);  
	    }    
	    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_INT)
	    {
	      (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	       &u32_value);
        sprintf ((char *)(ptr_proc_req->value),(const char *)"%d", u32_value);
	    }
	    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_STR)
	    {
	      (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	      str_val);
        strcpy ((char *)(ptr_proc_req->value),(const char *)str_val);
	    }
	    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_FRAC)
	    {
        #if FIXED_POINT
	      (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	       &fract_value);
        sprintf (ptr_proc_req->value, "%s", fract_value);
		    #endif
        #if FLOAT_POINT 
		    (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_READ,\
	       &float_value);
        sprintf ((char *)(ptr_proc_req->value),(const char *)"%f", float_value);          
		    #endif
	    }
	    ptr_proc_req->u8_value_len = (INT8U)strlen ((const char *)ptr_proc_req->value);
      ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_SUCCESS;
      ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_CONTENT; 
	  }    
    else if (ptr_proc_req->u8_num_path_elements >= 2)
    {
      lwm2m_prepare_inst_read_resp (ptr_proc_req->u16_inst_id_index, ptr_proc_req);
	  }  
	  else  if (ptr_proc_req->u8_num_path_elements >= 1)
	  { 
      inst_max = supported_object_list [ptr_proc_req->u16_obj_id_index].u8_max_num_inst;
	    for (inst_index = 0; inst_index < inst_max ; inst_index ++)
      { 
	      if (!((ptr_instance_info + inst_index)->u8_inst_state & LWM2M_OBJ_INST_STATE_VALID))
   	    {
          continue;     
        }
    	  res_format = 0x08;	
		    ptr_proc_req->value [write_index ++] = (INT8U)res_format;
		    ptr_proc_req->value [write_index ++] = (INT8U)(ptr_instance_info + inst_index)->u16_inst_id;
		    ptr_proc_req->u8_value_len = (INT8U)(write_index + 1);
	      lwm2m_prepare_inst_read_resp ((INT16S)inst_index, ptr_proc_req);
	      ptr_proc_req->value [write_index] =  (INT8U)(ptr_proc_req->u8_value_len - write_index - 1);
	      write_index = ptr_proc_req->u8_value_len;
      }
    }
  }
  if (ptr_proc_req->u8_request == LWM2M_PROCESS_REQ_WRITE)
  { 
    if (ptr_proc_req->u8_num_path_elements >= 3)
    {
      if (ptr_res_info->u8_prop & LWM2M_OBJ_RES_PROP_WRITE)
	    {
	      if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_BOOL)
	      {
          u8_value = (INT8U)strtol ((const char *)ptr_proc_req->value, (char **)&ptr_end, (int)10);
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE, &u8_value); 
	      }
	      if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_INT)
	      {
	        u32_value = (INT8U)strtol ((const char *)ptr_proc_req->value, (char **)&ptr_end, (int)10);
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE, &u32_value);  
	      }
		    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_STR)
	      {
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
				  ptr_proc_req->value);  
	      }
		    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_FRAC)
	      {
			    #if FIXED_POINT
          (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
	          &ptr_proc_req->value);
          #endif
          #if FLOAT_POINT
			    ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
	        ptr_proc_req->value);
          #endif
	      }
	      if(ret_value == 0)
	      {
          ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_SUCCESS;
          ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_CHANGED;
	      }
	      else
	      {
	        ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
          ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_ERR_BAD_REQ;
	      }
	    }
	    else
	    {
	      ptr_proc_req->u8_request = LWM2M_PROCESS_RESP_ERROR; 
		    ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
        ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_ERR_NOT_ALLLOWED;	
	    }  
    }
  }
  if (ptr_proc_req->u8_request == LWM2M_PROCESS_REQ_EXECUTE)
  { 
    if (ptr_proc_req->u8_num_path_elements >= 3)
    {
      if (ptr_res_info->u8_prop & LWM2M_OBJ_RES_PROP_EXECUTE)
	    {
	      if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_BOOL)
	      {
          u8_value = (INT8U)strtol ((const char *)(ptr_proc_req->value),(char **) &ptr_end, (int)10);
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_EXECUTE, &u8_value); 
	      }
	      if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_INT)
	      {
	        u32_value = (INT8U)strtol ((const char *)ptr_proc_req->value, (char **)&ptr_end, (int)10);
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_EXECUTE, &u32_value);  
	      }
		    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_STR)
	      {
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_EXECUTE,\
				  ptr_proc_req->value);  
	      }
		    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_OPAQUE)
	      {
          ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_EXECUTE,\
			  	ptr_proc_req->value);  
	      }
		    if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_FRAC)
	      {
			    #if FIXED_POINT
          (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
	          &ptr_proc_req->value);
          #endif
          #if FLOAT_POINT
			    ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_proc_req->u16_inst_id_index, LWM2M_RESOURCE_OPERATION_EXECUTE,\
	        ptr_proc_req->value);
          #endif
	      }
	      if(ret_value == 0)
	      {
          ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_SUCCESS;
          ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_CHANGED;
	      }
	      else
	      {
	        ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
          ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_ERR_BAD_REQ;
	      }
	    }
	    else
	    {
	      ptr_proc_req->u8_request = LWM2M_PROCESS_RESP_ERROR; 
		    ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
        ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_ERR_NOT_ALLLOWED;	
	    }  
    }
  }
  return 0;
  bad_request:
  ptr_proc_req->u8_request = LWM2M_PROCESS_RESP_ERROR; 
  ptr_proc_req->u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
  ptr_proc_req->u8_resp_detail = LWM2M_PROCESS_RESP_ERR_NOT_FOUND; 
  return 0;
}

/*! \fn  int lwm2m_get_obj_inst_list_for_reg (INT8U *ptr_data, int max_len)
    \brief  Prepares the objects and instances list for registration from LWM2M supported object list and instance list
    \param[out] ptr_data  Buffer to fill the objects and instance list
    \param[in] max_len   Maximum length to fill the objects and instance in the given data buffer
    \return     int      Data length on success or negative value on failure
*/
int lwm2m_get_obj_inst_list_for_reg (INT8U *ptr_data, int max_len)
{
  LWM2M_OBJECT_INST_INFO* lwm2m_inst_info;  
  int obj_id, inst_not_present, data_len, append_len;
  INT16U u16_inst_id;
  data_len = 0;
  for (obj_id = 0; obj_id < LWM2M_MAX_SUPPORTED_OBJECTS; obj_id ++)
  {
    inst_not_present = 1;
    lwm2m_inst_info = supported_object_list [obj_id].ptr_inst_list;
    for (u16_inst_id = 0; u16_inst_id < supported_object_list [obj_id].u8_max_num_inst; u16_inst_id ++)
    {
      if ( lwm2m_inst_info [u16_inst_id].u8_inst_state & LWM2M_OBJ_INST_STATE_VALID)
      {
        append_len = sprintf ((char *)(ptr_data + data_len), (const char *)("</%d/%d>,"), \
        supported_object_list[obj_id].u16_obj_id, u16_inst_id); 
        data_len += append_len;
        if ((data_len - 30) > max_len)
        {
          return -1;
        }
        inst_not_present = 0;
      }
    }
    if (inst_not_present)
    {
      append_len = sprintf ((char *)(ptr_data + data_len), (const char *)("</%d>,"), (int) supported_object_list[obj_id].u16_obj_id); 
      data_len += append_len;
      if ((data_len - 30) > max_len)
      {
        return -1;
      }
    }
  }
  ptr_data [data_len - 1] = '\0';
  return data_len;
}
#if LWM2M_CLIENT_SUPPORT_OBSERVE_FEATURE
/*! \fn  int lwm2m_resource_changed (INT16U u16_obj_id, INT16U u16_inst_id , INT16U u16_res_id)
    \brief   To enable notification for requested objects/instance/resource if specified in supported observed item  
    \param[in] u16_obj_id  Object id of the resource that changed
    \param[in] u16_inst_id Instance id of the resource that changed
    \param[in] u16_res_id  Resource id of the resource that changed
    \return     int      Zero on success 
*/
int lwm2m_resource_changed (INT16U u16_obj_id, INT16S u16_inst_id , INT16U u16_res_id)
{
  int index;
  for (index = 0; index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; index ++) 
  {
    if (lwm2m_observed_items [index].u8_observe_state & LWM2M_OBSERVE_OBJECT_ENABLE)
	  {
	    if (lwm2m_observed_items [index].obj_id == u16_obj_id)
	    {
	      lwm2m_observed_items [index].u8_observe_state |= LWM2M_OBSERVE_OBJECT_NOTIFY;  
	    }
	    if (lwm2m_observed_items [index].inst_id == u16_inst_id)
	    {
	      lwm2m_observed_items [index].u8_observe_state |= LWM2M_OBSERVE_INSTANCE_NOTIFY;  
	    }
	    if (lwm2m_observed_items [index].res_id == u16_res_id)
	    {
	      lwm2m_observed_items [index].u8_observe_state |= LWM2M_OBSERVE_RESOURCE_NOTIFY;  
	    }
	  }
  }
  return 0;
}
 /*! \fn  int lwm2m_check_for_observe_notification()
     \brief  To check if any particular observed item is in notify state or not 
     \return Observe object index on success or negative value on failure
*/
int lwm2m_check_for_observe_notification ()
{
  int obj_index;
  for (obj_index = 0; obj_index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; obj_index ++)
  {
	  if (lwm2m_observed_items[obj_index].u8_observe_state & LWM2M_OBSERVE_OBJECT_ENABLE)
	  {
	    if (lwm2m_observed_items  [obj_index].u8_observe_state & LWM2M_OBSERVE_OBJECT_NOTIFY)
	    {
        lwm2m_observed_items  [obj_index].u8_observe_state &= ~LWM2M_OBSERVE_OBJECT_NOTIFY;
		    return obj_index;
	    }
	  }
  }
  return -1;
}
#endif 
