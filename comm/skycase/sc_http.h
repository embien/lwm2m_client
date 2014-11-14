/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef SC_HTTP_H
#define SC_HTTP_H

#define SC_HTTP_PREP_PKT_TYPE_VERB_MASK		(0x3)
#define SC_HTTP_PREP_PKT_TYPE_VERB_GET		(0 << 0)
#define SC_HTTP_PREP_PKT_TYPE_VERB_POST		(1 << 0)
#define SC_HTTP_PREP_PKT_TYPE_VERB_DELETE	(2 << 0)
#define SC_HTTP_PREP_PKT_TYPE_VERB_PUT		(3 << 0)

#define SC_HTTP_PREP_PKT_TYPE_KEEP_ALIVE  (1 << 2)

#define SC_HTTP_REQ_METHOD_STR_GET      "GET " /*!< HTTP request verb get*/ 
#define SC_HTTP_REQ_METHOD_STR_PUT      "PUT " /*!< HTTP request verb put*/ 
#define SC_HTTP_REQ_METHOD_STR_POST     "POST " /*!< HTTP request verb  post*/
#define SC_HTTP_REQ_METHOD_STR_DELETE   "DELETE " /*!< HTTP request verb delete*/

#define SC_HTTP_HEADER_CONTENT_TYPE_JSON_STR   "application/json"  /*!< HTTP content type JSON */
#define SC_HTTP_HEADER_CONTENT_TYPE_XML_STR    "application/xml"   /*!< HTTP content type xml */ 

#define SC_HTTP_REQ_CONN_KEEP_ALIVE   "   \r\nConnection:keep-alive\r\n" /*!< HTTP  connection keep alive */
#define SC_HTTP_REQ_CONN_CLOSE        "   \r\nConnection:close\r\n"  /*!< HTTP  connection close*/       


#define SC_HTTP_RESP_FIELD_EMPTY                    "\r\n"
#define SC_HTTP_RESP_FIELD_VERSION                  "http/1.1 "
#define SC_HTTP_RESP_FIELD_SERVER                   "server"
#define SC_HTTP_RESP_FIELD_DATE                     "date"
#define SC_HTTP_RESP_FIELD_CONTENT_TYPE             "content-type"
#define SC_HTTP_RESP_FIELD_CONNECTION               "connection"
#define SC_HTTP_RESP_FIELD_CONTENT_LENGTH           "content-length"
#define SC_HTTP_RESP_FIELD_CONNECTION_CLOSE         "close"
#define SC_HTTP_RESP_FIELD_CONNECTION_KEEP_ALIVE    "keep-alive"
#define SC_HTTP_RESP_FIELD_CONTENT_TYPE_JSON        "application/json"   

#define SC_HTTP_RESP_CONNECTION_CLOSE               1   
#define SC_HTTP_RESP_CONNECTION_KEEP_ALIVE          2

#define SC_HTTP_RESP_CONTENT_TYPE_JSON              1
#define SC_HTTP_RESP_CONTENT_TYPE_XML               2

#define SC_HTTP_RESP_CONTENT_TYPE_SIZE              36
#define SC_HTTP_RESP_CONNECTION_SIZE                20
#define SC_HTTP_RESP_CONTENT_LENGTH_SIZE            10


#define SC_HTTP_RESP_PROCESS_STATE_IN_HEADER  0
#define SC_HTTP_RESP_PROCESS_STATE_IN_BODY    1
#define SC_HTTP_RESP_PROCESS_STATE_DONE       2


#define SC_HTTP_RESP_SERVER_NAME_SIZE       32
#define SC_HTTP_RESP_DATE_AND_TIME_SIZE     32
#define SC_HTTP_RESP_ENDPOINT_SIZE		      20
#define SC_HTTP_RESP_ACTION_SIZE				    20

typedef struct __sc_http_response
{
  int resp_code; 
  char  server_name [SC_HTTP_RESP_SERVER_NAME_SIZE];
  char  date [SC_HTTP_RESP_DATE_AND_TIME_SIZE];
  char  endpoint [SC_HTTP_RESP_ENDPOINT_SIZE];
  char action [SC_HTTP_RESP_ACTION_SIZE];
  INT8U u8_content_type;
  INT8U u8_char_set;
  INT8U u8_conn_state;

  INT8U *ptr_resp;
  
  void *ptr_pkt_buf;
  int pkt_buf_size;
  
  char *ptr_base_mem [3];
  int arr_type_size [3];
  int depth;

  INT16U u16_content_pos;
  INT16U u16_content_len;
  int processed_len;
  INT8U u8_process_state;

} SC_HTTP_RESPONSE;

int sc_http_validate_rx_packet (SC_HTTP_RESPONSE *ptr_http_resp, int rx_len);

extern int sc_process_http_resp_content (SC_HTTP_RESPONSE *ptr_http_resp);
extern int sc_prepare_packet_reg_client (INT8U* ptr_req_buf);
extern int sc_prepare_packet_data_write (INT8U *ptr_data, SC_PKT_DATA_WRITE_REQ *ptr_update_req);
extern int sc_prepare_packet_del_pending_req (INT8U* ptr_data, SC_PKT_READ_PENDING_REQ_RESP *ptr_del_pending_req);
extern int sc_prepare_packet_clear_pending_events (INT8U* ptr_data, SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_pending_event);
#endif
