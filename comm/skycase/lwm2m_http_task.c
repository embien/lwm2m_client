/*! \file 
  \brief      Module for Transmitting and receiving HTTP messages over TCP and handling the HTTP message 
 
  Contains the logic for TCP communcations,calling the function according to the HTTP request messages
*/

#include <lwm2m_client.h>

SC_LWM2M_HTTP_COMM_TASK sc_lwm2m_http_comm_task;

int init_tcp_client ();

/*! \fn        int init_tcp_client ()
    \brief     Initialise uri path and start TCP communication state process as idle   
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int init_lwm2m_http_client ()
{
  sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_IDLE;
  sc_lwm2m_http_comm_task.http_resp.ptr_resp = sc_lwm2m_http_comm_task.u8_buffer;
  return 0;
}
int lwm2m_http_client_task ()
{
  INT8U u8_cmd;
  int recv_bytes, ret_val;
  switch (sc_lwm2m_http_comm_task.u8_state)
  {
    case SC_HTTP_COMM_STATE_IDLE:
    { 
      u8_cmd = sc_get_next_command ();
      if (u8_cmd != 0)
      {
        sc_http_tcp_connect ();
        sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_WAIT_FOR_CONN;
      }
      break;
    }
    case SC_HTTP_COMM_STATE_WAIT_FOR_CONN:
    { 
      ret_val = sc_http_tcp_conn_state ();
      if ( 0 || ret_val == SC_HTTP_TCP_CONN_STATE_CONNECTED)
      {
        sc_lwm2m_http_comm_task.tx_len = sc_prep_http_request_packet (sc_lwm2m_http_comm_task.u8_buffer, SC_CLIENT_RX_BUFFER_SIZE);
        printf ("Request URL = %s\r\n", sc_lwm2m_http_comm_task.u8_buffer);
        sc_lwm2m_http_comm_task.u8_state =  SC_HTTP_COMM_STATE_SEND_PACKET;
      }
      else if (ret_val == SC_HTTP_TCP_CONN_STATE_CONNECT_ERR)
      {
        sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_ERROR;
      }
      break;
    }
    case SC_HTTP_COMM_STATE_SEND_PACKET:
    {
      if (!sc_http_tcp_send_data (sc_lwm2m_http_comm_task.u8_buffer, sc_lwm2m_http_comm_task.tx_len))
      {
        sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_WAIT_FOR_RESP;  
        sc_lwm2m_http_comm_task.rx_len = 0;
        sc_lwm2m_http_comm_task.http_resp.processed_len = 0;
        sc_lwm2m_http_comm_task.http_resp.u8_process_state = SC_HTTP_RESP_PROCESS_STATE_IN_HEADER;
        
      }
      break;
    }
    case SC_HTTP_COMM_STATE_WAIT_FOR_RESP:
    {
      recv_bytes = sc_http_tcp_recv_data (sc_lwm2m_http_comm_task.u8_buffer + sc_lwm2m_http_comm_task.rx_len, \
                                          SC_CLIENT_RX_BUFFER_SIZE - sc_lwm2m_http_comm_task.rx_len);
      if (recv_bytes > 0)
      {
        sc_lwm2m_http_comm_task.u8_buffer [sc_lwm2m_http_comm_task.rx_len + recv_bytes + 1] = 0; 
		    printf ("%s\r\n",sc_lwm2m_http_comm_task.u8_buffer);
        
		sc_lwm2m_http_comm_task.rx_len += recv_bytes;
        ret_val = sc_http_validate_rx_packet (&sc_lwm2m_http_comm_task.http_resp, sc_lwm2m_http_comm_task.rx_len); 
        if(ret_val == 0)
        {
          sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_PROCESS_RESPONSE;
        }
        else if(ret_val < 0)
        {
          sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_ERROR;
        }
      }
      //printf ("%s\r\n",sc_lwm2m_http_comm_task.u8_buffer);
      break;
    }
    case SC_HTTP_COMM_STATE_PROCESS_RESPONSE:
    {
      ret_val = sc_process_http_resp_content (&sc_lwm2m_http_comm_task.http_resp);
      if (!ret_val)
      {
        sc_set_last_cmd_result (0);
        sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_IDLE;
      }
      else
      {
		sc_set_last_cmd_result (1);
        sc_lwm2m_http_comm_task.u8_state = SC_HTTP_COMM_STATE_ERROR;
      }
      sc_http_tcp_disconnect ();
      break;
    }
    case SC_HTTP_COMM_STATE_ERROR:
    {
      sc_lwm2m_http_comm_task.u8_state  = SC_HTTP_COMM_STATE_IDLE;
      break;
    }
  }
  return 0;
}