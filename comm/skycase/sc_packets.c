#include <lwm2m_client.h>


SC_COMM_INFO sc_comm_info;
extern SC_LWM2M_HTTP_COMM_TASK sc_lwm2m_http_comm_task;

int sc_prepare_http_header (INT8U * ptr_request_buf, INT8U u8_pkt_type, INT8U* str_arg, int max_len);
int sc_prepare_data_read_url (INT8U *ptr_temp_buf, int max_len, SC_PKT_DATA_READ_REQ *ptr_read_req);
int sc_prepare_data_delete_url (INT8U *ptr_temp_buf, int max_len, SC_PKT_DATA_DEL_REQ *ptr_del_req);



int sc_get_next_command ()
{
  return sc_comm_info.u8_cur_cmd;
}

int sc_set_command (INT8U u8_cmd, void *ptr_arg)
{
  sc_comm_info.u8_cur_cmd = u8_cmd;
  sc_comm_info.ptr_cmd_arg = ptr_arg;
  sc_comm_info.cmd_result = -1;
  return 0;
}

int sc_set_last_cmd_result (int result)
{
  sc_comm_info.u8_cur_cmd = 0;
  sc_comm_info.cmd_result = result;
  return 0;
}

int sc_get_last_cmd_result ()
{
  return sc_comm_info.cmd_result;
}


int sc_set_resp_pkt_info (void *ptr_resp_pkt, int resp_pkt_len)
{
  sc_lwm2m_http_comm_task.http_resp.ptr_pkt_buf = ptr_resp_pkt;
  sc_lwm2m_http_comm_task.http_resp.pkt_buf_size = resp_pkt_len;
  return 0;
}



int sc_req_add_data_write (SC_PKT_DATA_WRITE_REQ *ptr_update_req, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id)
{
  int res_index;
  SC_RES_INFO *ptr_resource;
  res_index = ptr_update_req->arr_info.num_arr_items;
  ptr_resource = ptr_update_req->res_info; 
  (ptr_resource + res_index)->u16_obj_id = u16_obj_id;
  (ptr_resource + res_index)->u16_inst_id = u16_inst_id;
  (ptr_resource + res_index)->u16_res_id = u16_res_id; 
  ptr_update_req->arr_info.num_arr_items ++; 
  return 0;
}

int sc_req_set_data_read_all (SC_PKT_DATA_READ_REQ *ptr_read_req_info)
{
  ptr_read_req_info->u8_type = SC_DATA_READ_REQ_TYPE_FOR_ALL;
  return 0;
}
int sc_req_set_data_read_obj (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id)
{
  ptr_read_req_info->u8_type = SC_DATA_READ_REQ_TYPE_FOR_OBJ;
  ptr_read_req_info->u16_obj_id = u16_obj_id;
  return 0;
}
int sc_req_set_data_read_inst (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id)
{
  ptr_read_req_info->u8_type = SC_DATA_READ_REQ_TYPE_FOR_INST;
  ptr_read_req_info->u16_obj_id = u16_obj_id;
  ptr_read_req_info->u16_inst_id = u16_inst_id;
  return 0;
}
int sc_req_set_data_read_res (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id)
{
  ptr_read_req_info->u8_type = SC_DATA_READ_REQ_TYPE_FOR_RES;
  ptr_read_req_info->u16_obj_id = u16_obj_id;
  ptr_read_req_info->u16_inst_id = u16_inst_id;
  ptr_read_req_info->u16_res_id = u16_res_id;
  return 0;
}
int sc_req_set_data_read_time (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id, INT32U u32_time)
{
  ptr_read_req_info->u8_type = SC_DATA_READ_REQ_TYPE_FOR_TIME;
  ptr_read_req_info->u16_obj_id = u16_obj_id;
  ptr_read_req_info->u16_inst_id = u16_inst_id;
  ptr_read_req_info->u16_res_id = u16_res_id;
  ptr_read_req_info->u32_timestamp = u32_time;
  return 0;
}

