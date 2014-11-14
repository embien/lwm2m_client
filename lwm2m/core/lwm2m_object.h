/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M objects ,instances and resources
  
  Contains macros, structures and declarations for LWM2M objects ,instances and resources
*/

#ifndef LWM2M_OBJECT_H
#define LWM2M_OBJECT_H
#include <uno_typedef.h>

#define LWM2M_OBJ_RES_PROP_READ				                    BIT(0) /*!< LWM2M valid bit field for resource property read */
#define LWM2M_OBJ_RES_PROP_WRITE	 			                  BIT(1) /*!< LWM2M valid bit field for resource property write */
#define LWM2M_OBJ_RES_PROP_EXECUTE 				                BIT(2) /*!< LWM2M valid bit field for resource property execute */
#define LWM2M_OBJ_RES_PROP_RESERVED 				              BIT(3) /*!< bit field is reserved for future purpose */
#define LWM2M_OBJECT_RES_PROP_MULTI_INST_YES              BIT(4)  /*!< LWM2M valid bit field for resource property multiple instance */
#define LWM2M_OBJECT_RES_PROP_MULTI_INST_NO               0     /*!<  Resource property with zero multiple instance */

#define LWM2M_RESOURCE_NAME_MAX_LEN                       100 /*!< LWM2M resource name maximum length */
//#define LWM2M_PROC_MAX_STR_LEN                            30  /*!< LWM2M resource property maximum length */
#define LWM2M_OBJ_RES_TYPE_BOOL							              0 /*!< LWM2M resource type boolean */
#define LWM2M_OBJ_RES_TYPE_INT							              1 /*!< LWM2M resource type integer */
#define LWM2M_OBJ_RES_TYPE_STR						                2 /*!< LWM2M resource type string */
#define LWM2M_OBJ_RES_TYPE_FRAC                           3 /*!< LWM2M resource type fraction */
#define LWM2M_OBJ_RES_TYPE_OPAQUE									        4 /*!< LWM2M resource type opaque */                                      

#define LWM2M_OBJ_RES_FORMAT_INT8U						            0xe1 /*!< LWM2M resource format for unsigned 8-bit quantity */                                      
#define LWM2M_OBJ_RES_FORMAT_INT						              0xe4 /*!< LWM2M resource format for unsigned 32-bit quantity */
#define LWM2M_OBJ_RES_FORMAT_STR     					            0xe0 /*!< LWM2M resource format for string */
#define LWM2M_OBJ_RES_FORMAT_FRAC 					            	0xe4 /*!< LWM2M resource format for fraction */
#define LWM2M_OBJ_RES_FORMAT_INT16U						            0xe2 /*!< LWM2M resource format for Unsigned 16-bit quantity */
#define LWM2M_OBJ_RES_FORMAT_INT8S						            0xe1 /*!< LWM2M resource format for Unsigned 8-bit quantity */
#define LWM2M_OBJ_RES_FORMAT_INT16S						            0xe2 /*!< LWM2M resource format for signed 16-bit quantity */
 
#define LWM2M_MAX_PATH_LEN								                3  /*!< LWM2M maximum path length*/
#define LWM2M_MAX_VALUE_LEN							                	250 /*!< LWM2M maximum value length*/
#define LWM2M_PROCESS_REQ_READ						               	0 /*!< LMW2M request for read */
#define LWM2M_PROCESS_REQ_WRITE						              	1 /*!< LMW2M request for write */
#define LWM2M_PROCESS_REQ_EXECUTE									        3 /*!< LMW2M request for execute */
#define LWM2M_PROCESS_RESP_SUCCESS					            	2 /*!< LMW2M response as sucess */
#define LWM2M_PROCESS_RESP_CONTENT						            5 /*!< LMW2M response as content */
#define LWM2M_PROCESS_RESP_CHANGED						            4 /*!< LMW2M response as value changed */
#define LWM2M_PROCESS_RESP_ERROR						              4 /*!< LMW2M response as client error */
#define LWM2M_PROCESS_RESP_SERVER_ERROR						        5 /*!< LMW2M response as server error */
#define LWM2M_PROCESS_RESP_ERR_BAD_REQ					          0 /*!< LMW2M response as bad request */
#define LWM2M_PROCESS_RESP_ERR_NOT_ALLLOWED			         	5 /*!< LMW2M response as not allowed to change value */
#define LWM2M_PROCESS_RESP_ERR_NOT_FOUND				          4 /*!< LMW2M response as not found */

#define LWM2M_PATH_INDEX_OBJECT							              0 /*!< LWM2M path index for the object */
#define LWM2M_PATH_INDEX_INST							                1 /*!< LWM2M path index for the instance */ 
#define LWM2M_PATH_INDEX_RES						                	2 /*!< LWM2M path index for the resource */
#define LWM2M_OBJ_HEADER_TYPE_FIELD                       0xe8 	/*!< LWM2M header type field */
  
