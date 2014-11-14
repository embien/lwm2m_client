/*! \file 
  \brief      Module for Transmitting and receiving HTTP messages over TCP and handling the HTTP message 
 
  Contains the logic for TCP communcations,calling the function according to the HTTP request messages
*/

#include <lwm2m_client.h>
#if SASP

#pragma comment(lib,"ws2_32.lib")  /*!< Providing additional information to the compiler */
int sc_init_tcp_socket ();  
int sc_send_data (INT8U* ptr_request_buf);
int sc_process_received_http_response (INT8U*,int);
int lwm2m_get_obj_inst_list_for_reg_web_server (INT8U *ptr_data, int object_id, INT16U u16_instance, int request_level);
int init_tcp_comm ();
int sc_validate_received_http_packet (INT8U* ptr_resp_buf, int num_bytes);
int sc_deinit ();
int sc_queue_recv_data (INT8U *, int);
int process_wait_for_cmd ();

/*Creating a structure variable TCP communication process */
TCP_COMM_SM tcp_comm_sm;

/*! Create a socket for receive bytes from skycase server  */ 
SOCKET socket_server;

/*! Create a socket to set non blocking receiving mode */ 
SOCKET socket_recv;

/*! Create a file descriptor for fd_set */
fd_set socket_set;

/*! Create a file descriptor for fd_set */
fd_set wset;

/*! Create a file descriptor for fd_set */
fd_set rset;

/*! Create a file descriptor for fd_set */
fd_set ex_set;

/*! structure variable for timeval */ 
struct timeval timer;

/*! \fn        int init_tcp_comm ()
    \brief     Initialise  the uri path  
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int init_tcp_comm ()
{
  strcpy ((char*)tcp_comm_sm.u8_uri, "/api");
  return 0;
}

/*! \fn        int sc_get_avail_buf_size (int write_index, int read_index)
    \brief     Get available buffer size to receive data
    \param[in] write_index Index of the last received bytes 
    \param[in] read_index  Index of the maximum content length
    \return    int  Zero on success or error code on failure           
*/
int sc_get_avail_buf_size (int write_index, int read_index)
{
	int avail_size = 0;
	if (read_index < write_index)
	{
      avail_size = (RS_QUEUE_BUFFER_SIZE - write_index) + read_index;
	}
	else if (write_index < read_index)
	{
     avail_size = read_index - write_index;
	}
	else 
	{
	  return RS_QUEUE_BUFFER_SIZE;
	}
	return avail_size;
}