int sc_req_set_data_del_all (SC_PKT_DATA_DEL_REQ *ptr_del_req_info)
{
  ptr_del_req_info->u8_type = SC_DATA_DEL_REQ_TYPE_FOR_ALL;
  return 0;
}
int sc_req_set_data_del_obj (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id)
{
  ptr_del_req_info->u8_type = SC_DATA_DEL_REQ_TYPE_FOR_OBJ;
  ptr_del_req_info->u16_obj_id = u16_obj_id;
  return 0;
}
int sc_req_set_data_del_inst (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id)
{
  ptr_del_req_info->u8_type = SC_DATA_DEL_REQ_TYPE_FOR_INST;
  ptr_del_req_info->u16_obj_id = u16_obj_id;
  ptr_del_req_info->u16_inst_id = u16_inst_id;
  return 0;
}
int sc_req_set_data_del_res (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id)
{
  ptr_del_req_info->u8_type = SC_DATA_DEL_REQ_TYPE_FOR_RES;
  ptr_del_req_info->u16_obj_id = u16_obj_id;
  ptr_del_req_info->u16_inst_id = u16_inst_id;
  ptr_del_req_info->u16_res_id = u16_res_id;
  return 0;
}
int sc_req_set_data_del_time (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id, INT32U u32_time)
{
  ptr_del_req_info->u8_type = SC_DATA_DEL_REQ_TYPE_FOR_TIME;
  ptr_del_req_info->u16_obj_id = u16_obj_id;
  ptr_del_req_info->u16_inst_id = u16_inst_id;
  ptr_del_req_info->u16_res_id = u16_res_id;
  ptr_del_req_info->u32_timestamp = u32_time;
  return 0;
}

int sc_req_add_del_pending_req (SC_PKT_DEL_PENDING_REQUESTS_REQ *ptr_del_req_info, INT32U u32_req_id, INT16U u16_status)
{
  int res_index;
  SC_DEL_PENDING_REQ_INFO *ptr_del_req;
  res_index = ptr_del_req_info->arr_info.num_arr_items;
  ptr_del_req = ptr_del_req_info->req_info; 
  (ptr_del_req + res_index)->u16_status = u16_status;
  (ptr_del_req + res_index)->u32_req_id = u32_req_id;
  ptr_del_req_info->arr_info.num_arr_items ++; 
  return 0;
}

int sc_req_set_clear_pending_event_app_id (SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_event_req_info, INT32U u32_app_id)
{
  ptr_clear_event_req_info->u32_app_id = u32_app_id;
  return 0;
}
int sc_req_add_clear_pending_event (SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_event_req_info, INT16U u16_event_id, INT32U u32_event_count)
{
  int res_index;
  SC_PKT_CLEAR_EVENT_INFO *ptr_clear_event_info;
  res_index = ptr_clear_event_req_info->arr_info.num_arr_items;
  ptr_clear_event_info = ptr_clear_event_req_info->event_info; 
  (ptr_clear_event_info + res_index)->u16_event_id = u16_event_id;
  (ptr_clear_event_info + res_index)->u32_event_count = u32_event_count;
  ptr_clear_event_req_info->arr_info.num_arr_items ++; 
  return 0;
}

int sc_prep_http_request_packet (INT8U *ptr_tx_buf, int max_len)
{
  INT8U u8_cmd = sc_comm_info.u8_cur_cmd;
  int header_len, ret_val;
  int content_len = 0;
  char *ptr_temp_buf = sc_comm_info.u8_tmp_buf;
  if (u8_cmd == SC_CMD_DEVICE_REGISTER)
  {
    strncpy (ptr_temp_buf, SC_API_URL_PATH_DEVICE, SC_COMM_INFO_TMP_BUF_LEN);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_POST, ptr_temp_buf, max_len);
    content_len = sc_prepare_packet_reg_client (ptr_tx_buf + header_len);
  }
  else if (u8_cmd == SC_CMD_DEVICE_UNREGISTER)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s/%s/%d/%d", SC_API_URL_PATH_DEVICE, SC_CLIENT_END_POINT_NAME, \
                  ((SC_PKT_DEV_UNREG_REQ_INFO *)(sc_comm_info.ptr_cmd_arg))->u16_obj_id,
                  ((SC_PKT_DEV_UNREG_REQ_INFO *)(sc_comm_info.ptr_cmd_arg))->u16_inst_id);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_DELETE, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_DATA_WRITE)
  {
    strncpy (ptr_temp_buf, SC_API_URL_PATH_DATA, SC_COMM_INFO_TMP_BUF_LEN);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_POST, ptr_temp_buf, max_len);
    content_len = sc_prepare_packet_data_write (ptr_tx_buf + header_len, sc_comm_info.ptr_cmd_arg);
  }
  else if (u8_cmd == SC_CMD_DATA_READ)
  {
    sc_prepare_data_read_url (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, sc_comm_info.ptr_cmd_arg);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_DATA_DELETE)
  {
    sc_prepare_data_delete_url (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, sc_comm_info.ptr_cmd_arg);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_DELETE, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_READ_PENDING_REQUESTS)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s/%s", SC_API_URL_PATH_REQUEST, SC_CLIENT_END_POINT_NAME);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_DEL_PENDING_REQUESTS)
  {
    strncpy (ptr_temp_buf, SC_API_URL_PATH_REQUEST_DELETE, SC_COMM_INFO_TMP_BUF_LEN);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_POST, ptr_temp_buf, max_len);
    content_len = sc_prepare_packet_del_pending_req (ptr_tx_buf + header_len, sc_comm_info.ptr_cmd_arg);
  }
  else if (u8_cmd == SC_CMD_READ_DEVICE_LIST)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s/%s", SC_API_URL_PATH_DEVICE, SC_CLIENT_END_POINT_NAME);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_READ_APPLICATIONS_LIST)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s", SC_API_URL_PATH_APPLICATIONS);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_READ_ALL_EVENTS)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s/%d", SC_API_URL_PATH_EVENTS, *(INT32U *) sc_comm_info.ptr_cmd_arg);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_READ_PENDING_EVENTS)
  {
    snprintf (ptr_temp_buf, SC_COMM_INFO_TMP_BUF_LEN, "%s/%d", SC_API_URL_PATH_PENDING_EVENT, *(INT32U *) sc_comm_info.ptr_cmd_arg);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_GET, ptr_temp_buf, max_len);
  }
  else if (u8_cmd == SC_CMD_CLEAR_PENDING_EVENTS)
  {
    strncpy (ptr_temp_buf, SC_API_URL_PATH_PENDING_EVENT, SC_COMM_INFO_TMP_BUF_LEN);
    header_len = sc_prepare_http_header (ptr_tx_buf, SC_HTTP_PREP_PKT_TYPE_VERB_PUT, ptr_temp_buf, max_len);
    content_len = sc_prepare_packet_clear_pending_events (ptr_tx_buf + header_len, sc_comm_info.ptr_cmd_arg);
  }
  else
  {
    printf ("Unknown command\r\n");
    while (1);
  }
  ret_val = snprintf ((char*)ptr_tx_buf + header_len - 8, 4, "%d", content_len);
  //ptr_tx_buf [header_len - 8 + ret_val] = ' ';
  for (ret_val = header_len - 8 + ret_val; ret_val < (header_len - 4); ret_val ++)
  {
    ptr_tx_buf [ret_val] = ' ';
  }
  ptr_tx_buf [content_len + header_len] = 0;
  return content_len + header_len;
  
