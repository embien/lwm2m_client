#include <lwm2m_client.h>


//Must match the order in sc_resp_key_list
#define SC_RESP_PKT_ACTION_TYPE_DEV_CREATION        1
#define SC_RESP_PKT_ACTION_TYPE_REQ_READ            2
#define SC_RESP_PKT_ACTION_TYPE_DATA_WRITE          3
#define SC_RESP_PKT_ACTION_TYPE_REQ_DONE            4
#define SC_RESP_PKT_ACTION_TYPE_DEV_LIST            5
#define SC_RESP_PKT_ACTION_TYPE_DEV_DELETION        6
#define SC_RESP_PKT_ACTION_TYPE_DATA_READ           7
#define SC_RESP_PKT_ACTION_TYPE_DATA_DELETION       8
#define SC_RESP_PKT_ACTION_TYPE_ALL_APPLICATIONS	9
#define SC_RESP_PKT_ACTION_TYPE_ALL_EVENTS			10
#define SC_RESP_PKT_ACTION_TYPE_PENDING_EVENTS		11
#define SC_RESP_PKT_ACTION_TYPE_CLEAR_EVENTS		12

typedef int (*FN_PTR_SC_GET_ENUM_VALUE) (INT8U *, int len);
typedef int (*FN_PTR_SC_GET_ARR_ITEM_SIZE) ();

#define SC_RESP_PKT_READ_WRITE_TYPES              2
#define SC_RESP_PKT_ACTION_TYPES                  12
#define SC_RESP_PKT_TRUE_FALSE_TYPES                 2
const SC_ENUM_INT_PAIR sc_resp_action_value_pair_list [SC_RESP_PKT_ACTION_TYPES] = 
{
  {"device_creation" , SC_RESP_PKT_ACTION_TYPE_DEV_CREATION},
  {"data_write"      , SC_RESP_PKT_ACTION_TYPE_DATA_WRITE},
  {"requests_read"   , SC_RESP_PKT_ACTION_TYPE_REQ_READ},
  {"requests_done"   , SC_RESP_PKT_ACTION_TYPE_REQ_DONE},
  {"device_list"     , SC_RESP_PKT_ACTION_TYPE_DEV_LIST},
  {"device_deletion" , SC_RESP_PKT_ACTION_TYPE_DEV_DELETION},
  {"data_delete"     , SC_RESP_PKT_ACTION_TYPE_DATA_DELETION},
  {"data_read"       , SC_RESP_PKT_ACTION_TYPE_DATA_READ},
  {"all_applications", SC_RESP_PKT_ACTION_TYPE_ALL_APPLICATIONS},
  {"all_events"      , SC_RESP_PKT_ACTION_TYPE_ALL_EVENTS},
  {"pending_events"  , SC_RESP_PKT_ACTION_TYPE_PENDING_EVENTS},
  {"events_done"	, SC_RESP_PKT_ACTION_TYPE_CLEAR_EVENTS},
};
const SC_ENUM_INT_PAIR sc_resp_read_write_value_pair_list [SC_RESP_PKT_READ_WRITE_TYPES] = 
{
  {"read" , 0},
  {"write" , 1},
};

const SC_ENUM_INT_PAIR sc_resp_true_false_pair_list [SC_RESP_PKT_TRUE_FALSE_TYPES] = 
{
  {"true" , 1},
  {"false" , 0},
};


int get_action_enum_value (char * str_action, int len);
int get_pending_req_num (char *pending_req, int len);
int get_read_write_enum_value (char *pending_req, int len);
int get_true_false_enum_value (char *str, int len);
int get_array_item_size_device_list ();
int get_array_item_size_pending_req ();
int get_array_item_size_del_pending_req ();
int get_array_item_size_dev_info ();
int get_array_item_size_app_info ();
int get_array_item_size_read_data_info ();
int get_array_item_size_event_info ();
int get_array_item_size_clear_event_info ();
int sc_get_key_index_in_list (int resp_action, char *ptr_key, int key_len);
int sc_extract_value (SC_HTTP_RESPONSE *ptr_http_resp, SC_KEY_INFO *ptr_key_info);

extern LWM2M_OBJECT_INFO supported_object_list [LWM2M_MAX_SUPPORTED_OBJECTS];

