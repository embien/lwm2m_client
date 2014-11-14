/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef LWM2M_TCP_H
#define LWM2M_TCP_H
#include <lwm2m_client.h>

#define SC_TCP_COMM_STATE_IDLE                     0  /*!< TCP state process idle  */
#define SC_TCP_COMM_STATE_INIT_SOCKET              1  /*!< TCP state process initialise socket*/
#define SC_TCP_COMM_STATE_WAIT_FOR_CMD             2  /*!< TCP state process wait for command*/
#define SC_TCP_COMM_STATE_RECV_RESP                3 /*!< TCP state process receive response */
#define SC_TCP_COMM_STATE_QUEUE_RECV_DATA          4 /*!< TCP state process queue receive data*/
#define SC_TCP_COMM_STATE_PROCESS_RESP             5 /*!< TCP state process response packet*/
#define SC_TCP_COMM_STATE_PREP_PACKET              6 /*!< TCP state process prepare packet*/
#define SC_TCP_COMM_STATE_SEND_DATA                7 /*!< TCP state process send data */
#define SC_TCP_COMM_STATE_CHECK                    8 /*!< TCP state process check response packet*/                                    
#define SC_TCP_COMM_STATE_CLOSE                    9 /*!< TCP state process close*/                                    

#define SC_HTTP_REQ_METHOD_GET      1 /*!< HTTP request method get */ 
#define SC_HTTP_REQ_METHOD_PUT      2 /*!< HTTP request method put */                                  
#define SC_HTTP_REQ_METHOD_POST     3 /*!< HTTP request method post */ 
#define SC_HTTP_REQ_METHOD_DELETE   4 /*!< HTTP request method delete*/ 

#define SC_HTTP_REQ_METHOD_STR_GET      "GET " /*!< HTTP request verb get*/ 
#define SC_HTTP_REQ_METHOD_STR_PUT      "PUT " /*!< HTTP request verb put*/ 
#define SC_HTTP_REQ_METHOD_STR_POST     "POST " /*!< HTTP request verb  post*/
#define SC_HTTP_REQ_METHOD_STR_DELETE   "DELETE " /*!< HTTP request verb delete*/

#define SC_HTTP_REQ_CONN_KEEP_ALIVE   "   \r\nConnection:keep-alive\r\n" /*!< HTTP  connection keep alive */
#define SC_HTTP_REQ_CONN_CLOSE        "   \r\nConnection:close\r\n"  /*!< HTTP  connection close*/       
#define SC_RESERVED_HEADER_SIZE 800 //700 //600     /*!< HTTP reserved header size */
#define SC_HTTP_HEADER_CONTENT_TYPE_JSON_STR   "application/json"  /*!< HTTP content type JSON */
#define SC_HTTP_HEADER_CONTENT_TYPE_XML_STR    "application/xml"   /*!< HTTP content type xml */ 

#define DATA_SEND_RETRY_COUNT          10        /*!< HTTP data sending failed retry count */

#define SC_STR_REQ_ID            "\"request_id\"" /*!<  Request id string */
#define SC_STR_RQ_ID_LEN         8                /*!< Request id string  length */

#define SC_STR_TYPE            "\"type\""         /*!< Type  string*/
#define SC_STR_TYPE_LEN         4                 /*!< Type  string length*/

#define SC_STR_OBJ_ID            "\"object_id\""  /*!< Object id string */
#define SC_STR_OBJ_ID_LEN         8             /*!< Object id string length */

#define SC_STR_INST_ID            "\"instance_id\"" /*!< Instance  id string */
#define SC_STR_INST_ID_LEN         9                /*!< Instance id string length */

#define SC_STR_RES_ID             "\"resource_id\"" /*!< Resource id string */
#define SC_STR_RES_ID_LEN         13                /*!< Resource id string  length */

#define SC_STR_VALUE             "\"value\""        /*!< Value string */
#define SC_STR_VALUE_LEN         7                  /*!< Value string length */

#define SC_STR_STATUS             "\"status\""    /*!< Status  string */
#define SC_STR_STATUS_LEN         8               /*!< Status string length */

#define SC_STR_PENDING             "\"pending\""  /*!< Pending string */
#define SC_STR_PENDING_LEN          9             /*!< Pending string length */                 

#define SC_STR_MESSAGE             "\"message\""  /*!< Message string */
#define SC_STR_MESSAGE_LEN          9             /*!< Message string length*/

#define SC_STR_MESSAGE_SUCCESS       "\"success\"" /*!< Success string */
#define SC_STR_SUCCESS_LEN          9              /*!< Success string length */ 

#define SC_STR_MESSAGE_FAILURE      "\"failure\""  /*!< Faliure string */
#define SC_STR_FAILURE_LEN          9              /*!< Failure string lenght*/     

#define SC_STR_DEVICE_DESC           "\"device_desc\"" /*!< Device description string */
#define SC_STR_DEVICE_DESC_LEN          13             /*!< Device description string length */ 

