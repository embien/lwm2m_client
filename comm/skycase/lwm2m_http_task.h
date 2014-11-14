/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef LWM2M_HTTP_TASK_H
#define LWM2M_HTTP_TASK_H

#define SC_HTTP_TCP_CONN_STATE_DISCONNECTED   0
#define SC_HTTP_TCP_CONN_STATE_CONNECTING     1
#define SC_HTTP_TCP_CONN_STATE_CONNECTED      2
#define SC_HTTP_TCP_CONN_STATE_CONNECT_ERR    3


#define SC_HTTP_COMM_STATE_IDLE               0  /*!< TCP state process idle  */
#define SC_HTTP_COMM_STATE_WAIT_FOR_CONN      1  /*!< TCP state process initialise socket*/
#define SC_HTTP_COMM_STATE_SEND_PACKET        2  /*!< TCP state process initialise socket*/
#define SC_HTTP_COMM_STATE_WAIT_FOR_RESP      3  /*!< TCP state process wait for command*/
#define SC_HTTP_COMM_STATE_PROCESS_RESPONSE		4
#define SC_HTTP_COMM_STATE_ERROR			        5

/*! Declaration structure data member for TCP communication state machine */
typedef struct __sc_lwm2m_http_comm_task
{
  INT8U u8_state;
  INT32U resp_time_out;     
  int tx_len;
  int rx_len;
  unsigned char u8_buffer [SC_CLIENT_RX_BUFFER_SIZE];
  
  SC_HTTP_RESPONSE http_resp;
} SC_LWM2M_HTTP_COMM_TASK;


extern int sc_http_init ();
extern int sc_http_tcp_connect ();
extern int sc_http_tcp_update_conn_state ();
extern int sc_http_tcp_conn_state ();
extern int sc_http_tcp_send_data (INT8U* ptr_request_buf, int num_bytes);
extern int sc_http_tcp_recv_data (INT8U* ptr_rx_buf, int max_rx_len);
extern int sc_http_tcp_disconnect ();

int init_lwm2m_http_client ();
int lwm2m_http_client_task ();
#endif