const SC_KEY_INFO sc_key_info_common_resp[SC_RESP_NUM_KEY_TYPE_COMMON] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_list_dev_reg_resp [SC_RESP_NUM_KEY_TYPE_DEV_REG] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"device_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_DEV_REG_RESP_INFO, arr_info.num_arr_items), SC_PKT_DEV_REG_REQ_MAX_NUM_RESOURCES, get_array_item_size_device_list},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"instance_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_inst_id), SC_PKT_INFO_RES_INST_ID_MAX_LEN, NULL},
  {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
  {"object_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_obj_id), SC_PKT_INFO_RES_OBJ_ID_MAX_LEN, NULL},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_status), SC_PKT_INFO_RES_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_dev_list_resp [SC_RESP_NUM_KEY_TYPE_DEV_LIST] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"device_desc", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_INFO, u8_dev_desc), SC_RESP_DEV_INFO_DEV_DESC_MAX_LEN, NULL},
  {"device_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_RESP_INFO, arr_info.num_arr_items), SC_PKT_DEV_LIST_MAX_DEVICES, get_array_item_size_dev_info},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"instance_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_INFO, u16_inst_id), SC_RESP_DEV_INFO_INST_ID_MAX_LEN, NULL},
  {"num_devices", SC_KEY_INFO_VALUE_TYPE_INT,  STRUCT_MEMBER_POS(SC_PKT_DEV_LIST_RESP_INFO, u16_num_devices), SC_PKT_INFO_DEV_LIST_NUM_DEV_MAX_LEN, NULL},
  {"object_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_INFO, u16_obj_id),SC_RESP_DEV_INFO_OBJ_ID_MAX_LEN, NULL},
  {"registered", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_INFO, u16_reg_status), SC_RESP_DEV_INFO_REG_STATUS_MAX_LEN, get_true_false_enum_value},   
  {"user_desc", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_INFO, u8_user_desc), SC_RESP_DEV_INFO_USER_DES_MAX_LEN, NULL},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_DEV_LIST_RESP_INFO, u16_status), SC_PKT_INFO_DEV_LIST_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_data_write_resp [SC_RESP_NUM_KEY_TYPE_DATA_WRITE] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"data_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_DATA_WRITE_RESP, arr_info.num_arr_items), SC_PKT_DEV_REG_REQ_MAX_NUM_RESOURCES, get_array_item_size_device_list},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"instance_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_inst_id), SC_PKT_INFO_RES_INST_ID_MAX_LEN, NULL},
  {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
  {"object_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_obj_id), SC_PKT_INFO_RES_OBJ_ID_MAX_LEN, NULL},
  {"pending_requests", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_pending_request), SC_PKT_INFO_PENDING_REQ_VAL_MAX_LEN, get_pending_req_num},
  {"resource_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_res_id), SC_PKT_INFO_RES_RES_ID_MAX_LEN, NULL},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_INFO, u16_status), SC_PKT_INFO_RES_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_read_pending_req_resp [SC_RESP_NUM_KEY_TYPE_READ_PEND_REQ] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"instance_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO, u16_inst_id), SC_PKT_INFO_PENDING_REQ_INST_ID_MAX_LEN, NULL},
  {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
  {"object_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO, u16_obj_id), SC_PKT_INFO_PENDING_REQ_OBJ_ID_MAX_LEN, NULL},
  {"request_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO,u32_req_id), SC_PKT_INFO_PENDING_REQ_REQUEST_ID_MAX_LEN, NULL}, 
  {"request_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_READ_PENDING_REQ_RESP, arr_info.num_arr_items), SC_PKT_PENDING_REQ_MAX_REQS, get_array_item_size_pending_req},
  {"resource_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO, u16_res_id), SC_PKT_INFO_PENDING_REQ_RES_ID_MAX_LEN, NULL},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO, u16_status), SC_PKT_INFO_PENDING_REQ_STATUS_MAX_LEN, NULL},
  {"type", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO, u8_type), SC_PKT_INFO_PENDING_REQ_TYPE_MAX_LEN, get_read_write_enum_value},
  {"value", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PENDING_REQ_INFO,  u8_value), SC_PKT_INFO_PENDING_REQ_VAL_MAX_LEN, NULL}
};

const SC_KEY_INFO sc_key_info_read_app_list_resp  [SC_RESP_NUM_KEY_TYPE_APP_LIST] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"application_id",SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_APP_LIST_INFO, u16_app_id),SC_RESP_APP_INFO_APP_ID_MAX_LEN, NULL},
 {"application_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_APP_LIST_RESP_INFO, arr_info.num_arr_items), SC_PKT_APP_LIST_MAX_APPLICATIONS, get_array_item_size_app_info},
 {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
 {"running",SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_APP_LIST_INFO, u16_running),SC_RESP_APP_INFO_STATUS_MAX_LEN, get_true_false_enum_value},
 {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_APP_LIST_RESP_INFO, u16_status), SC_PKT_INFO_APP_LIST_STATUS_MAX_LEN, NULL},
 {"user_desc", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_APP_LIST_INFO, u8_user_desc), SC_RESP_APP_INFO_USER_DES_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_created_events [SC_RESP_NUM_KEY_TYPE_EVENTS_LIST] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"application_id",SC_KEY_INFO_VALUE_TYPE_INT,STRUCT_MEMBER_POS (SC_PKT_EVENT_LIST_RESP_INFO, u32_app_id),SC_PKT_INFO_EVENT_LIST_APP_ID_MAX_LEN, NULL},
 {"enabled", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, u16_enabled), SC_RESP_EVENT_INFO_ENABLED_MAX_LEN, get_true_false_enum_value},
 {"event_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, u16_event_id),SC_RESP_EVENT_INFO_EVENT_ID_MAX_LEN, NULL},
 {"event_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_EVENT_LIST_RESP_INFO, arr_info.num_arr_items), SC_PKT_EVENT_LIST_MAX_EVENTS, get_array_item_size_event_info},
 //{"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
 //{"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_EVENT_LIST_RESP_INFO, u16_status), SC_PKT_INFO_EVENT_LIST_STATUS_MAX_LEN, NULL},
 {"parameter1", SC_KEY_INFO_VALUE_TYPE_STRING,  STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, parameter1),SC_RESP_EVENT_INFO_PARAMETER1_MAX_LEN, NULL},
 {"parameter2", SC_KEY_INFO_VALUE_TYPE_STRING,  STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, parameter2),SC_RESP_EVENT_INFO_PARAMETER2_MAX_LEN, NULL},
 {"pending", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, u16_pending),SC_RESP_EVENT_INFO_PENDING_MAX_LEN, get_true_false_enum_value},
 {"source", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, source), SC_RESP_EVENT_INFO_SOURCE_MAX_LEN, NULL},
 {"type", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, u16_type), SC_RESP_EVENT_INFO_TYPE_MAX_LEN, NULL}, //EBMJ
 {"user_desc", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_EVENT_INFO, user_desc), SC_RESP_EVENT_INFO_USER_DES_MAX_LEN, NULL},
 }; 

