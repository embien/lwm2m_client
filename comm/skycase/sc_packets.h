/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef SC_PACKETS_H
#define SC_PACKETS_H

#define SC_CMD_DEVICE_IDLE              0 /*!< User command number for idle */
#define SC_CMD_DEVICE_REGISTER          1 /*!< User command number device registration  */
#define SC_CMD_DATA_WRITE               2 /*!< User command number data sending */
#define SC_CMD_READ_PENDING_REQUESTS    3 /*!< User command number reading pending request */
#define SC_CMD_DEL_PENDING_REQUESTS     4 /*!< User command number deleting pending request */
#define SC_CMD_READ_DEVICE_LIST         5 /*!< User command number device list */
#define SC_CMD_READ_APPLICATIONS_LIST   6 /*!< User command number device list */
#define SC_CMD_READ_ALL_EVENTS          7 /*!< User command number reading created events */
#define SC_CMD_READ_PENDING_EVENTS      8 /*!< User command number reading created events */
#define SC_CMD_CLEAR_PENDING_EVENTS     9 /*!< User command number reading created events */
#define SC_CMD_DEVICE_UNREGISTER        10 /*!< User command number device registration  */
#define SC_CMD_DATA_READ                11 /*!< User command number data sending */
#define SC_CMD_DATA_DELETE              12 /*!< User command number data sending */

#define SC_COMM_INFO_TMP_BUF_LEN              64
typedef struct __sc_comm_info
{ 
  INT8U u8_cur_cmd;
  INT8U u8_tmp_buf [SC_COMM_INFO_TMP_BUF_LEN];
  int cmd_result;
  void *ptr_cmd_arg;
  /*INT8U u8_request_pending_in_server; 
  INT8U u8_last_command_success;
  SC_PACKET_INFO packet_info;
  SC_HTTP_RESPONSE http_resp;
  */
} SC_COMM_INFO;



#define SC_API_URL_PATH_DEVICE     "/devices" /*!< http url Device string */
#define SC_API_URL_PATH_DATA       "/data"    /*!< http url Data  string */
#define SC_API_URL_PATH_REQUEST    "/requests" /*!< http url Request string */
#define SC_API_URL_PATH_REQUEST_DELETE    "/requests/delete" /*!< http url Request string */
#define SC_API_URL_PATH_APPLICATIONS     "/applications" /*!< http url Device string */
#define SC_API_URL_PATH_EVENTS     "/events" /*!< http url Device string */
#define SC_API_URL_PATH_PENDING_EVENT    "/events/pending" /*!< http url Pending Events string */

typedef struct __sc_enum_int_pair
{ 
  const char *str_name;
  const int value;
} SC_ENUM_INT_PAIR;

#define SC_PKT_INFO_RES_OBJ_ID_MAX_LEN        2
#define SC_PKT_INFO_RES_INST_ID_MAX_LEN       2
#define SC_PKT_INFO_RES_RES_ID_MAX_LEN        2
#define SC_PKT_INFO_RES_STATUS_MAX_LEN        2
#define SC_PKT_INFO_RES_VALUE_MAX_LEN         32

typedef struct __sc_res_info
{ 
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT16U u16_res_id;
  INT16U u16_status;
} SC_RES_INFO;

typedef struct __sc_res_value_info
{ 
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT16U u16_res_id;
  INT16U u16_status;
  INT8U value [SC_PKT_INFO_RES_VALUE_MAX_LEN];
} SC_RES_VALUE_INFO;

typedef struct __sc_array_info
{ 
  int num_arr_items;
} SC_ARRAY_INFO;

#define SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN       32
#define SC_PKT_INFO_ACTION_VAL_MAX_LEN	        1 
#define SC_PKT_INFO_PENDING_REQ_VAL_MAX_LEN	    1    

typedef struct __sc_packet_common_info
{
  INT8U u8_endpoint [SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN];
  INT8U u8_action;
  INT8U u8_pending_request;
} SC_PKT_COMMON_RESP_INFO;



typedef struct __sc_req_info_data_write
{
  SC_ARRAY_INFO arr_info;
  SC_RES_INFO res_info [SC_PKT_DEV_REG_REQ_MAX_NUM_RESOURCES];
} SC_PKT_DATA_WRITE_REQ;


