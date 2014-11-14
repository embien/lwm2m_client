/*! \file 
  \brief      codereviewed Module for Transmitting and receiving CoAP messages over UDP 
 
  Contains the logic for assembling and dismantling the CoAP packets 
*/

#include <lwm2m_client.h>
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
/*! Structure variable to hold transmit packet*/
COAP_PACKET_INFO coap_tx_packet;

/*! \fn       coap_transmit_packet (COAP_PACKET_INFO *ptr_packet)
    \brief     Assembles a CoAP message and transmit the packet over UDP 
    \param[in] ptr_packet  Contains the CoAP message packet to be transmitted after assembling
    \return    int         Zero on success  or error code on failure
*/
int coap_transmit_packet (COAP_PACKET_INFO *ptr_packet)
{
  INT8U u8_option_delta = 0, data_len = 0,u8_len, token_index = 0;
  INT8U *data_buf = get_coap_data_buf ();
  if (ptr_packet->u8_packet_class == COAP_PACKET_CLASS_REQ) 
  {
    data_buf [data_len ++] = COAP_HEADER_VERSION | COAP_HEADER_TYPE_CONFIRMABLE;
    data_buf [data_len ++] = (INT8U)(((ptr_packet->u8_packet_class << 5) | (ptr_packet->u8_packet_detail)));
    data_buf [data_len ++] = ptr_packet->u16_msg_id >> 8;              
    data_buf [data_len ++] = (ptr_packet->u16_msg_id);
  }
  else
  {
    if (ptr_packet->u8_token_len)
	{
      data_buf [data_len ++] = COAP_HEADER_VERSION | COAP_HEADER_TYPE_ACKNOWLEDGEMENT | ptr_packet->u8_token_len;
	}
	else
	{
      data_buf [data_len ++] = COAP_HEADER_VERSION | COAP_HEADER_TYPE_ACKNOWLEDGEMENT;
	}
	data_buf [data_len++] = (INT8U)(((ptr_packet->u8_packet_class << 5) | (ptr_packet->u8_packet_detail)));
    data_buf [data_len ++] = (ptr_packet->u16_msg_id >> 8);
    data_buf [data_len ++] = (ptr_packet->u16_msg_id);
	while (token_index < ptr_packet->u8_token_len)
    {
	  data_buf [data_len ++] = ptr_packet->u8_token_value [token_index ++];
    }
  }  
  if (ptr_packet->u8_valid_fields & COAP_PACKET_VALID_URI_PATH) 
  {
    u8_len = (INT8U)strlen((const char *)ptr_packet->uri_path_str);
    u8_option_delta = COAP_OPTION_URI_PATH - u8_option_delta;
    if (u8_len >= COAP_OPTION_LENGTH_8BITS)
    {
      data_buf [data_len ++] = (INT8U)(COAP_OPTION_FIELD (u8_option_delta) | COAP_OPTION_LENGTH_8BITS);
      data_buf [data_len ++] = (INT8U)(u8_len - COAP_OPTION_LENGTH_8BITS);
    }
    else
    {
      data_buf [data_len ++] = (INT8U)(COAP_OPTION_FIELD (u8_option_delta) | u8_len);
    }
    strcpy ((char *)(data_buf + data_len), (const char *)(ptr_packet->uri_path_str));
    data_len += u8_len;
  }
  if (ptr_packet->u8_valid_fields & COAP_PACKET_VALID_URI_QUERY) // request
  {
    u8_len = (INT8U)(strlen ((const char *)ptr_packet->uri_path_query));
    u8_option_delta = COAP_OPTION_URI_QUERY - u8_option_delta;
    if (u8_len >= COAP_OPTION_LENGTH_8BITS)
    {
      data_buf [data_len ++] = (INT8U)(COAP_OPTION_FIELD (u8_option_delta) | COAP_OPTION_LENGTH_8BITS);
      data_buf [data_len ++] = (INT8U)(u8_len - COAP_OPTION_LENGTH_8BITS);
    }
    else
    {
      data_buf [data_len ++] = (INT8U)(COAP_OPTION_FIELD (u8_option_delta) | u8_len);
    }
    strcpy ((char *)(data_buf + data_len),(const char *)ptr_packet->uri_path_query);
    data_len += u8_len;
  }
  if (ptr_packet->u8_valid_fields & COAP_PACKET_VALID_OBSERVE)
  {
    if (ptr_packet->u8_observe_count == 0)
      data_buf [data_len ++] = COAP_OPTION_OBSERVE_MARKER;
	else
	{
	  data_buf [data_len ++] = LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER;
      data_buf [data_len ++] = ptr_packet->u8_observe_count;
	}
  } 
  if (ptr_packet->u8_valid_fields & COAP_PACKET_VALID_URI_PAYLOAD)
  {
    data_buf [data_len ++] = (INT8U)COAP_OPTION_PAYLOAD_MARKER;
    memcpy (data_buf + data_len, ptr_packet->payload, ptr_packet->u8_payload_len);
    data_len += ptr_packet->u8_payload_len;
  }
  if (ptr_packet->u8_valid_fields & COAP_PACKET_VALID_OBSERVE_CANCEL)
  {
    return 0;	
  }
  coap_send_to_server (data_buf, data_len);
  return 0;
}

