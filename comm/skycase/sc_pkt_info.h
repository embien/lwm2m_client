/*! \file 
  \brief    Header implementing neccessary declarations for HTTP message packet information 
  
  Contains macros, structures and declarations for HTTP message packet information
*/

#ifndef SC_PKT_INFO_H
#define SC_PKT_INFO_H







#define SC_RESP_DEV_LIST_REG_TRUE                     "true"
#define SC_RESP_DEV_LIST_REG_FALSE                   "false"
#define SC_RES_INFO_UPDATE_REQ_TYPE_WRITE            "write"
#define SC_RES_INFO_UPDATE_REQ_TYPE_READ             "read"
#define SC_RESP_APP_LIST_RUNNING_STATUS_TRUE         "true"
#define SC_RESP_APP_LIST_RUNNING_STATUS_FALSE        "false"
#define SC_RESP_CREATED_EVENTS_ENABLE_FALSE          "false"
#define C_RESP_CREATED_EVENTS_ENABLE_TRUE            "true"
#define SC_RESP_CREATED_EVENTS_PENDING_FALSE          "false"
#define SC_RESP_CREATED_EVENTS_PENDING_TRUE            "true"

#define STRUCT_MEMBER_POS(s,m)	((int)(&(((s*)NULL)->m)))

#define SC_MAX_NUM_KEY_TYPES						14
//extern const SC_KEY_INFO sc_key_info_list[SC_MAX_NUM_KEY_TYPES];
//extern int sc_process_http_response (SC_LWM2M_HTTP_COMM *);


//temp

//extern SC_PACKET_INFO karthik_resp;


#endif