typedef struct __sc_resp_info_dev_reg
{
  SC_PKT_COMMON_RESP_INFO common_info;
  SC_ARRAY_INFO arr_info;
  SC_RES_INFO res_info [SC_PKT_DEV_REG_REQ_MAX_NUM_RESOURCES];
} SC_PKT_DEV_REG_RESP_INFO;

typedef struct __sc_req_info_dev_unreg
{
  INT16U u16_obj_id;
  INT16U u16_inst_id;
} SC_PKT_DEV_UNREG_REQ_INFO;

#define SC_RESP_DEV_UNREG_DEV_PATH_MAX_LEN      32
#define SC_RESP_DEV_UNREG_STATUS_MAX_LEN        2
typedef struct __sc_resp_info_dev_unreg
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT8U device_path [SC_RESP_DEV_UNREG_DEV_PATH_MAX_LEN];
  INT16U u16_status;
} SC_PKT_DEV_UNREG_RESP_INFO;
#define SC_RESP_DEV_INFO_OBJ_ID_MAX_LEN       2
#define SC_RESP_DEV_INFO_INST_ID_MAX_LEN      2
#define SC_RESP_DEV_INFO_DEV_DESC_MAX_LEN     32
#define SC_RESP_DEV_INFO_USER_DES_MAX_LEN     32
#define SC_RESP_DEV_INFO_REG_STATUS_MAX_LEN   2

typedef struct __sc_packet_resp_list_dev
{ 
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT8U  u8_dev_desc  [SC_RESP_DEV_INFO_DEV_DESC_MAX_LEN];
  INT8U  u8_user_desc [SC_RESP_DEV_INFO_USER_DES_MAX_LEN];
  INT16U u16_reg_status;
} SC_PKT_DEV_LIST_INFO;

#define  SC_PKT_INFO_DEV_LIST_NUM_DEV_MAX_LEN   2
#define  SC_PKT_INFO_DEV_LIST_STATUS_MAX_LEN    2


typedef struct __sc_resp_list_devices
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT16U u16_num_devices;
  INT16U u16_status;
  SC_ARRAY_INFO arr_info;
  SC_PKT_DEV_LIST_INFO dev_info [SC_PKT_DEV_LIST_MAX_DEVICES];
} SC_PKT_DEV_LIST_RESP_INFO;


typedef struct __sc_resp_info_data_write
{
  SC_PKT_COMMON_RESP_INFO common_info;
  SC_ARRAY_INFO arr_info;
  SC_RES_INFO res_info [SC_PKT_DATA_WRITE_REQ_MAX_WRITES];
} SC_PKT_DATA_WRITE_RESP;


#define SC_DATA_READ_REQ_TYPE_FOR_ALL       0
#define SC_DATA_READ_REQ_TYPE_FOR_OBJ       1
#define SC_DATA_READ_REQ_TYPE_FOR_INST      2
#define SC_DATA_READ_REQ_TYPE_FOR_RES       3
#define SC_DATA_READ_REQ_TYPE_FOR_TIME      4

typedef struct __sc_req_info_data_read
{
  INT8U u8_type;
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT16U u16_res_id;
  INT32U u32_timestamp;
} SC_PKT_DATA_READ_REQ;

typedef struct __sc_resp_info_data_read
{
  SC_PKT_COMMON_RESP_INFO common_info;
  SC_ARRAY_INFO arr_info;
  SC_RES_VALUE_INFO res_info [SC_PKT_DATA_READ_REQ_MAX_READS];
} SC_PKT_DATA_READ_RESP;

#define SC_DATA_DEL_REQ_TYPE_FOR_ALL       0
#define SC_DATA_DEL_REQ_TYPE_FOR_OBJ       1
#define SC_DATA_DEL_REQ_TYPE_FOR_INST      2
#define SC_DATA_DEL_REQ_TYPE_FOR_RES       3
#define SC_DATA_DEL_REQ_TYPE_FOR_TIME      4

typedef struct __sc_req_info_data_del
{
  INT8U u8_type;
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT16U u16_res_id;
  INT32U u32_timestamp;
} SC_PKT_DATA_DEL_REQ;