#define SC_STR_USER_DESC           "\"user_desc\""   /*!< User description string */
#define SC_STR_USER_DESC_LEN          11             /*!< User description string length */ 

#define SC_STR_REGISTERED           "\"registered\"" /*!< Registered  string */
#define SC_STR_REGISTERED_LEN          12            /*!< Registered string length */   

#define SC_STR_DEVICES           "\"devices\""      /*!< Device  string */
#define SC_STR_DEVICES_LEN          9               /*!< Device  string length*/

#define SC_STR_EVENT_LIST     "\"event_list\""  /*!< Event list string */
#define SC_STR_EVENT_LIST_LEN  11               /*!< Event list string length*/  

#define SC_STR_EVENT_ID      "\"event_id\""    /*!< Event id  string */
#define SC_STR_EVENT_ID_LEN  10                /*!< Event id string length */ 

#define SC_STRING_TYPE     "\"type\""           /*!< Type string */  
#define SC_STRING_TYPE_LEN  6                   /*!< Type string length*/

#define SC_STR_ENABLED    "\"enabled\""        /*!< Enabled  string */
#define SC_STR_ENABLED_LEN  9                   /*!< Enabled string length */

#define SC_PAR_STRING_PENDING      "\"pending\""  /*!< Pending string */
#define SC_PAR_STRING_PENDING_LEN  9              /*!< Pending string length */

#define SC_STR_SOURCE             "\"source\""    /*!< Source string */
#define SC_STR_SOURCE_LEN         8               /*!< Source string length*/

#define SC_STR_PARAMETER1   "\"parameter1\""        /*!< Parameter1 string */
#define SC_STR_PARAMETER1_LEN  12                   /*!< Parameter1 string length */

#define SC_STR_PARAMETER2   "\"parameter2\""        /*!< Parameter2 string */       
#define SC_STR_PARAMETER2_LEN  12                   /*!< Parameter2 string length */

#define SC_STRING_STATUS   "\"status\""           /*!< Status string */
#define SC_STRING_STATUS_LEN  8                   /*!< Status string length */

#define SC_STRING_MESSAGE   "\"message\""         /*!< Message string */
#define SC_STRING_MESSAGE_LEN  9                  /*!< Message string length*/

#define SC_STRING_EVENT_COUNT      "\"event_count\"" /*!< Event count string */
#define SC_STRING_EVENT_COUNT_LEN  13               /*!< Event count string length*/

#define SC_STR_CMD_ACTION            "\"action\"" /*!< Command action string */
#define SC_STR_CMD_ACTION_LEN        8            /*!< Command action string length */

#define SC_STR_CMD_DATA_WRITE        "\"data_write\"" /*!< Command data write string */
#define SC_STR_CMD_DATA_WRITE_LEN    12               /*!< Command data write string length */  

#define SC_STR_CMD_DATA_READ        "\"data_read\""   /*!< Command data read string */
#define SC_STR_CMD_DATA_READ_LEN    11                /*!< Command data read string length*/  

#define SC_STR_CMD_REQ_READ          "\"requests_read\"" /*!< Command request read string */
#define SC_STR_CMD_REQ_READ_LEN      14                 /*!< Command request read string length*/

#define SC_STR_CMD_REQ_DONE          "\"request_done\"" /*!< Command request done string */
#define SC_STR_CMD_REQ_DONE_LEN      14                 /*!< Command request done string length*/

#define SC_STR_CMD_DEV_CREATION      "\"device_creation\"" /*!< Command device creation string */
#define SC_STR_CMD_DEV_CREATION_LEN   17                   /*!< Command device creation string length */ 

#define SC_STR_CMD_DEV_DELETION      "\"device_deletion\"" /*!< Command device deletion string */
#define SC_STR_CMD_DEV_DELETION_LEN   17                   /*!< Command device deletion string length*/   

#define SC_STR_CMD_DEV_LIST          "\"device_list\""  /*!< Command device list  string */ 
#define SC_STR_CMD_DEV_LIST_LEN      13                 /*!< Command device list string length*/

#define SC_STR_CMD_DATA_DELETE         "\"data_delete\"" /*!< Command data deletion string */   
#define SC_STR_CMD_DATA_DELETE_LEN      13              /*!< Command data  deletion  string length */ 

#define SC_STR_CMD_ALL_EVENTS        "\"all_events\""  /*!< Command all events string */ 
#define SC_STR_CMD_ALL_EVENTS_LEN      12              /*!< Command all events string  length */

#define SC_STR_CMD_PENDING_EVENTS        "\"pending_events\"" /*!< Command pending  events string */
#define SC_STR_CMD_PENDING_EVENTS_LEN      16                 /*!< Command pending  events string length */

#define SC_STR_CMD_EVENTS_DONE        "\"events_done\""       /*!< Command events done string */                                
#define SC_STR_CMD_EVENTS_DONE_LEN     13                     /*!< Command events done string length*/     

