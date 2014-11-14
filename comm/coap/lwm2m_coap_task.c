/*! \file 
  \brief      Module implementing LWM2M client over CoAP
 
  Contains the logic for registering and communicating with CoAP LWM2M Server
*/

#include <lwm2m_client.h>
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP

/*! Declaration of structure variable for LWM2M process information */
LWM2M_PROCESS_INFO lwm2m_rx_proc_info;

/*! Declaration of structure variable for CoAP receive packet information */
COAP_PACKET_INFO coap_rx_packet;

/*! Global variable for LWM2M client state process */
int lwm2m_client_state;
int lwm2m_client_connect = 0;

int lwm2m_encode_process_req (COAP_PACKET_INFO *, LWM2M_PROCESS_INFO *);
void lwm2m_udp_client (INT8U);
int init_lwm2m_udp_client ();
int lwm2m_connect ();
int lwm2m_disconnect ();


/*! \fn         void send_register_request ()
    \brief      Sends registration CoAP packet to server for establishing communication 
    \param[in]  None     
    \return     None
*/
void send_register_request ()
{
  int index;
#if LWM2M_CLIENT_COMMUNICATION_UDP_COAP
  strncpy ((char *)(coap_tx_packet.uri_path_str), (const char *)LWM2M_REQ_REGISTER_DEVICE, (size_t)COAP_MAX_URI_PATH_LEN);
  coap_tx_packet.uri_path_str [strlen (LWM2M_REQ_REGISTER_DEVICE)] = 0;
  strncpy ((char *)(coap_tx_packet.uri_path_query),(const char *)(LWM2M_CLIENT_NAME),(size_t)COAP_MAX_URI_QUERY_LEN);
  coap_tx_packet.uri_path_query [strlen (LWM2M_CLIENT_NAME)] = 0;
#endif  
  coap_tx_packet.u8_valid_fields = COAP_PACKET_VALID_URI_PATH | COAP_PACKET_VALID_URI_QUERY | COAP_PACKET_VALID_URI_PAYLOAD;
  coap_tx_packet.u8_packet_class = COAP_PACKET_CLASS_REQ;
  coap_tx_packet.u8_packet_detail = COAP_PACKET_CLASS_REQ_POST;	
  index = lwm2m_get_obj_inst_list_for_reg (coap_tx_packet.payload, COAP_MAX_PAYLOAD_LEN);
  if (index < 0)
  {
    printf ("Unable to prepare reg packet\n\r");
    return;
  }
  coap_tx_packet.u8_payload_len = (INT8U)index;
  coap_transmit_packet (&coap_tx_packet);  
}

/*! \fn        int validate_req_resp (COAP_PACKET_INFO *ptr_packet)
    \brief     Validates the received client id from server
    \param[in] ptr_packet     Contains the CoAP message packets
    \return    int            Zero on sucess or error code on failure 
*/
int validate_req_resp (COAP_PACKET_INFO *ptr_packet)
{
  int index = 1;
  char *ptr_end;
  ptr_packet->client_id = (INT8U)strtol ((const char *)(ptr_packet->uri_location_path_str [index]),(char **) &ptr_end, (int)10);
  return 0;
}

/*! \fn       int init_lwm2m_udp_client ()
    \brief    Initialising the CoAP/Udp socket communication  
    \param[in]  None     
    \return     int     Zero on Success or error code on failure   
*/
int init_lwm2m_udp_client ()
{
  init_coap_udp_socket ();
  lwm2m_client_state = LWM2M_CLIENT_IDLE;
  return 0;
}