const SC_KEY_INFO sc_key_info_pending_events [SC_RESP_NUM_KEY_TYPE_PENDING_EVENTS] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"application_id",SC_KEY_INFO_VALUE_TYPE_INT,STRUCT_MEMBER_POS (SC_PKT_PENDING_EVENT_RESP_INFO, u32_app_id),SC_PKT_INFO_EVENT_LIST_APP_ID_MAX_LEN, NULL},
 {"event_count", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, u32_event_count),SC_PENDING_EVENT_INFO_COUNT_MAX_LEN, NULL},
 {"event_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, u16_event_id),SC_PENDING_EVENT_INFO_EVENT_ID_MAX_LEN, NULL},
 {"event_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_PENDING_EVENT_RESP_INFO, arr_info.num_arr_items), SC_PKT_EVENT_LIST_MAX_EVENTS, get_array_item_size_event_info},
 {"parameter1", SC_KEY_INFO_VALUE_TYPE_STRING,  STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, parameter1),SC_PENDING_EVENT_INFO_PARAMETER1_MAX_LEN, NULL},
 {"parameter2", SC_KEY_INFO_VALUE_TYPE_STRING,  STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, parameter2),SC_PENDING_EVENT_INFO_PARAMETER2_MAX_LEN, NULL},
 {"source", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, source), SC_PENDING_EVENT_INFO_SOURCE_MAX_LEN, NULL},
 {"type", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PENDING_EVENT_INFO, u16_type), SC_PENDING_EVENT_INFO_TYPE_MAX_LEN, NULL}, //EBMJ
 }; 

