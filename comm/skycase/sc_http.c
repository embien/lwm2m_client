#include <lwm2m_client.h>


extern SC_LWM2M_HTTP_COMM_TASK sc_lwm2m_http_comm_task;

int sc_http_resp_process_header_field (SC_HTTP_RESPONSE *ptr_http_resp, INT8U *ptr_field,INT8U* ptr_value, \
                                       int value_len)
{
  if (ptr_value == NULL)
  {
    if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_VERSION, 8))
    {
      ptr_http_resp->resp_code = atoi (ptr_field + 8);
    }
    if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_EMPTY, 2))
    {
      return 0;
    }
  }
  else
  {
    if (*ptr_value == ' ')
    {
      ptr_value ++;
      value_len --;
    }
    if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_SERVER, 6))
    {
      if (value_len > SC_HTTP_RESP_SERVER_NAME_SIZE - 1)
        value_len = SC_HTTP_RESP_SERVER_NAME_SIZE - 1;
      strncpy (ptr_http_resp->server_name, ptr_value, value_len);
      ptr_http_resp->server_name [value_len] = 0;
    }
    else if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_DATE, 4))
    {
      if (value_len > SC_HTTP_RESP_DATE_AND_TIME_SIZE - 1)
        value_len = SC_HTTP_RESP_DATE_AND_TIME_SIZE - 1;
      strncpy (ptr_http_resp->date, ptr_value, value_len);
      ptr_http_resp->date [value_len] = 0;    
    }
    else if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_CONTENT_TYPE, 12))
    {
      if (value_len > SC_HTTP_RESP_CONTENT_TYPE_SIZE - 1)
        value_len = SC_HTTP_RESP_CONTENT_TYPE_SIZE - 1;
      if (!strnicmp ((ptr_field + 12 + 2), SC_HTTP_RESP_FIELD_CONTENT_TYPE_JSON, 16))
        ptr_http_resp->u8_content_type = SC_HTTP_RESP_CONTENT_TYPE_JSON;     
    }
    else if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_CONNECTION, 10))
    {
      if (value_len > SC_HTTP_RESP_CONNECTION_SIZE - 1)
        value_len = SC_HTTP_RESP_CONNECTION_SIZE - 1;
      if (!strnicmp ((ptr_field + 10 + 2), SC_HTTP_RESP_FIELD_CONNECTION_CLOSE, 5))
        ptr_http_resp->u8_conn_state = SC_HTTP_RESP_CONNECTION_CLOSE;    
    }
    else if (!strnicmp (ptr_field, SC_HTTP_RESP_FIELD_CONTENT_LENGTH, 13))
    {
      if (value_len > SC_HTTP_RESP_CONTENT_LENGTH_SIZE - 1)
        value_len = SC_HTTP_RESP_CONTENT_LENGTH_SIZE - 1;
      ptr_http_resp->u16_content_len =  atoi(ptr_field + 16); 
    }
  }
  return 1;
}
int sc_http_validate_rx_packet (SC_HTTP_RESPONSE *ptr_http_resp, int rx_len)
{
  int index, value_index = 0; 
  INT8U* ptr_field, *ptr_value, *ptr_buf;
  ptr_buf = ptr_http_resp->ptr_resp;
process_again:
  if (ptr_http_resp->u8_process_state == SC_HTTP_RESP_PROCESS_STATE_IN_HEADER)
  {
    index = ptr_http_resp->processed_len;
    ptr_field = ptr_buf + index;
    ptr_value = NULL;
    for ( ;index < rx_len; index ++)
    {
      if ((ptr_buf [index] == ':') && (ptr_value == NULL))
      {
        ptr_value = ptr_buf + index + 1;
        value_index = index + 1;
      }
      if (ptr_buf [index] == '\n')
      {
        if (!sc_http_resp_process_header_field (ptr_http_resp, ptr_field, ptr_value, index - value_index - 1))
        {
          ptr_http_resp->u8_process_state = SC_HTTP_RESP_PROCESS_STATE_IN_BODY;
          ptr_http_resp->processed_len = index + 1;
          ptr_http_resp->u16_content_pos = index + 1;
          goto process_again;
        }
        ptr_field = ptr_buf + index + 1;
        ptr_value = NULL;
        ptr_http_resp->processed_len = index + 1;
      }
    }
  }
  else if (ptr_http_resp->u8_process_state == SC_HTTP_RESP_PROCESS_STATE_IN_BODY)
  {
    if (rx_len >= ptr_http_resp->u16_content_pos + ptr_http_resp->u16_content_len)
    {
      ptr_http_resp->u8_process_state = SC_HTTP_RESP_PROCESS_STATE_DONE;
      return 0;
    }   
  }
  return 1;
}
