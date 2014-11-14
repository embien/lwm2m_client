
#include <lwm2m_client.h> 
#define XOR_APP_STATE_IDLE						0
#define XOR_APP_STATE_DEV_REGISTERATION			1
#define XOR_APP_STATE_DEV_DATA_UPDATE			2
#define XOR_APP_STATE_WAIT_FOR_PENDING_REQ		3
#define XOR_APP_STATE_READ_PENDING_REQ			4
#define XOR_APP_STATE_WRITE_ON_DEVICE			5
#define XOR_APP_STATE_DELETE_REQUEST			6
#define XOR_APP_STATE_ERROR						7

//#define TRAIL_STATE   8

//#define XOR_INPUT1_TIMEOUT_MSEC	  5000
//#define XOR_OUTPUT_TIMEOUT_MSEC	  20000

//#define LWM2M_XOR_IN_OBJECT_ID 3200
//#define LWM2M_XOR_RESOURCE_ID  5500

void xor_app_update_value ();
int sc_last_command_result();
int print_last_cmd_result (int last_cmd);

int dev_dig_out_oper_dig_output_state(INT16S , INT8U , void *);
int dev_dig_in_oper_dig_input_state (INT16S, INT8U, void*);

typedef struct __xor_packet_info
{
  SC_PKT_COMMON_RESP_INFO info_common_resp;
  SC_PKT_DEV_REG_RESP_INFO info_dev_reg_resp;
  SC_PKT_DATA_WRITE_REQ info_data_write_req;
  SC_PKT_DATA_WRITE_RESP info_data_write_resp;
  SC_PKT_DATA_READ_REQ info_data_read_req;
  SC_PKT_DATA_READ_RESP info_data_read_resp;
  SC_PKT_READ_PENDING_REQ_RESP info_pending_req_resp;
  SC_PKT_DEL_PENDING_REQUESTS_REQ info_del_req_req;
  SC_PKT_DEL_PENDING_REQUESTS_RESP info_del_req_resp;
} XOR_PACKET_INFO;

XOR_PACKET_INFO xor_packet_info;

int con_app_last_cmd;
INT8U u8_wait_for_cmd_completion = 0;
INT16U u16_wait_for_timeout = 0;

SKYCASE_XOR_OPER xor_operation;

INT8U u8_xor_task_state = 0;

INT8U u8_digital_output = 0;
INT8U u8_digital_input1 = 0;
INT8U u8_digital_input2 = 0;
 
LWM2M_OBJECT_RES_INFO user_dev_dig_out_res_info [LWM2M_USER_DEV_DIG_OUT_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_DIG_OUTPUT_STATE),
    dev_dig_out_oper_dig_output_state
  }
};
 
LWM2M_OBJECT_RES_INFO user_dev_dig_in_res_info [LWM2M_USER_DEV_DIG_IN_RES_MAX] = 
{
  {
    LWM2M_RES_PROP(LW_RES_DIG_INPUT_STATE),
    dev_dig_in_oper_dig_input_state
  }
};

int dev_dig_out_oper_dig_output_state(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    *((INT8U*)ptr_value) = u8_digital_output;
  }
  else if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    u8_digital_output =*((INT8U*)ptr_value);
  }
  return 0;
}

int dev_dig_in_oper_dig_input_state(INT16S u16_inst_id, INT8U u8_oper, void *ptr_value)
{
  if (u8_oper == LWM2M_RESOURCE_OPERATION_READ)
  {
    if (u16_inst_id == 0)
	{
      u8_digital_input1 = rand() % 2;
      *((INT8U*)ptr_value) = u8_digital_input1;
	}
    else if (u16_inst_id == 1)
	{
      u8_digital_input2 = rand() % 2;
      *((INT8U*)ptr_value) = u8_digital_input2;
	}
	else 
    {
      printf ("XOR Demo : Read Digital Input State. Error - Unknown instance state\n\r");
      *((INT8U*)ptr_value) = 0;
    }
  }
  if (u8_oper == LWM2M_RESOURCE_OPERATION_WRITE)
  {
    if (u16_inst_id == 0)
	{
      u8_digital_input1 = *((INT8U*)ptr_value);
	}
    else if (u16_inst_id == 1)
	{
      u8_digital_input2 = *((INT8U*)ptr_value);
	}
	else 
    {
      printf ("XOR Demo : Write Digital Input State. Error - Unknown instance state\n\r");
    }
    
  }
  return 0;
}