/*! \fn        int init_tcp_client ()
    \brief     Initialise uri path and start TCP communication state process as idle   
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int init_tcp_client ()
{
  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_IDLE;
  strcpy (tcp_comm_sm.u8_uri, "/api");
  return 0;
}

/*! \fn        int lwm2m_tcp_client ()
    \brief     TCP communication state machine process   
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int lwm2m_tcp_client ()
{
  int ret_val = 0, error = 0, recv_resp = 0, recv_bytes, off_set = 0, num_bytes_to_validate = 0;
  int num_bytes = 0, index = 0, read_index = 0, val = 0, avail_size = 0, len = 0; 
  int rc, conn_closed = 0;
  fd_set read_fd; 
  struct timeval timeout;
  switch (tcp_comm_sm.tcp_comm_state)
  {
    case SC_TCP_COMM_STATE_IDLE:
	{
		      ret_val = sc_init_tcp_socket ();
      process_wait_for_cmd ();
      //tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  break;
	}
	case SC_TCP_COMM_STATE_INIT_SOCKET:
	{
#if SC_ENABLE_DEBUG_PRINTS 
      printf ("STATE:SC_TCP_COMM_STATE_INIT \r\n");
#endif 

	  if (ret_val == 1)
	  {
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_PREP_PACKET;
	  }
	  else
	  {
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_IDLE;
	  }
	  break;
	}
	case SC_TCP_COMM_STATE_RECV_RESP:
    {
      timeout.tv_sec = 0;
      timeout.tv_usec = 10000;
	  FD_ZERO(&read_fd);
	  FD_SET(socket_server, &read_fd);
	  rc = select(socket_server + 1, &read_fd, NULL, NULL, &timeout);
	  if((rc == 1) && (FD_ISSET(socket_server, &read_fd)))
	  {
#if SC_ENABLE_DEBUG_PRINTS
	    printf ("read available \r\n");
#endif
      }
	  else 
	  {
#if SC_ENABLE_DEBUG_PRINTS
	    printf ("read not available \r\n");
#endif        
		if (GetCurrentTime() >= (tcp_comm_sm.resp_time_out + SC_RESP_READ_TIMEOUT_MSEC))
		{
          tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;
		}
		break;
	  }
      recv_bytes = recv (socket_server, (char*)tcp_comm_sm.u8_client_rx_buffer, RS_CLIENT_RX_BUFER_SIZE, 0);//0
      if (recv_bytes <= 0)  
	  {
        if (recv_bytes == 0)
		{
	      printf ("Conn closed by server \r\n");
		  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;
		}
		else
		{
		  printf ("Socket error \r\n");
		  error = WSAGetLastError ();
		  printf ("ETDBG: Failed to recv client id. Winsock error code %d \r\n", error);
          tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;
		  break;
	    }
	  }
	  else
	  {
        tcp_comm_sm.u16_num_bytes_recv = recv_bytes;
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_QUEUE_RECV_DATA;
	  }
	  break;
    }
    case SC_TCP_COMM_STATE_QUEUE_RECV_DATA:
	{
#if SC_ENABLE_DEBUG_PRINTS 
      printf ("STATE:SC_TCP_COMM_STATE_QUEUE_RECV_DATA \r\n");
#endif
      printf ("Receving =%s\r\n", tcp_comm_sm.u8_client_rx_buffer);
	  avail_size = sc_get_avail_buf_size (tcp_comm_sm.write_index, tcp_comm_sm.read_index);
	  if (avail_size >= tcp_comm_sm.u16_num_bytes_recv)
	  {
#if SC_ENABLE_DEBUG_PRINTS
        printf ("No overwrite of data \r\n");
#endif 
	  }
	  else
	  {
#if SC_ENABLE_DEBUG_PRINTS
        printf (" overwrite of data \r\n");
#endif 
	  }
      sc_queue_recv_data (tcp_comm_sm.u8_client_rx_buffer, tcp_comm_sm.u16_num_bytes_recv);
	  tcp_comm_sm.u16_num_bytes_recv = 0;
	  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_PROCESS_RESP;
      break;
	}
    case SC_TCP_COMM_STATE_PROCESS_RESP:
	{
#if SC_ENABLE_DEBUG_PRINTS
      printf ("STATE:SC_TCP_COMM_STATE_PROCESS_RESP \r\n");
#endif 
	  if (tcp_comm_sm.read_index < tcp_comm_sm.write_index)
	  {
        num_bytes_to_validate = tcp_comm_sm.write_index - tcp_comm_sm.read_index;
		memcpy (tcp_comm_sm.u8_resp_buf, tcp_comm_sm.u8_queue_buffer + tcp_comm_sm.read_index, num_bytes_to_validate);
		tcp_comm_sm.u8_resp_buf [num_bytes_to_validate] = '\0';
	  }
      else
	  {
        num_bytes_to_validate = RS_QUEUE_BUFFER_SIZE - tcp_comm_sm.read_index;
        memcpy (tcp_comm_sm.u8_resp_buf, tcp_comm_sm.u8_queue_buffer + tcp_comm_sm.read_index, num_bytes_to_validate);
		off_set = num_bytes_to_validate;
        num_bytes_to_validate += tcp_comm_sm.write_index;
		memcpy (tcp_comm_sm.u8_resp_buf + off_set, tcp_comm_sm.u8_queue_buffer, tcp_comm_sm.write_index);//num_bytes_to_validate - tcp_comm_sm.write_index
		tcp_comm_sm.u8_resp_buf [num_bytes_to_validate] = '\0';
	  }
	  if (tcp_comm_sm.u8_resp_buf [0] != 'H')
	  { 
        printf ("ERROR IN PROCESS \r\n");
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;             //for testing 
	    break;
	  }
	  ret_val = sc_validate_received_http_packet (tcp_comm_sm.u8_resp_buf, num_bytes_to_validate); //tcp_comm_sm.u8_queue_buffer + tcp_comm_sm.read_index
	  if (ret_val > 0)
	  {
	    if (sc_process_received_http_response (tcp_comm_sm.u8_resp_buf, ret_val))
		{
#if SC_ENABLE_DEBUG_PRINTS
          printf ("Received Request Processing Success \r\n");
#endif 
		  read_index = tcp_comm_sm.read_index;
		  if ((read_index + ret_val) > RS_QUEUE_BUFFER_SIZE)
		  {
            val = RS_QUEUE_BUFFER_SIZE - read_index;
            val = ret_val - val;
		    tcp_comm_sm.read_index = val;
		  }
		  else
		  {
            tcp_comm_sm.read_index += ret_val;
		  }
          if ((num_bytes_to_validate - ret_val) > SC_HTTP_HEADER_MIN_LEN)
		  {
		    tcp_comm_sm.u8_process_pending = 1;
		  }
		  else
		  {
            tcp_comm_sm.u8_process_pending = 0;
		  }
	      if (tcp_comm_sm.u8_process_pending)
            tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_PROCESS_RESP;
		  else
		  {
            tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_RECV_RESP;
			tcp_comm_sm.resp_time_out = GetCurrentTime();
		  }
		}
	    else 
	    { 
          printf ("Received Request Processing Failed due to Invalid Response \r\n");
		  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_RECV_RESP;
	    }
	  }
	  else
	  {
	    if (ret_val < 0)
		{
           printf ("HTTP ERROR \r\n");
		   tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;  
		}
		else
	    {
          printf ("Full Packet Not Received \r\n");
          tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_RECV_RESP;
		  tcp_comm_sm.u8_process_pending = 0;
	     }
	  }
	  memset (tcp_comm_sm.u8_resp_buf, 0, SC_RESP_BUF_SIZE);
      memset (tcp_comm_sm.u8_client_rx_buffer, 0, SC_RESP_BUF_SIZE);
	  break;
	}
	case SC_TCP_COMM_STATE_PREP_PACKET:
	{
#if SC_ENABLE_DEBUG_PRINTS
      printf ("STATE:SC_TCP_COMM_STATE_PREP_PACKET \r\n");
#endif  
	  sc_prep_request_packet (tcp_comm_sm.u8_request_buf, tcp_comm_sm.u8_http_method, tcp_comm_sm.u8_connection, tcp_comm_sm.tcp_comm_sub_state, SC_COMM_CONTENT_TYPE_JSON);
      printf ("Request URL = %s\r\n", tcp_comm_sm.u8_request_buf);
	  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_SEND_DATA;  
	  u8_last_request = -1;
	  break;
    }
    case SC_TCP_COMM_STATE_SEND_DATA:
	{
#if SC_ENABLE_DEBUG_PRINTS
      printf ("STATE:SC_TCP_COMM_STATE_SEND_DATA \r\n");
#endif 
      ret_val = sc_send_data (tcp_comm_sm.u8_request_buf);
	  if (ret_val < 0)
	  {
	    if (++ tcp_comm_sm.retry_count >= DATA_SEND_RETRY_COUNT)
		  {
	      printf ("data send failed try again \r\n");
		    tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CLOSE;  
		    closesocket(socket_server);
		    tcp_comm_sm.retry_count = 0;
		    u8_last_request = -2;
	    }
	  }
	  else
	  {
        tcp_comm_sm.retry_count = 0;
	    tcp_comm_sm.resp_time_out = GetCurrentTime();
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_CHECK;
		u8_last_request = -3;
	  }
	  break;
    }
	case SC_TCP_COMM_STATE_CHECK:
	{
#if SC_ENABLE_DEBUG_PRINTS
      printf ("STATE:SC_TCP_COMM_STATE_CHECK \r\n");
#endif 
	  if (tcp_comm_sm.u8_process_pending)
	  {
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_PROCESS_RESP;
		u8_last_request = -4;
	  }
	  else
	  {
        tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_RECV_RESP;
		u8_last_request = 0;
	  }
      break;
	}
	case SC_TCP_COMM_STATE_CLOSE:
	{
#if SC_ENABLE_DEBUG_PRINTS
      printf ("STATE:SC_TCP_COMM_STATE_CLOSE \r\n");
#endif
      sc_deinit ();
	  closesocket(socket_server);
	  tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_IDLE;
	  printf ("press 'h' for help\r\n");
      break;
	}
 }
  return 0;
}

/*! \fn       int sc_deinit ()
    \brief    destroy the value of the variable after compeletion of every transmission 
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int sc_deinit ()
{
  tcp_comm_sm.read_index = 0;
  tcp_comm_sm.write_index = 0;
  tcp_comm_sm.u8_process_pending = 0;
  memset (tcp_comm_sm.u8_resp_buf, 0, SC_RESP_BUF_SIZE);
  memset (tcp_comm_sm.u8_client_rx_buffer, 0, RS_CLIENT_RX_BUFER_SIZE);
  memset (tcp_comm_sm.u8_queue_buffer, 0, RS_QUEUE_BUFFER_SIZE);
  memset (tcp_comm_sm.u8_request_buf, 0, SC_REQ_BUF_SIZE);
  console_app.cmd_mode = 1;
  return 0;
}

/*! \fn       int process_wait_for_cmd ()
    \brief    Wait for the user command when TCP communication state process is in idle state 
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int process_wait_for_cmd ()
{
	INT8U u8_cmd  = 0;
    u8_cmd = get_command ();
	if (u8_cmd == SC_CMD_DEVICE_IDLE)
	{
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_IDLE;
	}
	if(u8_cmd == SC_CMD_DEVICE_LIST)
	{
      tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_GET;
      tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DEVICE_LIST;
    }
	else if (u8_cmd == SC_CMD_DEVICE_REGISTER)
	{
      tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_POST;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DEVICE_REGISTER;
	}
	else if (u8_cmd == SC_CMD_DEVICE_UNREGISTER)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_DELETE;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DEVICE_UNREGISTER;
	}
	else if (u8_cmd == SC_CMD_SEND_DATA)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_POST;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_SEND_DATA;
	}
	else if (u8_cmd == SC_CMD_READING_PENDING_REQ)
	{
      tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_GET;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_READING_PENDING_REQ;
	}
	else if (u8_cmd == SC_CMD_DELETE_PENDING_REQ)
	{
      tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_POST;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DELETE_PENDING_REQ;
	}
	else if (u8_cmd == SC_CMD_LISTING_DATA)
	{
      tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_GET;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_LISTING_DATA;
	}
	else if (u8_cmd == SC_CMD_DATA_DELETE)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_DELETE;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DATA_DELETE;
	}
	else if (u8_cmd == SC_CMD_READING_CREATED_EVENTS)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_GET;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_READING_CREATED_EVENTS;
	}
	else if (u8_cmd == SC_CMD_READING_PENDING_EVENTS)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_GET;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_READING_PENDING_EVENTS;
	}
	else if (u8_cmd == SC_CMD_DELETE_PENDING_EVENTS)
	{
	  tcp_comm_sm.u8_http_method = SC_HTTP_REQ_METHOD_PUT;
	  tcp_comm_sm.u8_connection = 1;
      tcp_comm_sm.tcp_comm_state = SC_TCP_COMM_STATE_INIT_SOCKET;
	  tcp_comm_sm.tcp_comm_sub_state = SC_CMD_DELETE_PENDING_EVENTS;
	}

	return 0;
}

/*! \fn       int sc_queue_recv_data (INT8U *ptr_rx_buf, int num_bytes)
    \brief    Verify the receive data and add into the circular buffer 
    \param[in] ptr_rx_buf Data to be add into circular buffer 
    \param[in] num_bytes  Number of bytes in ptr_rx_buf
    \return    int  Zero on success or error code on failure           
*/
int sc_queue_recv_data (INT8U *ptr_rx_buf, int num_bytes)
{
   int  next_write_index = 0;
   int  num_bytes_written = 0;

   while (num_bytes_written < num_bytes)
   {
     next_write_index = tcp_comm_sm.write_index + 1;      
     if (next_write_index >= RS_QUEUE_BUFFER_SIZE)
     {
       printf ("Queue Buffer overflow \r\n");
       next_write_index = 0; 
     }
     if (next_write_index == tcp_comm_sm.write_index)
     {
       return 0;
     }
     else
     {
       tcp_comm_sm.u8_queue_buffer [tcp_comm_sm.write_index] = (INT8U) *ptr_rx_buf;
		   ptr_rx_buf ++; 
		   tcp_comm_sm.write_index = next_write_index;
       num_bytes_written ++;
	   }
   }
   return num_bytes_written;
}