const SC_KEY_INFO sc_key_info_clear_events_resp  [SC_RESP_NUM_KEY_TYPE_CLEAR_EVENTS] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"application_id",SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_CLEAR_EVENTS_RESP, u32_app_id),SC_PKT_INFO_CLEAR_EVENT_LIST_APP_ID_MAX_LEN, NULL},
 {"event_count",SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_CLEAR_EVENT_INFO, u32_event_count),SC_PKT_INFO_CLEAR_EVENT_INFO_EVENT_CNT_MAX_LEN, NULL},
 {"event_id", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_CLEAR_EVENT_INFO, u16_event_id), SC_PKT_INFO_CLEAR_EVENT_INFO_EVENT_ID_MAX_LEN, NULL},
 {"event_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_CLEAR_EVENTS_RESP, arr_info.num_arr_items), SC_PKT_EVENT_LIST_MAX_EVENTS, get_array_item_size_clear_event_info},
 {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_CLEAR_EVENT_INFO, u16_status), SC_PKT_INFO_CLEAR_EVENT_INFO_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_dev_del_resp [SC_RESP_NUM_KEY_TYPE_DEV_DELETE] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"devices", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_DEV_UNREG_RESP_INFO, device_path), SC_RESP_DEV_UNREG_DEV_PATH_MAX_LEN, NULL},
 {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
 {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
 {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_DEV_UNREG_RESP_INFO, u16_status), SC_RESP_DEV_UNREG_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_data_read_resp [SC_RESP_NUM_KEY_TYPE_DATA_READ] = {
 {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
 {"data_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_DATA_READ_RESP, arr_info.num_arr_items), SC_PKT_DATA_READ_REQ_MAX_READS, get_array_item_size_read_data_info},
 {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
 {"instance_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_VALUE_INFO, u16_inst_id), SC_PKT_INFO_RES_INST_ID_MAX_LEN, NULL},
 {"object_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_VALUE_INFO, u16_obj_id), SC_PKT_INFO_RES_OBJ_ID_MAX_LEN, NULL},
 {"resource_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_RES_VALUE_INFO, u16_res_id), SC_PKT_INFO_RES_RES_ID_MAX_LEN, NULL},
 {"value", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_RES_VALUE_INFO, value), SC_PKT_INFO_RES_VALUE_MAX_LEN, NULL}
};

const SC_KEY_INFO sc_key_info_data_del_resp [SC_RESP_NUM_KEY_TYPE_DATA_DELETE] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"data", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_DATA_DEL_RESP, data_path),SC_DATA_DEL_RESP_DATA_PATH_MAX_LEN,NULL},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_PKT_DATA_DEL_RESP, u16_status), SC_DATA_DEL_RESP_STATUS_MAX_LEN, NULL},
};

const SC_KEY_INFO sc_key_info_del_pending_resp [SC_RESP_NUM_KEY_TYPE_DEL_PEND_REQ] = {
  {"action", SC_KEY_INFO_VALUE_TYPE_ENUM, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_action), SC_PKT_INFO_ACTION_VAL_MAX_LEN, get_action_enum_value},
  {"endpoint", SC_KEY_INFO_VALUE_TYPE_STRING, STRUCT_MEMBER_POS (SC_PKT_COMMON_RESP_INFO, u8_endpoint), SC_PKT_INFO_ENDPOINT_VAL_MAX_LEN, NULL},
  {"message", SC_KEY_INFO_VALUE_TYPE_DISCARD},
  {"request_id", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_DEL_PENDING_REQ_INFO, u32_req_id), SC_PKT_INFO_PENDING_REQ_REQUEST_ID_MAX_LEN, NULL}, 
  {"request_list", SC_KEY_INFO_VALUE_TYPE_ARRAY, STRUCT_MEMBER_POS (SC_PKT_DEL_PENDING_REQUESTS_RESP, arr_info.num_arr_items), SC_PKT_DEL_PENDING_REQUEST_NUM_REQS, get_array_item_size_del_pending_req},
  {"status", SC_KEY_INFO_VALUE_TYPE_INT, STRUCT_MEMBER_POS (SC_DEL_PENDING_REQ_INFO, u16_status), SC_PKT_INFO_PENDING_REQ_STATUS_MAX_LEN, NULL},
};


const SC_RESP_KEY_LIST sc_resp_key_list [SC_MAX_NUM_RESP_TYPES] = 
{
  {sc_key_info_common_resp, SC_RESP_NUM_KEY_TYPE_COMMON},
  {sc_key_info_list_dev_reg_resp, SC_RESP_NUM_KEY_TYPE_DEV_REG},
  {sc_key_info_read_pending_req_resp, SC_RESP_NUM_KEY_TYPE_READ_PEND_REQ},
  {sc_key_info_data_write_resp, SC_RESP_NUM_KEY_TYPE_DATA_WRITE},
  {sc_key_info_del_pending_resp, SC_RESP_NUM_KEY_TYPE_DEL_PEND_REQ}, 
  {sc_key_info_dev_list_resp, SC_RESP_NUM_KEY_TYPE_DEV_LIST},
  {sc_key_info_dev_del_resp, SC_RESP_NUM_KEY_TYPE_DEV_DELETE},
  {sc_key_info_data_read_resp, SC_RESP_NUM_KEY_TYPE_DATA_READ},
  {sc_key_info_data_del_resp, SC_RESP_NUM_KEY_TYPE_DATA_DELETE},
  {sc_key_info_read_app_list_resp,SC_RESP_NUM_KEY_TYPE_APP_LIST},
  {sc_key_info_created_events, SC_RESP_NUM_KEY_TYPE_EVENTS_LIST},
  {sc_key_info_pending_events, SC_RESP_NUM_KEY_TYPE_PENDING_EVENTS},
  {sc_key_info_clear_events_resp, SC_RESP_NUM_KEY_TYPE_CLEAR_EVENTS},
};