int init_xor_app_task ()
{
  return 0;
}

void xor_app_task ()
{
  int index;
  SC_PKT_DEV_REG_RESP_INFO *ptr_dev_reg_resp;
  SC_PKT_DATA_WRITE_REQ  *ptr_data_write_req_info;
  SC_PKT_DATA_WRITE_RESP  *ptr_data_write_resp_info;
  SC_PKT_READ_PENDING_REQ_RESP *ptr_pending_req_read_resp_info;  
  SC_PKT_DEL_PENDING_REQUESTS_REQ *ptr_del_pending_req_info; 
  SC_PKT_DEL_PENDING_REQUESTS_RESP *ptr_del_pending_resp_info;
  LWM2M_PROCESS_INFO ptr_proc_req;

  if (u8_wait_for_cmd_completion)
  {
    if (sc_get_last_cmd_result ())
    {
      return;
    }
	u8_wait_for_cmd_completion = 0;
    if (con_app_last_cmd)
    {
      print_last_cmd_result (con_app_last_cmd);
      con_app_last_cmd = 0;
    }
    return;
  }

  if (u16_wait_for_timeout) 
  {
    if (GetCurrentTime() >= (xor_operation.resp_time_out_inst0 + u16_wait_for_timeout))
    {
      xor_operation.resp_time_out_inst0 = GetCurrentTime();
	  u16_wait_for_timeout = 0;
    }
	return;
  }

  switch (u8_xor_task_state)
  {
    case XOR_APP_STATE_IDLE:
	case XOR_APP_STATE_DEV_REGISTERATION:
    {
	  xor_operation.resp_time_out_inst0 = GetCurrentTime();
      xor_operation.resp_time_out_inst1 = GetCurrentTime();

	  ptr_dev_reg_resp = &xor_packet_info.info_dev_reg_resp;
      sc_set_resp_pkt_info (ptr_dev_reg_resp, sizeof(SC_PKT_DEV_REG_RESP_INFO));
      sc_set_command (SC_CMD_DEVICE_REGISTER, NULL);
	  con_app_last_cmd = SC_CMD_DEVICE_REGISTER;

	  u16_wait_for_timeout = 5000;
      u8_xor_task_state = XOR_APP_STATE_DEV_DATA_UPDATE;
	  u8_wait_for_cmd_completion = 1;
      break;
  	}
	case XOR_APP_STATE_DEV_DATA_UPDATE:
    {
      ptr_data_write_req_info = &xor_packet_info.info_data_write_req;
	  ptr_data_write_resp_info = &xor_packet_info.info_data_write_resp;
      memset (ptr_data_write_resp_info, 0, sizeof (SC_PKT_DATA_WRITE_RESP));
      memset (ptr_data_write_req_info, 0, sizeof (SC_PKT_DATA_WRITE_REQ));
      sc_set_resp_pkt_info (ptr_data_write_resp_info, sizeof(SC_PKT_DATA_WRITE_RESP));
      sc_req_add_data_write (ptr_data_write_req_info, 3200, 0, 5500);
	  sc_req_add_data_write (ptr_data_write_req_info, 3200, 1, 5500);
      sc_set_command (SC_CMD_DATA_WRITE, ptr_data_write_req_info);
      con_app_last_cmd = SC_CMD_DATA_WRITE;

      u8_xor_task_state = XOR_APP_STATE_WAIT_FOR_PENDING_REQ;
	  u8_wait_for_cmd_completion = 1;
      break;
	}
	case XOR_APP_STATE_WAIT_FOR_PENDING_REQ:
	{
      if (xor_packet_info.info_data_write_resp.common_info.u8_pending_request)
      {
        u8_xor_task_state = XOR_APP_STATE_READ_PENDING_REQ;
        xor_packet_info.info_data_write_resp.common_info.u8_pending_request = 0;
      }
      else
      {
        u16_wait_for_timeout = 5000;
      }
	  break;
	}
	case XOR_APP_STATE_READ_PENDING_REQ:
	{ 
      ptr_pending_req_read_resp_info = &xor_packet_info.info_pending_req_resp;
      memset (ptr_pending_req_read_resp_info, 0, sizeof (SC_PKT_READ_PENDING_REQ_RESP));
      sc_set_resp_pkt_info (ptr_pending_req_read_resp_info, sizeof(SC_PKT_READ_PENDING_REQ_RESP));
      sc_set_command (SC_CMD_READ_PENDING_REQUESTS, NULL);
      con_app_last_cmd = SC_CMD_READ_PENDING_REQUESTS;

	  u8_xor_task_state = XOR_APP_STATE_WRITE_ON_DEVICE;
	  u8_wait_for_cmd_completion = 1;
	  break;
	}
    case XOR_APP_STATE_WRITE_ON_DEVICE:
    {
      ptr_pending_req_read_resp_info = &xor_packet_info.info_pending_req_resp;
      ptr_proc_req.u8_request = LWM2M_PROCESS_REQ_WRITE;
      ptr_proc_req.u8_num_path_elements = 3;
      for (index = 0; index < ptr_pending_req_read_resp_info->arr_info.num_arr_items; index ++)
	  {
        ptr_proc_req.object_path [LWM2M_PATH_INDEX_OBJECT] = ptr_pending_req_read_resp_info->req_info [index].u16_obj_id;
        ptr_proc_req.object_path [LWM2M_PATH_INDEX_INST] = ptr_pending_req_read_resp_info->req_info [index].u16_inst_id;
        ptr_proc_req.object_path [LWM2M_PATH_INDEX_RES] = ptr_pending_req_read_resp_info->req_info [index].u16_res_id;
		strcpy (ptr_proc_req.value, &ptr_pending_req_read_resp_info->req_info [index].u8_value);
        lwm2m_process_request_obj (&ptr_proc_req);
	  }		
      u8_xor_task_state = XOR_APP_STATE_DELETE_REQUEST;
      break;
	}
	case XOR_APP_STATE_DELETE_REQUEST:
	{   
      ptr_pending_req_read_resp_info = &xor_packet_info.info_pending_req_resp;
      ptr_del_pending_req_info = &xor_packet_info.info_del_req_req;
	  ptr_del_pending_resp_info = &xor_packet_info.info_del_req_resp;
      memset (ptr_del_pending_req_info, 0, sizeof (SC_PKT_DEL_PENDING_REQUESTS_REQ));
      for (index = 0; index < ptr_pending_req_read_resp_info->arr_info.num_arr_items; index ++)
      {
        sc_req_add_del_pending_req (ptr_del_pending_req_info,\
                 ptr_pending_req_read_resp_info->req_info [index].u32_req_id, 0);
      }
      memset (ptr_del_pending_resp_info, 0, sizeof (SC_PKT_DEL_PENDING_REQUESTS_RESP));
      sc_set_resp_pkt_info (ptr_del_pending_resp_info, sizeof(SC_PKT_DEL_PENDING_REQUESTS_RESP));
      sc_set_command (SC_CMD_DEL_PENDING_REQUESTS, ptr_del_pending_req_info);
      con_app_last_cmd = SC_CMD_DEL_PENDING_REQUESTS;

	  u16_wait_for_timeout = 10000;
      u8_xor_task_state = XOR_APP_STATE_DEV_DATA_UPDATE;
	  u8_wait_for_cmd_completion = 1;
      break;
    }
    default:
	{
	  printf ("Unknown XOR state\n\r");
	  break;
	}
  }
}