/*! \fn       int sc_initialize_tcp_socket ()
    \brief    Configure a setting and  create a socket for TCP communication 
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int sc_initialize_tcp_socket ()
{
	WSADATA wsa;
    struct sockaddr_in server;
	unsigned long mode = 1;
	
	
    
	int ret_val = 0, error = 0, err;
	int len= 0;
	int ret = 0;
#if SC_ENABLE_DEBUG_PRINTS 
	printf("\nInitialising Winsock...");
#endif 

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return -1;
    }
#if SC_ENABLE_DEBUG_PRINTS      
    printf("Initialised.\n");
#endif      
    //Create a socket
    if((socket_server = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
		return -2;
    }
 #if SC_ENABLE_DEBUG_PRINTS
    printf("Socket created.\r\n");
 #endif  
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE    
    server.sin_addr.s_addr = inet_addr(SC_SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SC_SERVER_PORT);
#endif 
#if SC_BLOCKING_MODE
    ret_val = connect(socket_server, (struct sockaddr *)&server , sizeof(server));
    if (ret_val < 0)
    {
      printf("connect error \r\n");
      return -3;
    }
	else
      return 1;
#endif 
#if SC_NON_BLOCKING_CONNECT

    // Set Non-blocking Mode
//connect:
	socket_recv = socket_server;
	ioctlsocket(socket_recv, FIONBIO, &mode);//FIONBIO //FIONREAD
	ret_val = connect(socket_recv, (struct sockaddr *)&server , sizeof(server));
	err = WSAGetLastError(); 
	if (ret_val < 0 && err == WSAEWOULDBLOCK)
	{
     //error, fail somehow, close socket
	 socket_set.fd_array[0] = socket_recv;
     socket_set.fd_count = 1;
     timer.tv_usec = 50;//args->timeout;
     ret = select(0, &rset, &wset, &ex_set, &timer);
	 FD_SET(socket_recv, &wset);
	 FD_SET(socket_recv, &rset); 
	 FD_SET(socket_recv, &ex_set); 

	 if ( FD_ISSET( socket_recv, &rset) || FD_ISSET( socket_recv, &wset ) || FD_ISSET( socket_recv, &ex_set)) 
	 {
       len = sizeof(error);
       if ( getsockopt((SOCKET) socket_recv, (int)SOL_SOCKET, (int)SO_ERROR, (char *)&error, (int *)&len ) < 0 )
	   {
         return -1;
	   }
	   else
	   {
	    //printf ("rset = %d\r\n", rset);
	    //printf ("wset = %d\r\n", wset);
		return 1;
	  }
	 }
	 else 
	 {
       /* error */
       return -2;
     }
	}
	return 1;
#endif 
}

/*! \fn       int sc_send_data (INT8U* ptr_request_buf)
    \brief    Send a HTTP prepared packet to skycase server through TCP  
    \param[in] ptr_rx_buf Data to be send over TCP 
    \return    int  Zero on success or error code on failure           
*/
int sc_send_data (INT8U* ptr_request_buf)
{
    int error = 0, ret_val = 0, num_bytes = 0; 
	num_bytes = strlen((const char*)ptr_request_buf);

	ret_val = send(socket_server , (const char*)ptr_request_buf ,  num_bytes, 0);
    if(ret_val < 0)
    {
      error = WSAGetLastError ();
#if SC_ENABLE_DEBUG_PRINTS
	  printf ("ETDBG: Failed to recv client id. Winsock error code %d \r\n", error);
#endif
      return -1;
    }
    else
    {
     if (ret_val != num_bytes)  
	 {
#if SC_ENABLE_DEBUG_PRINTS
       printf("Full Data not sent successfully \r\n");
#endif
	 }

    printf("Data Send Succesfully \r\n\n");
	printf ("___________________PACKET RECEVING___________________\r\n");

	return 1;
   }
}








#endif