/*! \fn        int sc_prepare_packet_reg_client (INT8U* ptr_request_buf)
    \brief     Prepare the registration packet to register the client in skycase server  
    \param[in] ptr_request       Data buffer to fill the registration information 
    \return    int               Data  length on success or error code on failure           
*/
int sc_prepare_packet_reg_client (INT8U* ptr_req_buf)
{
  int data_len = 0;
  char *ptr_data = ptr_req_buf;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  int  append_len, comma_flag  = 1, num_desc = 0, index = 0, obj_cnt = 0, inst_cnt = 0, u16_inst = 0,inst_index = 0;
  int ret_len = 0,res_index = 0;
  data_len = 0; 
  ret_len = sprintf (ptr_data + data_len, "{endpoint:\"%s\",device_list:[", SC_CLIENT_END_POINT_NAME);
  data_len += ret_len;
  //printf ("%s\r\n",ptr_data);
#if 1
  for (index = 0;index < LWM2M_MAX_SUPPORTED_OBJECTS;index ++)
  {
    ptr_instance_info = supported_object_list [index].ptr_inst_list;
    for (inst_index = 0; inst_index < supported_object_list[index].u8_max_num_inst; inst_index ++)
    { 
      (ptr_instance_info +  inst_index)->u16_inst_id;
        append_len =  sprintf (ptr_data + data_len, "{object_id:\"%d\",instance_id:\"%d\",device_desc:\"%d\",uuid:\"%d\"},", \
                           supported_object_list[index].u16_obj_id,(ptr_instance_info +  inst_index)->u16_inst_id, 123, 456);
      data_len += append_len;
    }
  }
#endif   
 
  data_len --;
#if SC_ENABLE_DEBUG_PRINTS 
  printf ("str_len = %d\r\n", strlen ((char*)ptr_data));
#endif  
  *(ptr_data + data_len) = ']';
  data_len ++;
 *(ptr_data + data_len) = '}';
  return data_len + 1;  
}


/*! \fn        int sc_prep_packet_for_read_value (LWM2M_PROCESS_INFO *ptr_proc_req, INT8U *ptr_data, int object_id, INT16U u16_instance, int request_level)
    \brief     Prepare HTTP request packet to send data and this data is prefered from user specfic IPSO resources 
    \param[in] ptr_proc_req   Information of the processing requests in LWM2M objects
    \param[in] ptr_data       Data buffer to fill the read value
    \param[in] object_id      Requested LWM2M object id 
    \param[in] instance_id    Requested LWM2M instance id 
    \param[in] request_level  Level to process on LWM2M layer
    \return    int  One on success or zero on failure           
*/
int sc_prepare_packet_data_write (INT8U *ptr_data, SC_PKT_DATA_WRITE_REQ *ptr_update_req)
{
  int data_len, append_len, comma_flag  = 1, num_desc = 0, index = 0, obj_cnt = 0, inst_cnt = 0,\
  u16_inst = 0;
  int res_index = 0, ret_len = 0;
  LWM2M_PROCESS_INFO ptr_proc_req;
  SC_RES_INFO *sc_ptr_res_info;
  sc_ptr_res_info = ptr_update_req->res_info;
  res_index = 0;
  data_len = 0; 
  ret_len = sprintf (ptr_data + data_len, "{endpoint:\"%s\",data_list:[", SC_CLIENT_END_POINT_NAME);
  data_len += ret_len;
  ptr_proc_req.u8_request = LWM2M_PROCESS_REQ_READ;
  ptr_proc_req.u8_num_path_elements = 3;
  for (index = 0; index < ptr_update_req->arr_info.num_arr_items; index ++) 
  {
    ptr_proc_req.object_path [LWM2M_PATH_INDEX_OBJECT] = (sc_ptr_res_info + index)->u16_obj_id;
    ptr_proc_req.object_path [LWM2M_PATH_INDEX_INST] = (sc_ptr_res_info + index)->u16_inst_id;
    ptr_proc_req.object_path [LWM2M_PATH_INDEX_RES] = (sc_ptr_res_info + index)->u16_res_id;
    lwm2m_process_request_obj (&ptr_proc_req);
    append_len =  sprintf (ptr_data + data_len, "{object_id:\"%d\",instance_id:\"%d\",resource_id:\"%d\",value:\"%s\"},", \
      (sc_ptr_res_info + index)->u16_obj_id, (sc_ptr_res_info + index)->u16_inst_id,(sc_ptr_res_info + index)->u16_res_id, ptr_proc_req.value);///endpoint:\"%s\",SC_CLIENT_END_POINT_NAME, 
  
    data_len += append_len;
    //data_len ++;
  }
  data_len --;
#if SC_ENABLE_DEBUG_PRINTS
  printf ("str_len = %d\r\n", strlen ((char*)ptr_data));
#endif
  *(ptr_data + data_len) = ']';
  data_len ++;
  *(ptr_data + data_len) = '}';

  return data_len + 1;
}


/*! \fn       int sc_prepare_packet_delete_pending_req (INT8U* ptr_data)
    \brief     Prepare the HTTP request packet for delete pending request 
    \param[in] ptr_data          Data buffer to add the HTTP request information
    \return    int               Zero on success or error code on failure           
*/
int sc_prepare_packet_del_pending_req (INT8U* ptr_data, SC_PKT_DEL_PENDING_REQUESTS_REQ *ptr_del_pending_req) //SC_PKT_READ_PENDING_REQ_RESP *ptr_del_pending_req)
{
  int index = 0, ret_len = 0, append_len = 0,data_len = 0;
  SC_DEL_PENDING_REQ_INFO *sc_ptr_res_info;
  sc_ptr_res_info = ptr_del_pending_req->req_info;
  (sc_ptr_res_info + index)->u16_status = 0; //EBMJ
  ret_len = sprintf (ptr_data + data_len, "{endpoint:\"%s\",request_list:[", SC_CLIENT_END_POINT_NAME);
  data_len += ret_len;
  for (index = 0; index < ptr_del_pending_req->arr_info.num_arr_items; index ++)
  {
    append_len =  sprintf (ptr_data + data_len, "{request_id:\"%d\",status:\"%d\"},",(sc_ptr_res_info + index)->u32_req_id, (sc_ptr_res_info + index)->u16_status); 
    data_len += append_len;
  }
  if (ptr_del_pending_req->arr_info.num_arr_items)
	data_len --;
  *(ptr_data + data_len) = ']';
  data_len ++;
  *(ptr_data + data_len) = '}';
  data_len ++; 
  return data_len + 1;
}