#if SASP
  int data_len, content_len = 0,ret_val;
  INT8U u8_string [40];  
  memset (&sc_lwm2m_http_comm.u8_buffer, 0 ,RS_CLIENT_RX_BUFER_SIZE);
  
  else if (u8_cmd_received == SC_CMD_DATA_DELETE)
  {
  strcpy ((char*)u8_string ,SC_STR_DATA);

  strcat ((char*)u8_string ,(const char *)"/");
    strcat ((char*)u8_string ,SC_CLIENT_END_POINT_NAME);
  sc_prep_packet_for_del_data ((u8_string + strlen(u8_string)), &sc_lwm2m_http_comm.packet_info);
    data_len = sc_prepare_http_header (&sc_lwm2m_http_comm.u8_buffer,SC_HTTP_REQ_METHOD_STR_DELETE, u8_string);
  }
  else if (u8_cmd_received == SC_CMD_DATA_READ)
  {
  strcpy ((char*)u8_string ,SC_STR_DATA);
  strcat ((char*)u8_string ,(const char *)"/");
    strcat ((char*)u8_string ,SC_CLIENT_END_POINT_NAME);
    sc_prep_packet_for_list_data ((u8_string + strlen(u8_string)), &sc_lwm2m_http_comm.packet_info);
    data_len = sc_prepare_http_header (&sc_lwm2m_http_comm.u8_buffer, SC_HTTP_REQ_METHOD_STR_GET, u8_string);
  }


  ret_val = sprintf ((char*)sc_lwm2m_http_comm.u8_buffer + data_len - 8, "%d", content_len);
  sc_lwm2m_http_comm.u8_buffer [data_len - 8 + ret_val] = ' ';
  sc_lwm2m_http_comm.u8_buffer [content_len + data_len] = 0;
  sc_lwm2m_http_comm.tx_len = content_len + data_len;
  #endif
  return 0;
}