#define SC_DATA_DEL_RESP_STATUS_MAX_LEN           2
#define SC_DATA_DEL_RESP_DATA_PATH_MAX_LEN        32
typedef struct __sc_resp_info_data_del
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT16U u16_status;
  INT8U data_path [SC_DATA_DEL_RESP_DATA_PATH_MAX_LEN];
} SC_PKT_DATA_DEL_RESP;

#define SC_PKT_INFO_PENDING_REQ_VALUE_MAX_LEN       16
#define SC_PKT_INFO_PENDING_REQ_REQUEST_ID_MAX_LEN  4
#define SC_PKT_INFO_PENDING_REQ_OBJ_ID_MAX_LEN      2
#define SC_PKT_INFO_PENDING_REQ_INST_ID_MAX_LEN     2
#define SC_PKT_INFO_PENDING_REQ_RES_ID_MAX_LEN      2
#define SC_PKT_INFO_PENDING_REQ_STATUS_MAX_LEN      2
#define SC_PKT_INFO_PENDING_REQ_TYPE_MAX_LEN        1

typedef struct __sc_pending_req_info
{ 
  INT32U u32_req_id;
  INT16U u16_obj_id;
  INT16U u16_inst_id;
  INT16U u16_res_id;
  INT16U u16_status;
  INT8U  u8_value [SC_PKT_INFO_PENDING_REQ_VALUE_MAX_LEN];
  INT8U  u8_type;
  INT8U  u8_reserved;  
  INT16U u16_reserved;
}SC_PENDING_REQ_INFO;

typedef struct __sc_resp_info_pending_req
{
  SC_PKT_COMMON_RESP_INFO common_info;
  SC_ARRAY_INFO arr_info;
  SC_PENDING_REQ_INFO req_info [SC_PKT_PENDING_REQ_MAX_REQS];
} SC_PKT_READ_PENDING_REQ_RESP;

#define SC_PKT_INFO_PENDING_REQ_REQUEST_ID_MAX_LEN  4
#define SC_PKT_INFO_PENDING_REQ_STATUS_MAX_LEN      2
typedef struct __sc_packet_resp_del_pending_info
{
  INT32U u32_req_id;
  INT16U u16_status;
  INT16U u16_reserved;
} SC_DEL_PENDING_REQ_INFO;

typedef struct __sc_req_info_del_pending_requests
{
  SC_ARRAY_INFO arr_info;
  SC_DEL_PENDING_REQ_INFO req_info [SC_PKT_DEL_PENDING_REQUEST_NUM_REQS];
} SC_PKT_DEL_PENDING_REQUESTS_REQ;

typedef struct __sc_resp_info_del_pending_requests
{
  SC_PKT_COMMON_RESP_INFO common_info;
  SC_ARRAY_INFO arr_info;
  SC_DEL_PENDING_REQ_INFO req_info [SC_PKT_DEL_PENDING_REQUEST_NUM_REQS];
} SC_PKT_DEL_PENDING_REQUESTS_RESP;

#define SC_RESP_APP_INFO_APP_ID_MAX_LEN       2
#define SC_RESP_APP_INFO_USER_DES_MAX_LEN     32
#define SC_RESP_APP_INFO_STATUS_MAX_LEN   2

typedef struct __sc_packet_resp_list_app
{ 
  INT16U u16_app_id;
  INT16U u16_running;
  INT8U  u8_user_desc [SC_RESP_APP_INFO_USER_DES_MAX_LEN];
} SC_PKT_APP_LIST_INFO;

#define  SC_PKT_INFO_APP_LIST_NUM_APPS_MAX_LEN    2
#define  SC_PKT_INFO_APP_LIST_STATUS_MAX_LEN      2

typedef struct __sc_resp_list_apps
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT16U u16_num_apps;
  INT16U u16_status;
  SC_ARRAY_INFO arr_info;
  SC_PKT_APP_LIST_INFO app_info [SC_PKT_APP_LIST_MAX_APPLICATIONS];
} SC_PKT_APP_LIST_RESP_INFO;

#define  SC_PKT_INFO_EVENT_LIST_APP_ID_MAX_LEN    4
typedef struct __sc_req_info_all_events
{
  INT32U u32_app_id;
} SC_PKT_ALL_EVENTS_REQ;


