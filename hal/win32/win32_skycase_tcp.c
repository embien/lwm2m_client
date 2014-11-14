#include <lwm2m_client.h>
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE

#define SC_ENABLE_NON_BLOCKING_MODE    1      /*!< To set TCP communication nonblocking mode */

#pragma comment(lib,"ws2_32.lib")  /*!< Providing additional information to the compiler */


typedef struct __sc_win32_tcp_info
{
	SOCKET socket;
  INT32U resp_time_out;
  int conn_state;
} SC_WIN32_TCP_INFO;

SC_WIN32_TCP_INFO sc_win32_tcp_info;

int sc_http_init ()
{
  WSADATA wsa;
#if SC_ENABLE_DEBUG_PRINTS 
  printf("\nInitialising Winsock...");
#endif
  if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0)
  {
    printf("Failed. Error Code : %d",WSAGetLastError());
    return -1;
  }
  sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_DISCONNECTED;
  return 0;
}
//SASP tbd reviewed

int sc_http_tcp_conn_state ()
{
  sc_http_tcp_update_conn_state ();
  return sc_win32_tcp_info.conn_state;
}

/*! \fn       int sc_init_tcp_socket ()
    \brief    Configure a setting and  create a socket for TCP communication 
    \param[in] None
    \return    int  Zero on success or error code on failure           
*/
int sc_http_tcp_connect ()
{
  struct sockaddr_in server;
  unsigned long mode = 1;
  int ret_val = 0, error = 0, err;
  
#if SC_ENABLE_DEBUG_PRINTS      
  printf("Initialised.\n");
#endif      
  //Create a socket
  if((sc_win32_tcp_info.socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
  {
    printf("Could not create socket : %d" , WSAGetLastError());
    return -2;
  }
 #if SC_ENABLE_DEBUG_PRINTS
  printf("Socket created.\r\n");
 #endif  
  server.sin_addr.s_addr = inet_addr(SC_SERVER_IP);
  server.sin_family = AF_INET;
  server.sin_port = htons(SC_SERVER_PORT);

#if !SC_ENABLE_NON_BLOCKING_MODE
  ret_val = connect (sc_win32_tcp_info.socket, (struct sockaddr *)&server, sizeof(server));
  if (ret_val < 0)
  {
    printf("connect error \r\n");
    return -3;
  }
  else
  {
    return 0;
  }
#elif SC_ENABLE_NON_BLOCKING_MODE
  // Set Non-blocking Mode
  //connect:
  ioctlsocket (sc_win32_tcp_info.socket, FIONBIO, &mode);
  ret_val = connect (sc_win32_tcp_info.socket, (struct sockaddr *)&server , sizeof(server));
  err = WSAGetLastError(); 
  if ((ret_val < 0) && (err != WSAEWOULDBLOCK))
  {
    sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_CONNECT_ERR;
    return -1;
  }
  sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_CONNECTING;
  sc_win32_tcp_info.resp_time_out = GetCurrentTime();
#endif
  return 0;
}
int sc_http_tcp_update_conn_state ()
{
  int ret_val = 0, error = 0, len;
  fd_set socket_set, wset, ex_set;
  /*! structure variable for timeval */ 
  struct timeval timer;
  //error, fail somehow, close socket
  socket_set.fd_array[0] = sc_win32_tcp_info.socket;
  socket_set.fd_count = 1;
  timer.tv_usec = 50;//args->timeout;
  FD_ZERO (&wset);
  FD_ZERO (&ex_set);
  FD_SET(sc_win32_tcp_info.socket, &wset);
  FD_SET(sc_win32_tcp_info.socket, &ex_set); 
  ret_val = select(0, NULL, &wset, &ex_set, &timer);
  if (FD_ISSET (sc_win32_tcp_info.socket, &wset))
  {
    sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_CONNECTED;
    return 0;
  }
  if (FD_ISSET (sc_win32_tcp_info.socket, &ex_set))
  {
    len = sizeof(error);
    if (getsockopt((SOCKET) sc_win32_tcp_info.socket, (int)SOL_SOCKET, (int)SO_ERROR, (char *)&error, (int *)&len ) >= 0 )
    {
      sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_CONNECT_ERR;
      return 1;
    }
  }
  if (GetCurrentTime() >= (sc_win32_tcp_info.resp_time_out + SC_HTTP_RESP_READ_TIMEOUT_MSEC))
  {
    sc_win32_tcp_info.conn_state = SC_HTTP_TCP_CONN_STATE_CONNECT_ERR;
    sc_http_tcp_disconnect ();
    return -1;
  }
  return -1;
}

/*! \fn       int sc_send_data (INT8U* ptr_request_buf)
    \brief    Send a HTTP prepared packet to skycase server through TCP  
    \param[in] ptr_rx_buf Data to be send over TCP 
    \return    int  Zero on success or error code on failure           
*/
int sc_http_tcp_send_data (INT8U* ptr_request_buf, int num_bytes)
{
  int error = 0, ret_val = 0;
  ret_val = send (sc_win32_tcp_info.socket , (const char*)ptr_request_buf ,  num_bytes, 0);
  if(ret_val < 0)
  {
    error = WSAGetLastError ();
#if SC_ENABLE_DEBUG_PRINTS
    //printf ("ETDBG: Failed to recv client id. Winsock error code %d \r\n", error);
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
    sc_win32_tcp_info.resp_time_out = GetCurrentTime();
    printf("Data Sent Succesfully \r\n\n");
    return 0;
  }
}

int sc_http_tcp_recv_data (INT8U* ptr_rx_buf, int max_rx_len)
{
  fd_set read_fd; 
  int rc, recv_bytes, error; 
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 10000;
  FD_ZERO (&read_fd);
  FD_SET (sc_win32_tcp_info.socket, &read_fd);
  rc = select (sc_win32_tcp_info.socket + 1, &read_fd, NULL, NULL, &timeout);
  if((rc == 1) && (FD_ISSET(sc_win32_tcp_info.socket, &read_fd)))
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
    if (GetCurrentTime() >= (sc_win32_tcp_info.resp_time_out + SC_HTTP_RESP_READ_TIMEOUT_MSEC))
    {
      return -1;
    }
   //break;
  }
  recv_bytes = recv (sc_win32_tcp_info.socket, (char*)ptr_rx_buf, max_rx_len, 0);//0
  if (recv_bytes <= 0)   
  {
    if (recv_bytes == 0)
    {
    printf ("Conn closed by server \r\n");
      return -1;
    }
    else
  {
      //printf ("Socket error \r\n");
    error = WSAGetLastError ();
    //printf ("ETDBG: Failed to recv client id. Winsock error code %d \r\n", error);
     // break;
    return -1;
  }
  }
  return recv_bytes;
}
int sc_http_tcp_disconnect ()
{
 // sc_deinit ();
  closesocket(sc_win32_tcp_info.socket);
  return 0;
}

#endif
