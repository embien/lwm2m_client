/*! \file 
  \brief      Module implementing UDP communication
  
   Contains the logic for socket creation, sending and reeiving data through created socket
*/

#include <lwm2m_client.h>
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP

#pragma comment(lib,"ws2_32.lib") 

/*! Declaration of structure data members for socket communication */
typedef struct __udp_info
{
  int sockaddr_in_len;
  int udp_socket;
  struct sockaddr_in si_server_addr;
  INT8U data_buf [4096];
} UDP_INFO;

/*! Create a structure variable for socket communication */
UDP_INFO udp_info;

/*! Create a structure variable for socket implementation */
WSADATA wsa;

/*! \fn        int init_coap_udp_socket ()
    \brief     Configure a setting and create a socket for UDP communication  
    \param[in] None 
    \return    int         Zero on success  or error code on failure
*/
int init_coap_udp_socket ()
{
   INT32U iMode = 1;
  /* Initialise winsock */
#if SC_ENABLE_DEBUG_PRINTS
  printf("\nInitialising Winsock...");
#endif 
  if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
  {
    printf("Failed. Error Code : %d",WSAGetLastError());
    exit(EXIT_FAILURE);
  }
#if SC_ENABLE_DEBUG_PRINTS
  printf("Initialised.\n");
#endif
   /* create socket */
  if ((udp_info.udp_socket = (INT)(socket ((int)AF_INET, (int)SOCK_DGRAM, (int)IPPROTO_UDP))) == SOCKET_ERROR)
  {
    printf("socket() failed with error code : %d" , WSAGetLastError());
    exit(EXIT_FAILURE);
  }     
  /* setup address structure */
  memset((char *) &udp_info.si_server_addr, 0, sizeof (udp_info.si_server_addr));
  udp_info.si_server_addr.sin_family = AF_INET;
#if LWM2M_CLIENT_COMMUNICATION_UDP_COAP  
  udp_info.si_server_addr.sin_port = htons(LWM2M_COAP_UDP_SERVER_PORT);
  udp_info.si_server_addr.sin_addr.S_un.S_addr = inet_addr(LWM2M_COAP_UDP_SERVER_IP);
#endif   
  udp_info.sockaddr_in_len = sizeof (udp_info.si_server_addr);
  ioctlsocket((SOCKET)(udp_info.udp_socket), (long)(FIONBIO), (ULONG *)(&iMode));
  return 0;
}

/*! \fn        int coap_send_to_server (INT8U *ptr_tx_buf, int tx_len) 
    \brief     send data to UDP server  
    \param[in] ptr_tx_buf Transmit data buffer which holds the data
    \param[in] tx_len     Transmit data length 
    \return    int        Zero on success  or error code on failure
*/
int coap_send_to_server (INT8U *ptr_tx_buf, int tx_len)
{
  int send_bytes;
#if SC_ENABLE_DEBUG_PRINTS
  for (index = 0;index < tx_len;index ++)
    {
      printf(" %02x",ptr_tx_buf [index]);
  }
#endif 
  send_bytes = sendto((SOCKET)(udp_info.udp_socket), (const char *)ptr_tx_buf, (int)tx_len, (int)0, \
    ( const struct sockaddr*)&udp_info.si_server_addr, (int)(udp_info.sockaddr_in_len));
  if (send_bytes == SOCKET_ERROR)
  {
    printf ("sendto() failed with error code : %d" , WSAGetLastError());
  }
  return send_bytes;
}

/*! \fn        int coap_recv_from_server (INT8U *ptr_rx_buf, int rx_len) 
    \brief     Receive data from UDP server  
    \param[in] ptr_rx_buf Receive data buffer which holds the data
    \param[in] rx_len     Receive data length from UDP server
    \return    int        Zero on success  or error code on failure
*/
int coap_recv_from_server (INT8U *ptr_rx_buf, int rx_len)
{
  int recv_bytes;
  recv_bytes = recvfrom((SOCKET)(udp_info.udp_socket),(char *)(ptr_rx_buf), (int)rx_len, (int)0, (struct sockaddr *) &udp_info.si_server_addr,(int *)&udp_info.sockaddr_in_len);
  if(recv_bytes == SOCKET_ERROR)
  {
    return 0;
  }
  if (recv_bytes > 0 && recv_bytes !=  (int)0xffffffff)
    return recv_bytes;
  else
    return 0;
}

/*! \fn        INT8U *get_coap_data_buf ()
    \brief     Get data buffer to fill CoAP messages 
    \param[in] None 
    \return    int        Data buffer on success  or error code on failure
*/
INT8U *get_coap_data_buf ()
{
  return udp_info.data_buf;
}
#endif