/*! \fn       int sc_prepare_packet_clear_pending_events (INT8U* ptr_data)
    \brief     Prepare the HTTP request packet for delete pending request 
    \param[in] ptr_data          Data buffer to add the HTTP request information
    \return    int               Zero on success or error code on failure           
*/
int sc_prepare_packet_clear_pending_events (INT8U* ptr_data, SC_PKT_CLEAR_EVENTS_REQ *ptr_clear_pending_event) //SC_PKT_READ_PENDING_REQ_RESP *ptr_del_pending_req)
{
  int index = 0, ret_len = 0, append_len = 0,data_len = 0;
  SC_PKT_CLEAR_EVENT_INFO *sc_ptr_res_info;
  sc_ptr_res_info = ptr_clear_pending_event->event_info;
  (sc_ptr_res_info + index)->u16_status = 0; //EBMJ
  ret_len = sprintf (ptr_data + data_len, "{application_id:\"%d\",event_list:[", ptr_clear_pending_event->u32_app_id);
  data_len += ret_len;
  for (index = 0; index < ptr_clear_pending_event->arr_info.num_arr_items; index ++)
  {
    append_len =  sprintf (ptr_data + data_len, "{event_id:\"%d\",event_count:\"%d\"},",(sc_ptr_res_info + index)->u16_event_id, (sc_ptr_res_info + index)->u32_event_count); 
    data_len += append_len;
  }
  if (ptr_clear_pending_event->arr_info.num_arr_items)
	data_len --;
  *(ptr_data + data_len) = ']';
  data_len ++;
  *(ptr_data + data_len) = '}';
  data_len ++; 
  return data_len + 1;
}

int sc_process_http_resp_chars (SC_HTTP_RESPONSE *ptr_http_resp)
{
  int index;
  INT8U *ptr_store_mem;
  char *ptr_field;
  int total_len;
  total_len = ptr_http_resp->u16_content_len; 
  ptr_field = ptr_http_resp->ptr_resp + ptr_http_resp->processed_len;
  index = 0;
  while (1)
  {
    if (ptr_field [index] == '"')
    {
      //Do nothing
      //printf ("Dbl qt");
    }
    else if (ptr_field [index] == '{')
    {
      //Do nothing
      //printf ("Dbl {");
    }
    else if (ptr_field [index] == '}')
    {
      //Do nothing
      //printf ("Dbl }");
          if (ptr_http_resp->arr_type_size [ptr_http_resp->depth])
      {
        ptr_store_mem = ptr_http_resp->ptr_base_mem [ptr_http_resp->depth];
        (*(int *)(ptr_store_mem)) ++;
      }

    }
      else if (ptr_field [index] == ']')
    {
      //Do nothing
      //printf ("Dbl ]");
      ptr_http_resp->depth --;
    }
    else if (ptr_field [index] == ',')
    {
      //Do nothing
      //printf ("Dbl ,");
    }
    else
      break;
    index ++;
  }
  //ptr_http_resp->processed_len += index;
  return index;
}

int sc_http_resp_discard_value (SC_HTTP_RESPONSE *ptr_http_resp)
{
  int total_len, index;
  char *ptr_val, discard_char, discard_end_char;
  int discard_count;
  ptr_val = ptr_http_resp->processed_len + ptr_http_resp->ptr_resp;
  total_len = ptr_http_resp->u16_content_len + ptr_http_resp->u16_content_pos;
  discard_char = *ptr_val;
  discard_count = 1;
  if (discard_char == '[')
    discard_end_char = ']';
  else if (discard_char == '{')
    discard_end_char = '}';
  else if (discard_char == '"')
    discard_end_char = '"';
  else
  {
    discard_char = 0;
    discard_end_char = ',';
  }
    
  printf ("To discard value based on '%c' at (%s)", discard_char, ptr_val);
  ptr_val ++;
  for (index = ptr_http_resp->processed_len; index < total_len; index ++)
  {
    if (*ptr_val == discard_end_char)
    {
      if (-- discard_count == 0)
      {
        break;
      }
    } 
    else if (*ptr_val == discard_char)
      discard_count ++;
    ptr_val ++;
  }
  return index - ptr_http_resp->processed_len + 2;
}