int sc_prepare_http_header (INT8U * ptr_request_buf, INT8U u8_pkt_type, INT8U* str_arg, int max_len)
{
  int data_len, ret_len;
  char *ptr_temp_buf = sc_comm_info.u8_tmp_buf;
  if (SC_HTTP_PREP_PKT_TYPE_VERB_GET == (SC_HTTP_PREP_PKT_TYPE_VERB_MASK & u8_pkt_type))
  {
    strncpy ((char*)ptr_request_buf, SC_HTTP_REQ_METHOD_STR_GET, max_len);
  }
  else if (SC_HTTP_PREP_PKT_TYPE_VERB_POST == (SC_HTTP_PREP_PKT_TYPE_VERB_MASK & u8_pkt_type))
  {
    strncpy ((char*)ptr_request_buf, SC_HTTP_REQ_METHOD_STR_POST, max_len);
  }
  else if (SC_HTTP_PREP_PKT_TYPE_VERB_DELETE == (SC_HTTP_PREP_PKT_TYPE_VERB_MASK & u8_pkt_type))
  {
    strncpy ((char*)ptr_request_buf, SC_HTTP_REQ_METHOD_STR_DELETE, max_len);
  }
  else if (SC_HTTP_PREP_PKT_TYPE_VERB_PUT == (SC_HTTP_PREP_PKT_TYPE_VERB_MASK & u8_pkt_type))
  {
    strncpy ((char*)ptr_request_buf, SC_HTTP_REQ_METHOD_STR_PUT, max_len);
  }
  else
    return 0;
  data_len = strlen ((char*)ptr_request_buf);
  max_len -= data_len;
  #if SC_LOCAL_TOMCAT_SERVER
  ret_len = sprintf (ptr_request_buf + data_len, "%s", SC_LOCAL_TOMCAT_URI);
  data_len += ret_len;
  max_len -= ret_len;
  #endif
  ret_len = snprintf ((char*)(ptr_request_buf + data_len), max_len, (const char*)"%s",  str_arg);
  data_len += ret_len;
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), (const char*)" HTTP/1.1\r\nHost: %s", SC_SERVER_API_URL);
  data_len += ret_len;
  
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), (const char*)"\r\nUser-Agent: SkyCase Client\r\n");
  data_len += ret_len;
  base64encode("0:demo_user", 11, ptr_temp_buf, 76);
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), "apikey: %s\r\n", ptr_temp_buf);
  data_len += ret_len;
#if SC_COMM_CONTENT_TYPE == SC_COMM_CONTENT_TYPE_JSON  
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), (const char*)"Accept: text/html,application/json\r\nAccept-Language: en-US,en;q=0.5\r\n");
  data_len += ret_len;
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), "Content-Type: %s", SC_HTTP_HEADER_CONTENT_TYPE_JSON_STR);
  data_len += ret_len;
#elif SC_COMM_CONTENT_TYPE == SC_COMM_CONTENT_TYPE_XML  
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), (const char*)"Accept: text/html,application/xml\r\nAccept-Language: en-US,en;q=0.5\r\n");
  data_len += ret_len;
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), "Content-Type: %s", SC_HTTP_HEADER_CONTENT_TYPE_XML_STR);
  data_len += ret_len;
#endif
  if (u8_pkt_type & SC_HTTP_PREP_PKT_TYPE_KEEP_ALIVE)
  {
    ret_len = sprintf ((char*)(ptr_request_buf + data_len), SC_HTTP_REQ_CONN_KEEP_ALIVE);
  }
  else
  {
    ret_len = sprintf ((char*)(ptr_request_buf + data_len), SC_HTTP_REQ_CONN_CLOSE);
  }
  data_len += ret_len;
  ret_len = sprintf ((char*)(ptr_request_buf + data_len), "Content-Length:      \r\n\r\n");
  data_len += ret_len;
  return data_len;
}

int sc_prepare_data_read_url (INT8U *ptr_temp_buf, int max_len, SC_PKT_DATA_READ_REQ *ptr_read_req)
{
  if (ptr_read_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_OBJ)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_read_req->u16_obj_id);
  }
  else if (ptr_read_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_INST)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_read_req->u16_obj_id, ptr_read_req->u16_inst_id);
  }
  else if (ptr_read_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_RES)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_read_req->u16_obj_id, ptr_read_req->u16_inst_id, ptr_read_req->u16_res_id);
  }
  else if (ptr_read_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_TIME)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_read_req->u16_obj_id, ptr_read_req->u16_inst_id, ptr_read_req->u16_res_id, \
              ptr_read_req->u32_timestamp);
  }
  else //if (ptr_read_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_ALL)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME);
  }
  return 0;
}

int sc_prepare_data_delete_url (INT8U *ptr_temp_buf, int max_len, SC_PKT_DATA_DEL_REQ *ptr_del_req)
{
  if (ptr_del_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_OBJ)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_del_req->u16_obj_id);
  }
  else if (ptr_del_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_INST)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_del_req->u16_obj_id, ptr_del_req->u16_inst_id);
  }
  else if (ptr_del_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_RES)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_del_req->u16_obj_id, ptr_del_req->u16_inst_id, ptr_del_req->u16_res_id);
  }
  else if (ptr_del_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_TIME)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s/%d/%d/%d/%d", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME, \
              ptr_del_req->u16_obj_id, ptr_del_req->u16_inst_id, ptr_del_req->u16_res_id, \
              ptr_del_req->u32_timestamp);
  }
  else //if (ptr_del_req->u8_type == SC_DATA_READ_REQ_TYPE_FOR_ALL)
  {
    snprintf (ptr_temp_buf, max_len, "%s/%s", SC_API_URL_PATH_DATA, SC_CLIENT_END_POINT_NAME);
  }
  return 0;
}