/*! \fn       int coap_decode_packet (COAP_PACKET_INFO *ptr_packet, INT8U *ptr_buf, int recv_len)
    \brief    Dismantles the received bytes and fills the information on CoAP message packet
    \param[out] ptr_packet  Contains the CoAP message header
    \param[in]  ptr_buf     Contains the received CoAP message packet information from server
    \param[in]  recv_len    Contains the length of received bytes  
    \return     int         Zero on success  or error code on failure
*/
int coap_decode_packet (COAP_PACKET_INFO *ptr_packet, INT8U *ptr_buf, int recv_len)
{
  INT8U u8_option_delta, u8_option_len, token_index = 0;
  int process_index = 0;
  ptr_packet->u8_valid_fields = 0;
  ptr_packet->u8_valid_locations = 0;
  ptr_packet->u8_valid_ids = 0;
  ptr_packet->u8_token_len = 0; 
  u8_option_delta = 0;
  ptr_packet->u8_packet_type = ptr_buf [process_index ++];
  if (ptr_packet->u8_packet_type & COAP_PACKET_TOKEN_LEN_FIELDS)
  {
    ptr_packet->u8_token_len = ptr_packet->u8_packet_type & COAP_PACKET_TOKEN_LEN_FIELDS;
  }
  ptr_packet->u8_packet_class = ptr_buf [process_index] >> 3;
  ptr_packet->u8_packet_detail = ptr_buf [process_index] & 0x1F;
  process_index ++;
  ptr_packet->u16_msg_id = (ptr_buf [process_index ++]) << 8; 
  ptr_packet->u16_msg_id |= ptr_buf[process_index ++];
  while (token_index <  ptr_packet->u8_token_len)
  {
    ptr_packet->u8_token_value [token_index ++] = ptr_buf [process_index ++]; 
  }
  while (process_index < recv_len)
  {
    if (ptr_buf [process_index] == COAP_OPTION_PAYLOAD_MARKER)
    {
      process_index ++;
      ptr_packet->u8_valid_fields |= COAP_PACKET_VALID_PAYLOAD;
      u8_option_len = (INT8U)(recv_len - process_index); 
      ptr_packet->u8_payload_len = u8_option_len;
      memcpy (ptr_packet->payload, ptr_buf + process_index, u8_option_len);
      process_index += u8_option_len;
      continue;
    }
    u8_option_delta += (ptr_buf [process_index] >> 4) & 0x0F;   //to find the option value
    u8_option_len = ptr_buf [process_index] & 0xF;
    process_index ++;
    if (u8_option_len == COAP_OPTION_LENGTH_8BITS)
    {
      u8_option_len += ptr_buf [process_index ++];
    }
    if (u8_option_delta == COAP_OPTION_LOCATION_PATH)
    {
      ptr_packet->u8_valid_fields |= COAP_PACKET_VALID_LOCATION;
      strncpy ((char  *)(ptr_packet->uri_location_path_str [ptr_packet->u8_valid_locations]), \
                (const char *)(ptr_buf + process_index), (size_t)u8_option_len); 
      ptr_packet->uri_location_path_str [ptr_packet->u8_valid_locations] [u8_option_len] = '\0';
      process_index += u8_option_len;
      ptr_packet->u8_valid_locations ++;
    }
    else if (u8_option_delta == COAP_OPTION_URI_PATH)
    {
      ptr_packet->u8_valid_fields |= COAP_PACKET_VALID_URI_PATH;
      strncpy ((char *)(ptr_packet->uri_location_path_str [ptr_packet->u8_valid_locations]), \
                (const char *)(ptr_buf + process_index), (size_t)u8_option_len); 
      ptr_packet->uri_location_path_str [ptr_packet->u8_valid_locations][u8_option_len] = '\0';
      process_index += u8_option_len;
      ptr_packet->u8_valid_locations ++;
    }
	else if (u8_option_delta  == COAP_OPTION_OBSERVE)
	{
      ptr_packet->u8_misc_req |= COAP_OBSERVE_STATE_ENABLE;
	}    
  }
  return 0; 
} 
#endif