int sc_process_http_resp_content (SC_HTTP_RESPONSE *ptr_http_resp)
{ 
  int index, ret_index,total_len, value_index = 0, start_index = 0, ret_val_index, key_len, key_start;
  SC_PKT_COMMON_RESP_INFO *ptr_common_resp_info;
  INT8U *ptr_field;
  total_len = ptr_http_resp->u16_content_len; 
  ptr_field = ptr_http_resp->ptr_resp + ptr_http_resp->u16_content_pos;
  if (ptr_http_resp->ptr_resp [ptr_http_resp->u16_content_pos] != '{')
  {
    return -1;
  }
  //temp 
  //memset (ptr_http_resp->ptr_pkt_buf, 0, resp_buf_size);
  ptr_common_resp_info = ptr_http_resp->ptr_pkt_buf;
  ptr_http_resp->ptr_base_mem [0] = ptr_http_resp->ptr_pkt_buf;
  ptr_http_resp->arr_type_size [0] = 0;
  ptr_http_resp->depth = 0;


  ptr_field ++;
  ptr_http_resp->processed_len ++;
  //printf ("ptr field for process\n\r :%s\r\n",ptr_field);
  index = 0; 
  while (ptr_field [index] == '"')
  {
    index ++; 
  }
  if (ptr_field [index] == '{')
  {
    index ++; 
  }
  key_start = index;
  key_len = 0;
  ptr_http_resp->processed_len += index;
  for ( ; index < total_len;)
  {
    if (ptr_field [index] == ':')
    {
      ret_index = sc_get_key_index_in_list (ptr_common_resp_info->u8_action, ptr_field + key_start, key_len); 
      //printf ("return index :%d\r\n",ret_index);
      ptr_http_resp->processed_len += key_len + 1;
      index ++;
      if (ret_index < 0)
      {
        printf ("Some error in processing the key\r\n");
        key_len = sc_http_resp_discard_value (ptr_http_resp);
        index += key_len;
        ptr_http_resp->processed_len += key_len;
      }
      else
      {
        ret_val_index = sc_extract_value (ptr_http_resp, &sc_resp_key_list [ptr_common_resp_info->u8_action].ptr_key_list[ret_index]);
        if (!ret_val_index)
        {
          printf ("Some error in processing the value\r\n");
        }
        else
        {
          index += ret_val_index;
          key_len = 0;
          ptr_http_resp->processed_len += (ret_val_index);
          key_len = sc_process_http_resp_chars (ptr_http_resp);
          index += key_len;
          ptr_http_resp->processed_len += key_len;
        }
      }
      key_start = index;
      key_len = 0;  
    }
    else
    {
      index ++;
      key_len ++;
    }
  } 
  return 0;
}

char karthik_string [50];
int sc_extract_value (SC_HTTP_RESPONSE *ptr_http_resp, SC_KEY_INFO *ptr_key_info)
{
  int index,value_index = 0, total_len, action_index, array_item_size, store_index;
  INT8U *ptr_value ,*ptr_strtol;
  int value_len = 0, consumed_len = 0;
  FN_PTR_SC_GET_ENUM_VALUE fn_ptr_get_enum_value;
  FN_PTR_SC_GET_ARR_ITEM_SIZE fn_ptr_get_arr_size;
  INT8U *ptr_store_mem;
  void *ptr_void_mem;
  total_len =  ptr_http_resp->u16_content_len + ptr_http_resp->u16_content_pos;
  ptr_value = ptr_http_resp->ptr_resp + ptr_http_resp->processed_len;
  ptr_store_mem = ptr_http_resp->ptr_base_mem [ptr_http_resp->depth];
  index = 0; 

  if (*ptr_value == '"')
  {
    ptr_value ++;
    consumed_len ++;
  }
  if (*ptr_value == '[') 
  {
    ptr_http_resp->depth ++;  
    ptr_http_resp->ptr_base_mem [ptr_http_resp->depth] = (ptr_key_info->store_offset + ptr_http_resp->ptr_base_mem [ptr_http_resp->depth - 1]);
    fn_ptr_get_arr_size = ptr_key_info->ptr_misc;
    action_index = fn_ptr_get_arr_size ();
    ptr_http_resp->arr_type_size [ptr_http_resp->depth] = action_index; 
  
    ptr_value ++;
    consumed_len ++;
    return consumed_len;
  }
  while (index < total_len)
  {
    if ((ptr_value [index] == ',' ) || (ptr_value [index] == '}') || (ptr_value [index] == ']') || (ptr_value [index] == '"'))
      break;
    value_len ++;
    index ++;
  }
  consumed_len += index;
  strncpy (karthik_string, ptr_value, value_len);
  karthik_string [value_len] = 0;
  //printf ("Going to process value [%s]\r\n", karthik_string);
  if (ptr_http_resp->arr_type_size [ptr_http_resp->depth])
  {
    store_index = *(int *)(ptr_store_mem);
    array_item_size = ptr_http_resp->arr_type_size [ptr_http_resp->depth];
    ptr_void_mem = ((ptr_store_mem + (store_index * array_item_size) + 4 + ptr_key_info->store_offset));
  }
  else
  {
    ptr_void_mem = ptr_store_mem + ptr_key_info->store_offset;
  }
  if (ptr_key_info->u8_value_type == SC_KEY_INFO_VALUE_TYPE_STRING)
  {
    if (value_len >= ptr_key_info->max_len)
      value_len = ptr_key_info->max_len;
    strncpy (ptr_void_mem, ptr_value, value_len); 
    *((INT8U *)ptr_void_mem + value_len) = 0;
  } 
  else if (ptr_key_info->u8_value_type == SC_KEY_INFO_VALUE_TYPE_INT)
  {
    action_index = strtol (ptr_value, &ptr_strtol, 10);
    if (ptr_key_info->max_len == 1)
      *(INT8U*)(ptr_void_mem) = action_index;
    else if (ptr_key_info->max_len == 2)
      *(INT16U*)(ptr_void_mem) = action_index;
    else if (ptr_key_info->max_len == 4)
    {
      *(INT32U*)(ptr_void_mem) = action_index;
    }
  }
  else if (ptr_key_info->u8_value_type == SC_KEY_INFO_VALUE_TYPE_ENUM)
  {
    fn_ptr_get_enum_value = ptr_key_info->ptr_misc;
    action_index = fn_ptr_get_enum_value (ptr_value, value_len);
    if ( action_index >= 0)
    {
      if (ptr_key_info->max_len == 1)
        *(INT8U*)(ptr_void_mem) = action_index;
      else if (ptr_key_info->max_len == 2)
       *(INT16U*)(ptr_void_mem) = action_index;
      else if (ptr_key_info->max_len == 4)
       *(INT32U*)(ptr_void_mem) = action_index;
    }
  }
  else if (ptr_key_info->u8_value_type == SC_KEY_INFO_VALUE_TYPE_DISCARD)
  {
    //printf ("Discarding");
  }
  return consumed_len;
}