/*! \fn       int lwm2m_decode_process_req (LWM2M_PROCESS_INFO *ptr_proc_info, COAP_PACKET_INFO *ptr_packet)
    \brief    Decodes the CoAP Packet for processing the request from server
    \param[out]  ptr_proc_info     Contains the information for LWM2M process  
    \param[in]   ptr_packet        Contains the CoAP message header
    \return      int               Zero on success or error code on failure    
*/
int lwm2m_decode_process_req (LWM2M_PROCESS_INFO *ptr_proc_info, COAP_PACKET_INFO *ptr_packet)
{
  char *ptr_end;
  int index;
  if (ptr_packet-> u8_packet_class == COAP_PACKET_CLASS_REQ)
  {
     if (ptr_packet-> u8_packet_detail == COAP_PACKET_CLASS_REQ_GET)
       ptr_proc_info->u8_request = LWM2M_PROCESS_REQ_READ;
     else if (ptr_packet-> u8_packet_detail == COAP_PACKET_CLASS_REQ_PUT)
       ptr_proc_info->u8_request = LWM2M_PROCESS_REQ_WRITE;
	 else if (ptr_packet-> u8_packet_detail == COAP_PACKET_CLASS_REQ_POST)
	   ptr_proc_info->u8_request = LWM2M_PROCESS_REQ_EXECUTE;
	 else
       return -1;
  }
  ptr_proc_info->u8_num_path_elements = 0;
  for (index = 0; index < ptr_packet->u8_valid_locations; index ++)
  {
    ptr_proc_info->object_path  [index] = (INT16U) strtol ((const char*)(ptr_packet->uri_location_path_str [index]),(char **) &ptr_end, (int)10);
    ptr_proc_info->u8_num_path_elements ++;
  }
  ptr_proc_info->u8_value_len = ptr_packet->u8_payload_len;
  memcpy (ptr_proc_info->value, ptr_packet->payload, ptr_proc_info->u8_value_len);
  ptr_proc_info->value [ptr_proc_info->u8_value_len] = '\0';  
  return 0;
}

/*! \fn     int lwm2m_process_request_observe_changed (int observe_index)
    \brief    Process the observed items when comes to  notify
    \param[in]  observe_index     Contains the index of the observed items
    \return     int               Zero on Success or error code on failure
*/
int lwm2m_process_request_observe_changed (int observe_index)
{
  int token_index = 0;
  lwm2m_rx_proc_info.u8_num_path_elements = 0;
  lwm2m_observed_items[observe_index].u8_notify_count ++;
  lwm2m_rx_proc_info.u8_request = LWM2M_PROCESS_REQ_READ;
  if (lwm2m_observed_items[observe_index].u8_valid_locations >= 1) 
  {
    lwm2m_rx_proc_info.object_path[LWM2M_PATH_INDEX_OBJECT] = lwm2m_observed_items[observe_index].obj_id; 
    lwm2m_rx_proc_info.u8_num_path_elements ++;
  }
  if (lwm2m_observed_items[observe_index].u8_valid_locations >= 2)
  {
    lwm2m_rx_proc_info.object_path[LWM2M_PATH_INDEX_INST] = lwm2m_observed_items[observe_index].inst_id; 
	lwm2m_rx_proc_info.u8_num_path_elements ++;
  }
  if (lwm2m_observed_items[observe_index].u8_valid_locations >= 3)
  {
    lwm2m_rx_proc_info.object_path[LWM2M_PATH_INDEX_RES] = lwm2m_observed_items[observe_index].res_id; 
	lwm2m_rx_proc_info.u8_num_path_elements ++;
  }
  lwm2m_process_request_obj (&lwm2m_rx_proc_info);
  lwm2m_rx_proc_info.resource_type =  LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER;//set marker for observe notify
  lwm2m_rx_proc_info.u8_resp_detail = LWM2M_PROCESS_RESP_CHANGED;
  coap_tx_packet.u8_observe_count = lwm2m_observed_items[observe_index].u8_notify_count;
  lwm2m_encode_process_req (&coap_tx_packet, &lwm2m_rx_proc_info);
  coap_tx_packet.u8_valid_fields |= COAP_PACKET_VALID_OBSERVE;
  coap_tx_packet.u16_msg_id = (INT8U)(lwm2m_observed_items[observe_index].u16_msg_id << 8);
  coap_tx_packet.u16_msg_id = lwm2m_observed_items[observe_index].u16_msg_id;
  coap_tx_packet.u8_token_len =  lwm2m_observed_items[observe_index].u8_token_len; 
  while (token_index < coap_tx_packet.u8_token_len)
  {
    coap_tx_packet.u8_token_value [token_index] = lwm2m_observed_items[observe_index].u8_token_value [token_index]; 
    token_index ++;
  }  
  return 0;  
}

