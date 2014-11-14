/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef SC_PKT_JSON_H
#define SC_PKT_JSON_H

#define SC_KEY_INFO_VALUE_TYPE_ARRAY				  0
#define SC_KEY_INFO_VALUE_TYPE_INT					  1
#define SC_KEY_INFO_VALUE_TYPE_STRING				  2
#define SC_KEY_INFO_VALUE_TYPE_ENUM           3
#define SC_KEY_INFO_VALUE_TYPE_DISCARD        4

typedef struct __sc_key_info
{
  char *str_key_name;
  INT8U u8_value_type;
  int store_offset;
  int max_len;
  void *ptr_misc;
} SC_KEY_INFO;

typedef struct __sc_resp_key_list
{
	const SC_KEY_INFO *ptr_key_list;
	INT8U u8_num_keys;
} SC_RESP_KEY_LIST;


#define SC_MAX_NUM_RESP_TYPES 13

#define SC_RESP_NUM_KEY_TYPE_COMMON               2
#define SC_RESP_NUM_KEY_TYPE_DEV_REG              7
#define SC_RESP_NUM_KEY_TYPE_DATA_WRITE           9
#define SC_RESP_NUM_KEY_TYPE_READ_PEND_REQ        11
#define SC_RESP_NUM_KEY_TYPE_DEV_LIST              10
#define SC_RESP_NUM_KEY_TYPE_APP_LIST         7
#define SC_RESP_NUM_KEY_TYPE_EVENTS_LIST                  11
#define SC_RESP_NUM_KEY_TYPE_PENDING_EVENTS					9
#define SC_RESP_NUM_KEY_TYPE_CLEAR_EVENTS         6
#define SC_RESP_NUM_KEY_TYPE_DEV_DELETE          5 
#define SC_RESP_NUM_KEY_TYPE_DATA_READ           7
#define SC_RESP_NUM_KEY_TYPE_DATA_DELETE           5 
#define SC_RESP_NUM_KEY_TYPE_DEL_PEND_REQ    6

#endif