#define LWM2M_RESOURCE_OPERATION_READ                     1 /*!< LWM2M resource operation read */  
#define LWM2M_RESOURCE_OPERATION_WRITE                    2 /*!< LWM2M resource operation write */
#define LWM2M_RESOURCE_OPERATION_EXECUTE				          3 /*!< LWM2M resource operation execute */                   

#define LWM2M_MAX_TOKEN_LEN							                	 8 /*!< LWM2M maximum length of the token value */         

#define LWM2M_OBSERVE_OBJECT_ENABLE			BIT(0)               /*!< LWM2M observe object enable */
#define LWM2M_OBSERVE_OBJECT_NOTIFY			BIT(1)               /*!< LWM2M observe object notify */
#define LWM2M_OBSERVE_INSTANCE_NOTIFY		BIT(2)               /*!< LWM2M observe instance notify*/
#define LWM2M_OBSERVE_RESOURCE_NOTIFY   BIT(3)               /*!< LWM2M observe object resource notify */
#define LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER 0x61           /*!< LWM2M observed object resource changed marker */

#define LWM2M_OBJ_INST_STATE_VALID              BIT(0) /*!< LWM2M valid bit field for instance state valid */
#define LWM2M_OBJ_INST_VALID                    1      /*!< LWM2M instance state valid */
#define LWM2M_OBJ_INST_INVALID                  0      /*!< LWM2M instance state invalid */

/*! Structure definition for resource information */
typedef struct __lwm2m_resource_info
{
  INT16U u16_res_id;
  INT8U u8_name [LWM2M_RESOURCE_NAME_MAX_LEN];
  INT8U  u8_prop;
  INT8U  u8_type;
  INT32U min_value;
  INT32U max_value;
} LWM2M_RESOURCE_INFO;

/*! Fucntion pointer declaration for operation of read value */
typedef int (*FN_PTR_RES_OPERATION) (INT16S, INT8U, void *);

/*! Structure  for object resource information */
typedef struct __lwm2m_object_res_info
{
  LWM2M_RESOURCE_INFO *ptr_resource_info;
  FN_PTR_RES_OPERATION fn_ptr_res_oper;
} LWM2M_OBJECT_RES_INFO;

/*! Structure for object instance information */
typedef struct __lwm2m_object_inst_info
{
  INT8U u8_inst_state;
  INT16U u16_inst_id;
  INT8U u8_max_res;
  LWM2M_OBJECT_RES_INFO *ptr_res_list;          
}LWM2M_OBJECT_INST_INFO;

/*! structure for object information */
typedef struct __lwm2m_object_info
{
  INT16U u16_obj_id;
  INT8U u8_max_num_inst;
  LWM2M_OBJECT_INST_INFO *ptr_inst_list;
} LWM2M_OBJECT_INFO;

/*! structure declartion for LWM2M process information */
typedef struct __lwm2m_process_info
{
	INT8U u8_request;
	INT16U object_path [LWM2M_MAX_PATH_LEN];
	INT8U u8_num_path_elements;
	INT8U value [LWM2M_MAX_VALUE_LEN];
	INT8U u8_value_len;
  INT8U u8_resp_code;  /// 2 
	INT8U u8_resp_detail; // .0
	INT16S u16_obj_id_index;
  INT16S u16_inst_id_index;
  INT16S u16_res_id_index;
  INT8U resource_type;  // oma, reusable  //GK
  union resource_value 
  {
	  INT8U u8_value;
	  INT16U u16_value;
	  INT32U u32_value;
	  INT8U str [LWM2M_MAX_VALUE_LEN];
	  FRACTION fraction_value;
	  }res_val;
}LWM2M_PROCESS_INFO;

/*! structure declartion for LWM2M observe information */
typedef struct __lwm2m_observe_info
{
  INT8U u8_token_value [LWM2M_MAX_TOKEN_LEN];
  INT8S u8_token_len;
  INT16U u16_msg_id;
  INT8U u8_notify_count;
  INT16U obj_id;
  INT16U inst_id;
  INT16U res_id;
  INT16S obj_index;
  INT16S inst_index;
  INT16S res_index;
  INT8U u8_valid_locations;
  INT8U u8_observe_state;
} LWM2M_OBSERVE_INFO;

//extern LWM2M_OBSERVE_INFO lwm2m_observed_items [LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS];
//extern LWM2M_OBJECT_INFO supported_object_list [LWM2M_MAX_SUPPORTED_OBJECTS];
extern int lwm2m_obj_validate_obj_id (INT16U );
extern int lwm2m_obj_validate_inst_id (INT16U , int);
extern int lwm2m_obj_validate_res_id (INT16U, int, int);
extern int lwm2m_get_obj_inst_list_for_reg (INT8U*, int);
extern int lwm2m_process_request_obj (LWM2M_PROCESS_INFO *);
extern int lwm2m_resource_changed  (INT16U , INT16S, INT16U);
extern int lwm2m_check_for_observe_notification();


#endif