int sc_get_key_index_in_list (int resp_action, char *ptr_key, int key_len)
{
  int index = 0,cmp_val;
  if (*(ptr_key + key_len - 1) == '"')
  {
      key_len --;
  }
  for (index = 0; index < sc_resp_key_list [resp_action].u8_num_keys; index ++)
  {
    cmp_val = strnicmp (ptr_key, sc_resp_key_list[resp_action].ptr_key_list[index].str_key_name, key_len);
    if (cmp_val == 0)
      return index;
    else if (cmp_val < 0)
    {
        break;
    }
  }
  printf ("Some error in (in %d) searching for key %s\r\n", resp_action, ptr_key);
  while (1);
  return -1;
}

int get_array_item_size_device_list()
{
  return sizeof (SC_RES_INFO);
}
int get_array_item_size_read_data_info ()
{
  return sizeof (SC_RES_VALUE_INFO);
}

int get_array_item_size_pending_req ()
{
  return sizeof (SC_PENDING_REQ_INFO);
}
int get_array_item_size_del_pending_req ()
{
  return sizeof (SC_DEL_PENDING_REQ_INFO);
}
int get_array_item_size_dev_info ()
{
  return sizeof (SC_PKT_DEV_LIST_INFO);
}
int get_array_item_size_app_info ()
{
  return sizeof (SC_PKT_APP_LIST_INFO);
}
int get_array_item_size_event_info ()
{
  return sizeof (SC_PKT_EVENT_INFO);
}
int get_array_item_size_clear_event_info ()
{
  return sizeof (SC_PKT_CLEAR_EVENT_INFO);
}
int get_int_from_enum_int_pair (const SC_ENUM_INT_PAIR *ptr_pairs, int num_pairs, char * str_action, int len)
{
  int index;
  for (index = 0; index < num_pairs; index ++)
  {
    if (!strnicmp (ptr_pairs[index].str_name, str_action, len))
    {
      return ptr_pairs[index].value;
    }
  }
  printf ("Not able to find int for enum\r\n");
  return -1;
}

int get_action_enum_value (char * str_action, int len)
{
  return get_int_from_enum_int_pair (sc_resp_action_value_pair_list, SC_RESP_PKT_ACTION_TYPES, str_action, len);
}

int get_read_write_enum_value (char * str_name, int len)
{
  return get_int_from_enum_int_pair (sc_resp_read_write_value_pair_list, SC_RESP_PKT_READ_WRITE_TYPES, str_name, len);
}
int get_true_false_enum_value (char *str, int len)
{
  return get_int_from_enum_int_pair (sc_resp_true_false_pair_list, SC_RESP_PKT_TRUE_FALSE_TYPES, str, len);
}

int get_pending_req_num (char *pending_req, int len)
{
  char *ptr_strtol;
  return (strtol (pending_req, &ptr_strtol, 10));
}