#define SC_RESP_READ_TIMEOUT_MSEC 60000        /*!< Waiting time response read */ 



#define SC_REQ_BUF_SIZE         2000      /*!<  HTTP request buffer size */  
#define SC_RESP_BUF_SIZE        RS_QUEUE_BUFFER_SIZE        /* Queue buffer size assigned  to response buffer size */
#define SC_MAX_NUM_REQUEST_PENDING 30     /*!< Maximum request pending */
#define SC_MAX_NUM_EVENT_PENDING   30     /*!< Maximum event pending */
#define SC_NON_BLOCKING_CONNECT    1      /*!< To set TCP communication nonblocking mode */
#define SC_BLOCKING_MODE           0      /*!< To set TCP communication blocking mode */


#define SC_HTTP_STR_HEADER_STATUS          "HTTP/1.1 200 OK" /*!< HTTP response status */
#define SC_HTTP_STR_HEADER_STATUS_LEN      15               /*!< HTTP response status length */
#define SC_HTTP_HEADER_MIN_LEN              100            /*!< HTTP header minimum length */
#define  SC_STR_CONTENT_LEN    "Content-Length"           /*!< Content length string */
#define  SC_OPEN_BRACE         0x7B                       /*!<  ASCII value for open brace*/ 
#define  SC_CLOSED_BRACE       0x7D                       /*!<  ASCII value for close brace*/                          
#define  SC_LEFT_CHEVRON       0x3C                       /*!<  ASCII value for left chevron*/
#define  SC_RIGHT_CHEVRON      0x3E                       /*!<  ASCII value for right chevron */

#define SC_STR_DEVICE     "devices" /*!< Device string */
#define SC_STR_DATA       "data"    /*!< Data  string */
#define SC_STR_REQUEST    "requests" /*!< Request string */
#define SC_STR_DELETE     "delete"  /*!< Delete string */
#define SC_STR_EVENTS     "events"  /*!< Event string */
#define SC_STRING_PENDING     "pending"  /*!< Pending string */
#define HEXA_TO_INT(Hexa) (Hexa >= 'a') ? Hexa - 'a' + 10 : Hexa - '0' /*!< Conversion of hexadecimal to integer */

/*! Declaration structure data member for TCP communication state machine */
typedef struct __tcp_comm_sm
{
  unsigned char u8_cmd;
  unsigned char u8_retry_count;
  unsigned char u8_http_method;
  unsigned char u8_connection;
  unsigned char u8_process_pending;
  unsigned char u8_reg_success;
  unsigned char request_level;
  int status_value;
  int sub_status_value;
  int tcp_comm_state;
  int tcp_comm_sub_state;
  int obj_id;
  int inst_id;
  int res_id;
  int inst_count;
  int write_index;
  int read_index;
  int http_err_packet;
  int retry_count;
  int retries;
  int last_state;
  int app_id;
  INT16U u16_num_bytes_recv;
  unsigned char u8_uri [50];
  unsigned char u8_client_rx_buffer [RS_CLIENT_RX_BUFER_SIZE]; 
  unsigned char u8_resp_buf [SC_RESP_BUF_SIZE];         
  unsigned char u8_request_buf [SC_REQ_BUF_SIZE];       
  unsigned char u8_queue_buffer [RS_QUEUE_BUFFER_SIZE];    
  unsigned char u8_str_command_buf [30];
  INT32U resp_time_out;
} TCP_COMM_SM;

/*! Extern the TCP communication structure variable */
extern TCP_COMM_SM tcp_comm_sm;

/*! Declaration of structure data member for HTTP process */
typedef struct __sc_http_process
{
  int pending_request;
  int num_obj;
  int num_request_recv;
  INT8U u8_pending;
  INT8U u8_status_value [10];
  INT8U u8_type [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_req_id [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_res_id [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_obj_id [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_inst_id [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_value [SC_MAX_NUM_REQUEST_PENDING];
  INT16U u16_app_id;
  INT16U u16_num_pending_events;
  INT16U u16_event_id [SC_MAX_NUM_EVENT_PENDING];
  INT16U u16_event_count [SC_MAX_NUM_EVENT_PENDING];
}SC_HTTP_PROCESS;


#define XOR_APP_REGISTER_SUCCESS       BIT(0)
#define XOR_APP_DATA_REGISTER_FAILURE  BIT(1)
#define XOR_APP_DATA_WRITE_SUCCESS     BIT(2)
/*! Extern the HTTP process structure varialbe */
extern SC_HTTP_PROCESS sc_http_process;
extern int lwm2m_get_obj_inst_list_for_reg_web_server (INT8U*, int, INT16U);
extern int base64encode(const void*, int, char*, int);
extern int get_command ();
extern  int sc_prep_request_packet (INT8U*, INT8U, INT8U, INT8U, INT8U);
extern SKYCASE_XOR_OPER xor_operation;
extern LWM2M_PROCESS_INFO lwm2m_write_process;
extern int lwm2m_process_update_res_val();
#endif