#define SC_RESP_EVENT_INFO_EVENT_ID_MAX_LEN			2
#define SC_RESP_EVENT_INFO_TYPE_MAX_LEN           2
#define SC_RESP_EVENT_INFO_ENABLED_MAX_LEN        2
#define SC_RESP_EVENT_INFO_PENDING_MAX_LEN        2
#define SC_RESP_EVENT_INFO_COUNT_MAX_LEN          4
#define SC_RESP_EVENT_INFO_USER_DES_MAX_LEN       32
#define SC_RESP_EVENT_INFO_SOURCE_MAX_LEN			32
#define SC_RESP_EVENT_INFO_PARAMETER1_MAX_LEN     32
#define SC_RESP_EVENT_INFO_PARAMETER2_MAX_LEN     32

typedef struct __sc_packet_resp_list_event
{ 
  INT16U u16_event_id;
  INT16U u16_type;
  INT16U u16_enabled;
  INT16U u16_pending;
  INT32U u32_event_count;
  INT8U  user_desc [SC_RESP_EVENT_INFO_USER_DES_MAX_LEN];
  INT8U  source [SC_RESP_EVENT_INFO_SOURCE_MAX_LEN];
  INT8U  parameter1 [SC_RESP_EVENT_INFO_PARAMETER1_MAX_LEN];
  INT8U  parameter2 [SC_RESP_EVENT_INFO_PARAMETER2_MAX_LEN];
} SC_PKT_EVENT_INFO;

#define  SC_PKT_INFO_EVENT_LIST_APP_ID_MAX_LEN    4
#define  SC_PKT_INFO_EVENT_LIST_STATUS_MAX_LEN      2

typedef struct __sc_resp_list_events
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT32U u32_app_id;
  INT16U u16_status;
  SC_ARRAY_INFO arr_info;
  SC_PKT_EVENT_INFO event_info [SC_PKT_EVENT_LIST_MAX_EVENTS];
} SC_PKT_EVENT_LIST_RESP_INFO;

//EBMJ
#define SC_PENDING_EVENT_INFO_EVENT_ID_MAX_LEN			2
#define SC_PENDING_EVENT_INFO_TYPE_MAX_LEN				2
#define SC_PENDING_EVENT_INFO_COUNT_MAX_LEN				4
#define SC_PENDING_EVENT_INFO_SOURCE_MAX_LEN			32
#define SC_PENDING_EVENT_INFO_PARAMETER1_MAX_LEN		32
#define SC_PENDING_EVENT_INFO_PARAMETER2_MAX_LEN		32

typedef struct __sc_pending_event_info
{ 
  INT16U u16_event_id;
  INT16U u16_type;
  INT32U u32_event_count;
  INT8U  source [SC_PENDING_EVENT_INFO_SOURCE_MAX_LEN];
  INT8U  parameter1 [SC_PENDING_EVENT_INFO_PARAMETER1_MAX_LEN];
  INT8U  parameter2 [SC_PENDING_EVENT_INFO_PARAMETER2_MAX_LEN];
}SC_PENDING_EVENT_INFO;

typedef struct __sc_resp_info_pending_event
{
  SC_PKT_COMMON_RESP_INFO common_info;
  INT32U u32_app_id;
  INT16U u16_status;
  SC_ARRAY_INFO arr_info;
  SC_PENDING_EVENT_INFO event_info [SC_PKT_PENDING_REQ_MAX_REQS];
} SC_PKT_PENDING_EVENT_RESP_INFO;//EBMJ

#define SC_RESP_EVENT_INFO_EVENT_ID_MAX_LEN       2
#define SC_RESP_EVENT_INFO_TYPE_MAX_LEN           2
#define SC_RESP_EVENT_INFO_ENABLED_MAX_LEN        2
#define SC_RESP_EVENT_INFO_PENDING_MAX_LEN        2
#define SC_RESP_EVENT_INFO_USER_DES_MAX_LEN       32
#define SC_RESP_EVENT_INFO_SOURCE_MAX_LEN       32
#define SC_RESP_EVENT_INFO_PARAMETER1_MAX_LEN     32
#define SC_RESP_EVENT_INFO_PARAMETER2_MAX_LEN     32

#define  SC_PKT_INFO_CLEAR_EVENT_INFO_EVENT_ID_MAX_LEN    2
#define  SC_PKT_INFO_CLEAR_EVENT_INFO_STATUS_MAX_LEN      2
#define  SC_PKT_INFO_CLEAR_EVENT_INFO_EVENT_CNT_MAX_LEN   4
typedef struct __sc_packet_resp_clear_event
{ 
  INT16U u16_event_id;
  INT16U u16_status;
  INT32U u32_event_count;
} SC_PKT_CLEAR_EVENT_INFO;