/*! \fn       int lwm2m_encode_process_req (COAP_PACKET_INFO *ptr_out_packet, LWM2M_PROCESS_INFO *ptr_proc_info)
    \brief    Prepares the CoAP message packets from LWM2M response messages
    \param[out]  ptr_out_packet   Contains the CoAP message packet
    \param[in]  ptr_proc_info     Contains the information of the response of LWM2M
    \return     int               Zero on Success or error code on failure
*/
int lwm2m_encode_process_req (COAP_PACKET_INFO *ptr_out_packet, LWM2M_PROCESS_INFO *ptr_proc_info)
{
  ptr_out_packet->u8_valid_fields = 0;   
  if (ptr_proc_info->u8_request == LWM2M_PROCESS_REQ_READ)
  {
    ptr_out_packet->u8_packet_class = ptr_proc_info->u8_resp_code;
    ptr_out_packet->u8_packet_detail = ptr_proc_info->u8_resp_detail;
	memcpy (ptr_out_packet->payload,  ptr_proc_info->value, ptr_proc_info->u8_value_len);
    ptr_out_packet->u8_payload_len = ptr_proc_info->u8_value_len;
	ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_URI_PAYLOAD;
    ptr_out_packet->payload [ptr_proc_info->u8_value_len] = '\0';
  }
  else if (ptr_proc_info->u8_request == LWM2M_PROCESS_REQ_WRITE)
  {
    ptr_out_packet->u8_packet_class = ptr_proc_info->u8_resp_code;
    ptr_out_packet->u8_packet_detail =  ptr_proc_info->u8_resp_detail;
  }
  else if (ptr_proc_info->u8_request == LWM2M_PROCESS_REQ_EXECUTE)
  {
    ptr_out_packet->u8_packet_class = ptr_proc_info->u8_resp_code;
    ptr_out_packet->u8_packet_detail =  ptr_proc_info->u8_resp_detail;
  }
  else if (ptr_proc_info->u8_request == LWM2M_PROCESS_RESP_ERROR)
  {
    ptr_out_packet->u8_packet_class = ptr_proc_info->u8_resp_code;
    ptr_out_packet->u8_packet_detail =  ptr_proc_info->u8_resp_detail;
  }
  return 0;

 }
 
 /*! \fn      int lwm2m_process_request (COAP_PACKET_INFO *ptr_in_packet)
    \brief    Process the read/write/execute/observe for requested LWM2M or IPSO objects/instances/resoureces
    \param[in]  ptr_in_packet        Containes the CoAP message packet
    \return     int                  Zero on success or error code on failure  
*/
int lwm2m_process_request (COAP_PACKET_INFO *ptr_in_packet)
{
  int token_index = 0, index;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_RESOURCE_INFO *ptr_res_info;
  COAP_PACKET_INFO *ptr_out_packet = &coap_tx_packet;
  lwm2m_decode_process_req (&lwm2m_rx_proc_info, ptr_in_packet);
  lwm2m_process_request_obj (&lwm2m_rx_proc_info);
  lwm2m_encode_process_req (ptr_out_packet, &lwm2m_rx_proc_info);
  ptr_out_packet->u16_msg_id = (ptr_in_packet->u16_msg_id << 8);
  ptr_out_packet->u16_msg_id = ptr_in_packet->u16_msg_id;
  ptr_out_packet->u8_token_len =  ptr_in_packet->u8_token_len; 
  while (token_index < ptr_out_packet->u8_token_len)
  {
    ptr_out_packet->u8_token_value [token_index] = ptr_in_packet->u8_token_value [token_index ]; 
    token_index ++;
  }
#if LWM2M_CLIENT_SUPPORT_OBSERVE
  if ((ptr_in_packet->u8_packet_type & COAP_OBSERVE_STATE_RESET) == COAP_OBSERVE_STATE_RESET)
  {
    for (index = 0; index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; index ++)
	{
      if (ptr_out_packet->u16_msg_id  == lwm2m_observed_items[index].u16_msg_id)
	  {
	    lwm2m_observed_items[index].u8_observe_state  = 0;
		ptr_out_packet->u8_valid_fields = 0; 
		ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_OBSERVE_CANCEL;
		break;
	  }
	}
  }
  if (ptr_in_packet->u8_misc_req & COAP_OBSERVE_STATE_ENABLE && (ptr_out_packet->u8_packet_class != LWM2M_PROCESS_RESP_ERROR))
  {  
	ptr_out_packet->u8_observe_count = 0;
    ptr_in_packet->u8_misc_req &= ~COAP_OBSERVE_STATE_ENABLE;
	for (index = 0; index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; index ++)
    { 
	  if ((lwm2m_observed_items[index].u8_observe_state & COAP_OBSERVE_STATE_ENABLE))
	  {
	    if ((ptr_in_packet->u8_valid_locations == 1) && (lwm2m_observed_items[index].u8_valid_locations == 1))
		{
		  if (lwm2m_observed_items[index].obj_id == supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].u16_obj_id)
		  {
			ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_OBSERVE;
		    lwm2m_observed_items[index].u8_notify_count ++;
			lwm2m_observed_items[index].u16_msg_id = ptr_in_packet->u16_msg_id;
			lwm2m_rx_proc_info.resource_type =  LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER;
			ptr_out_packet->u8_observe_count = lwm2m_observed_items[index].u8_notify_count;
			return 0;
	      }
		}
		if ((ptr_in_packet->u8_valid_locations == 2) &&(lwm2m_observed_items[index].u8_valid_locations == 2))
		{
		  ptr_instance_info = supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].ptr_inst_list;
		  if ((lwm2m_observed_items[index].obj_id == \
			  supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].u16_obj_id)&&\
		    (lwm2m_observed_items[index].inst_id  ==  ptr_instance_info->u16_inst_id))
	      {
			ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_OBSERVE;
	        lwm2m_observed_items[index].u8_notify_count ++;
			lwm2m_observed_items[index].u16_msg_id = ptr_in_packet->u16_msg_id;
			lwm2m_rx_proc_info.resource_type =  LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER;
			ptr_out_packet->u8_observe_count = lwm2m_observed_items[index].u8_notify_count;
			return 0;
	      }
		}
	    if ((ptr_in_packet->u8_valid_locations == 3) && (lwm2m_observed_items[index].u8_valid_locations == 3))
		{
		  ptr_instance_info = supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].ptr_inst_list;
		  ptr_obj_res_info = ptr_instance_info [lwm2m_rx_proc_info.u16_inst_id_index].ptr_res_list;
          ptr_res_info = ptr_obj_res_info [lwm2m_rx_proc_info.u16_res_id_index].ptr_resource_info; 
		  if ((lwm2m_observed_items[index].obj_id == \
			 supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].u16_obj_id)&&\
		    (lwm2m_observed_items[index].inst_id == ptr_instance_info->u16_inst_id)&&\
			 (lwm2m_observed_items[index].res_id  == ptr_res_info->u16_res_id))
	      {
			ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_OBSERVE;
		    lwm2m_observed_items[index].u8_notify_count ++;
			lwm2m_observed_items[index].u16_msg_id = ptr_in_packet->u16_msg_id;
		    lwm2m_rx_proc_info.resource_type =  LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER;
            ptr_out_packet->u8_observe_count = lwm2m_observed_items[index].u8_notify_count;
			return 0;
	      }
		}
	  }
	}
	for (index = 0; index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; index ++)
    {
      if ((lwm2m_observed_items[index].u8_observe_state & COAP_OBSERVE_STATE_ENABLE))
	  {
		  continue;
	  }
	  else
	  { 
	    if (ptr_in_packet->client_id < 0)
		{
		  lwm2m_rx_proc_info.u8_request = LWM2M_PROCESS_RESP_ERROR; 
		  lwm2m_rx_proc_info.u8_resp_code = LWM2M_PROCESS_RESP_ERROR;
          lwm2m_rx_proc_info.u8_resp_detail = LWM2M_PROCESS_RESP_ERR_NOT_ALLLOWED;
		  lwm2m_encode_process_req (ptr_out_packet, &lwm2m_rx_proc_info);
		  break;			  
		}
		lwm2m_observed_items[index].u8_notify_count = 0;
		lwm2m_observed_items[index].u8_token_len = ptr_in_packet->u8_token_len;
		if((lwm2m_observed_items[index].u8_token_len) < 0)
		{
		  lwm2m_rx_proc_info.u8_request = LWM2M_PROCESS_RESP_ERROR; 
		  lwm2m_rx_proc_info.u8_resp_code = LWM2M_PROCESS_RESP_SERVER_ERROR;
          lwm2m_rx_proc_info.u8_resp_detail = LWM2M_PROCESS_RESP_ERR_BAD_REQ;
		  lwm2m_encode_process_req (ptr_out_packet, &lwm2m_rx_proc_info);
		  break;		
		}
		ptr_out_packet->u8_valid_fields |= COAP_PACKET_VALID_OBSERVE;
        lwm2m_observed_items[index].u8_observe_state = COAP_OBSERVE_STATE_ENABLE;
	    lwm2m_observed_items[index].u16_msg_id = ptr_in_packet->u16_msg_id;
	    lwm2m_observed_items[index].u8_valid_locations = ptr_in_packet->u8_valid_locations;
		if (ptr_in_packet->u8_valid_locations >= 1)
		{
		  lwm2m_observed_items[index].obj_index  = lwm2m_rx_proc_info.u16_obj_id_index;
		  lwm2m_observed_items[index].obj_id = supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].u16_obj_id;
		}
		if (ptr_in_packet->u8_valid_locations >= 2)
		{
		  lwm2m_observed_items[index].inst_index  = lwm2m_rx_proc_info.u16_inst_id_index;
	 	  ptr_instance_info = supported_object_list [lwm2m_rx_proc_info.u16_obj_id_index].ptr_inst_list;
          lwm2m_observed_items[index].inst_id  = ptr_instance_info->u16_inst_id;
		}
		if (ptr_in_packet->u8_valid_locations >= 3)
		{
		  lwm2m_observed_items[index].res_index  = lwm2m_rx_proc_info.u16_res_id_index;
		  ptr_obj_res_info = ptr_instance_info [lwm2m_observed_items[index].res_index].ptr_res_list; 
          ptr_res_info = ptr_obj_res_info [ lwm2m_observed_items[index].inst_index].ptr_resource_info; 
          lwm2m_observed_items[index].res_id = ptr_res_info->u16_res_id;
		}
		while (token_index < lwm2m_observed_items[index].u8_token_len)
        {
          lwm2m_observed_items[index].u8_token_value[token_index] = ptr_in_packet->u8_token_value[token_index]; 
          token_index ++;
        }
	    break;
	  } 
	}
	if (index == LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS)
	{
	  lwm2m_rx_proc_info.u8_request = LWM2M_PROCESS_RESP_ERROR; 
    lwm2m_rx_proc_info.u8_resp_code = LWM2M_PROCESS_RESP_SERVER_ERROR;
    lwm2m_rx_proc_info.u8_resp_detail = LWM2M_PROCESS_RESP_ERR_BAD_REQ;
	  lwm2m_encode_process_req (ptr_out_packet, &lwm2m_rx_proc_info);
  }
}
#endif
return 0;
}