int print_last_cmd_result (int last_cmd)
{
  int index;
  SC_RES_INFO *ptr_res_info;
  SC_RES_VALUE_INFO *ptr_res_value_info;
  SC_PENDING_REQ_INFO *ptr_pending_req_info;
  SC_DEL_PENDING_REQ_INFO *ptr_del_pending_req_info;
  if (last_cmd == SC_CMD_DEVICE_REGISTER)
  {
    printf ("Device Registered\r\n");
	printf ("S.No   ObjID  Inst ID  Res ID   Status\r\n");
	for (index = 0; index < xor_packet_info.info_dev_reg_resp.arr_info.num_arr_items; index ++)
    {
      ptr_res_info = &xor_packet_info.info_dev_reg_resp.res_info [index];
      printf ("%d   %d      %d       %d        %d\r\n", index + 1, ptr_res_info->u16_obj_id, \
              ptr_res_info->u16_inst_id, ptr_res_info->u16_res_id, ptr_res_info->u16_status);
    }
  }
  else if (last_cmd == SC_CMD_READ_PENDING_REQUESTS)
  {
    printf ("Requests Read\r\n");
	printf ("S.No  ReqID   ObjID  Inst ID  Res ID   Status  Value    Type\r\n");
    for (index = 0; index < xor_packet_info.info_pending_req_resp.arr_info.num_arr_items; index ++)
    {
      ptr_pending_req_info = &xor_packet_info.info_pending_req_resp.req_info [index];
      printf ("%d   %d      %d       %d        %d  %d  \"%s\"     %s\r\n", index + 1, ptr_pending_req_info->u32_req_id, \
              ptr_pending_req_info->u16_obj_id, ptr_pending_req_info->u16_inst_id, ptr_pending_req_info->u16_res_id, 
              ptr_pending_req_info->u16_status, ptr_pending_req_info->u8_value, ptr_pending_req_info->u8_type ? "Write" : "Read");
    }
    printf ("Write Value Digital Input1 - %d\r\n", u8_digital_input1);
    printf ("Write Value Digital Input2 - %d\r\n", u8_digital_input2);
  }
  else if (last_cmd == SC_CMD_DEL_PENDING_REQUESTS)
  {
    printf ("Requests Deleted\r\n");
	printf ("S.No  ReqID   Status\r\n");
    for (index = 0; index < xor_packet_info.info_del_req_resp.arr_info.num_arr_items; index ++)
    {
      ptr_del_pending_req_info = &xor_packet_info.info_del_req_resp.req_info [index];
	  printf ("%d   %d	%d\r\n", index + 1, ptr_del_pending_req_info->u32_req_id, \
		  ptr_del_pending_req_info->u16_status);
    }
    printf ("Write Value Digital Input1 - %d\r\n", u8_digital_input1);
    printf ("Write Value Digital Input2 - %d\r\n", u8_digital_input2);
    printf ("Read Value Digital Output - %d\r\n", u8_digital_output);
  }
  else if (last_cmd == SC_CMD_DATA_WRITE)
  {
    printf ("Data Written\r\n");
	printf ("S.No  ObjID  InstID   ResID   Status	Value\r\n");
    for (index = 0; index < xor_packet_info.info_data_write_resp.arr_info.num_arr_items; index ++)
    {
      ptr_res_info = &xor_packet_info.info_data_write_resp.res_info [index];
      printf ("%d		%d  %d  %d  %d		%d\r\n", index + 1, ptr_res_info->u16_obj_id, \
              ptr_res_info->u16_inst_id, ptr_res_info->u16_res_id, ptr_res_info->u16_status, \
			  (index == 0) ? u8_digital_input1 : u8_digital_input2);
    }
	if (xor_packet_info.info_data_write_resp.common_info.u8_pending_request) 
      printf ("Pending Requests Available. \r\n");
	else
      printf ("No Pending Requests. \r\n");

  }
  else if (last_cmd == SC_CMD_DATA_READ)
  {
    printf ("Data Read\r\n");
	printf ("S.No  ObjID  InstID   ResID   Time   Value\r\n");
	
    for (index = 0; index < xor_packet_info.info_data_read_resp.arr_info.num_arr_items; index ++)
    {
      ptr_res_value_info = &xor_packet_info.info_data_read_resp.res_info [index];
      printf ("%d   %d  %d  %d  %d	%s\r\n", index + 1, ptr_res_value_info->u16_obj_id, \
              ptr_res_value_info->u16_inst_id, ptr_res_value_info->u16_res_id, ptr_res_value_info->u16_status, 
              ptr_res_value_info->value);
    }
  }
  return 0;
}