#define  SC_PKT_INFO_CLEAR_EVENT_LIST_APP_ID_MAX_LEN    4
typedef struct __sc_req_info_clear_events
{
  INT32U u32_app_id;
  SC_ARRAY_INFO arr_info;
  SC_PKT_CLEAR_EVENT_INFO event_info [SC_PKT_EVENT_LIST_MAX_EVENTS];
} SC_PKT_CLEAR_EVENTS_REQ;

typedef struct __sc_resp_info_clear_events
{
  INT32U u32_app_id;
  SC_ARRAY_INFO arr_info;
  SC_PKT_CLEAR_EVENT_INFO event_info [SC_PKT_EVENT_LIST_MAX_EVENTS];
} SC_PKT_CLEAR_EVENTS_RESP;

typedef union __sc_packet_info
{
  SC_PKT_COMMON_RESP_INFO info_common_resp;
  SC_PKT_DEV_REG_RESP_INFO info_dev_reg_resp;
  SC_PKT_DEV_UNREG_REQ_INFO info_dev_unreg_req;
  SC_PKT_DEV_UNREG_RESP_INFO info_dev_unreg_resp;
  SC_PKT_DEV_LIST_RESP_INFO info_dev_list_resp;
  SC_PKT_DATA_WRITE_REQ info_data_write_req;
  SC_PKT_DATA_WRITE_RESP info_data_write_resp;
  SC_PKT_DATA_READ_REQ info_data_read_req;
  SC_PKT_DATA_READ_RESP info_data_read_resp;
  SC_PKT_DATA_DEL_REQ info_data_del_req;
  SC_PKT_DATA_DEL_RESP info_data_del_resp;
  SC_PKT_READ_PENDING_REQ_RESP info_pending_req_resp;
  SC_PKT_DEL_PENDING_REQUESTS_REQ info_del_req_req;
  SC_PKT_DEL_PENDING_REQUESTS_RESP info_del_req_resp;
  SC_PKT_APP_LIST_RESP_INFO info_app_list_resp;
  SC_PKT_ALL_EVENTS_REQ info_all_events_req;
  SC_PKT_CLEAR_EVENTS_REQ info_clear_events_req;
  SC_PKT_CLEAR_EVENTS_RESP info_clear_events_resp;
} SC_PACKET_INFO;


int sc_get_next_command ();
int sc_set_last_cmd_result (int result);
int sc_prep_http_request_packet (INT8U *ptr_tx_buf, int max_len);
int sc_set_resp_pkt_info (void *ptr_resp_pkt, int resp_pkt_len);
int sc_set_command (INT8U u8_cmd, void *ptr_arg);
int sc_get_last_cmd_result ();
int sc_req_add_del_pending_req (SC_PKT_DEL_PENDING_REQUESTS_REQ *ptr_del_req_info, INT32U u32_req_id, INT16U u16_status);
int sc_req_set_clear_pending_event_app_id (SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_event_req_info, INT32U u32_app_id);
int sc_req_add_clear_pending_event (SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_event_req_info, INT16U u16_event_id, INT32U u32_event_count);
int sc_req_add_data_write (SC_PKT_DATA_WRITE_REQ *ptr_update_req, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id);
int sc_req_set_data_read_all (SC_PKT_DATA_READ_REQ *ptr_read_req_info);
int sc_req_set_data_read_obj (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id);
int sc_req_set_data_read_inst (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id);
int sc_req_set_data_read_res (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id);
int sc_req_set_data_read_time (SC_PKT_DATA_READ_REQ *ptr_read_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id, INT32U u32_time);

int sc_req_set_data_del_all (SC_PKT_DATA_DEL_REQ *ptr_del_req_info);
int sc_req_set_data_del_obj (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id);
int sc_req_set_data_del_inst (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id);
int sc_req_set_data_del_res (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id);
int sc_req_set_data_del_time (SC_PKT_DATA_DEL_REQ *ptr_del_req_info, INT16U u16_obj_id, INT16U u16_inst_id, INT16U u16_res_id, INT32U u32_time);

#endif