/*! \fn      void lwm2m_client_resource_observe_task (INT8U ub_task_id)
    \brief   Implements the observe task for requested LWM2M objects/instance/resource 
    \param[in]  ub_task_id    Identifier for the task. Can be discarded.
    \return     void          None   
*/
void lwm2m_client_resource_observe_task (INT8U ub_task_id)
{
  //lwm2m_resource_changed  (LWM2M_OBJ_ID_IPSO_DIG_OUT, 0,LW_RES_ID_DIG_OUTPUT_STATE);
  //lwm2m_resource_changed  (LWM2M_OBJ_ID_IPSO_DIG_IN, 0,LW_RES_ID_DIG_INPUT_STATE); 
  //lwm2m_resource_changed  (LWM2M_OBJ_ID_IPSO_ACCE_METER, 0,LW_RES_ID_X_VALUE);
  //lwm2m_resource_changed  (LWM2M_OBJ_ID_IPSO_SET_POINT, 0,LW_RES_ID_SET_POINT_VALUE);
}

/*! \fn         void lwm2m_udp_client (INT8U ub_task_id)
    \brief      Implements the LWM2M client funcitonality over CoAP/UDP
    \param[in]  ub_task_id   Identifier for the task. Can be discarded.
    \return     None
*/
void lwm2m_udp_client_task (INT8U ub_task_id)
{
  INT8U reg_buf [COAP_UDP_MAX_DATA_SIZE];
  int index, status;
  int recv_len;
  switch (lwm2m_client_state)
  {
    case LWM2M_CLIENT_IDLE:
    {
	  if (lwm2m_client_connect)
	  {
		  lwm2m_client_state = LWM2M_CLIENT_STATE_SEND_REG_REQ;
		  
	  }
      break;
    }
    case LWM2M_CLIENT_STATE_SEND_REG_REQ:
    {
	  send_register_request ();
	  lwm2m_client_state = LWM2M_CLIENT_STATE_WAIT_FOR_REG_RESP;
      break;
    }
    case LWM2M_CLIENT_STATE_WAIT_FOR_REG_RESP:
    {
      recv_len = coap_recv_from_server (reg_buf, COAP_UDP_MAX_DATA_SIZE);
      if (recv_len)
	  {
	    printf ("%d:bytes recived\r\n", recv_len);
        for (index = 0; index < recv_len; index ++)
        {
          printf (" %02x", reg_buf [index]);
        }
        printf ("\r\n");
        coap_decode_packet (&coap_rx_packet, reg_buf, recv_len);
        if (validate_req_resp (&coap_rx_packet) == 0)
        {
          printf ("client suceesfully registered\r\n");
		  lwm2m_client_state = LWM2M_CLIENT_STATE_COMM;
        }
	  }	  
      break;
	}
	case LWM2M_CLIENT_STATE_COMM:
    {
      recv_len = coap_recv_from_server (reg_buf, COAP_UDP_MAX_DATA_SIZE);
	  if (recv_len)
	  {
	    printf ("%d:bytes recived\r\n", recv_len);
        for (index = 0; index < recv_len; index ++)
        {
          printf (" %02x", reg_buf [index]);
        }
        status = coap_decode_packet (&coap_rx_packet, reg_buf, recv_len);
        if (status == 0)
        {
          status = lwm2m_process_request (&coap_rx_packet);
          if (status == 0)
          {
            coap_transmit_packet (&coap_tx_packet);
			recv_len = 0;
		  }
		}
      }    
	  else
	  {
	    index = lwm2m_check_for_observe_notification ();
        if (index >= 0)
		{
	      status = lwm2m_process_request_observe_changed (index);
		  if (status == 0)
		  {
    	    coap_transmit_packet (&coap_tx_packet);     
		  }
		}
	  }
	  if (!lwm2m_client_connect)
	  {
		  lwm2m_client_state = LWM2M_CLIENT_IDLE;
	  }
	  break;
    }
  }
}

int lwm2m_connect ()
{
	lwm2m_client_connect = 1;
	return lwm2m_client_connect;
}
int lwm2m_disconnect ()
{
  lwm2m_client_connect = 0;
  return lwm2m_client_connect; 
}
#endif
