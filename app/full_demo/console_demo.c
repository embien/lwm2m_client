/*! \file 
  \brief      Module implementing console application for user interaction 
 
  Contains the logic for console appearance 
*/

#include <lwm2m_client.h>
#include "user_dev_dig_in.h"
#include "user_dev_dig_out.h"


/*! structure declaration for console application*/
CONSOLE_DEMO_APP console_app;
int con_app_last_cmd;

#include "user_dev_dig_in.c"
#include "user_dev_dig_out.c"
int get_int_input ();


/*! \fn        int GetOption ()
    \brief     To get the user input as charecter
    \param[in] None 
    \return    int     Charecter on success  or zero on failure
*/
int GetOption ()
{
  if (_kbhit ())
    return tolower (_getch ());
  return -1;
}

/*! \fn        void print_help_menu ()
    \brief     To print the help menu to select the options of  HTTP/TCP client process 
    \param[in] None 
    \return    None 
*/
void print_help_menu ()
{
  printf ("%s\r\n", "R: Register the device to Skycase\r\nU: Unregister the device from Skycase\r\nW: Write data\r\nL: List the Registered device \r\nQ: Pending request\r\nD: Delete Pending Request\r\nS: Listing Data\r\nC: Delete Data\r\nX: Read Created Events\r\nY: Read Pending Events\r\nZ: Delete Pending Events\r\nA  List available applications\r\nE Exit Application");
  printf ("press 'h' for help\r\n");
}

int init_console_app_task ()
{
  print_help_menu();
  return 0;
}

SC_PKT_DEV_LIST_RESP_INFO con_app_dev_list_info;
SC_PKT_DEV_REG_RESP_INFO con_app_reg_resp_info;
SC_PKT_DEV_UNREG_REQ_INFO con_app_unreg_req_info;
SC_PKT_DEV_UNREG_RESP_INFO con_app_unreg_resp_info;
SC_PKT_DATA_WRITE_REQ  con_app_data_write_req_info;
SC_PKT_DATA_WRITE_RESP  con_app_data_write_resp_info;
SC_PKT_DATA_READ_REQ  con_app_data_read_req_info;
SC_PKT_DATA_READ_RESP  con_app_data_read_resp_info;
SC_PKT_DATA_DEL_REQ  con_app_data_del_req_info;
SC_PKT_DATA_DEL_RESP  con_app_data_del_resp_info;
SC_PKT_READ_PENDING_REQ_RESP con_app_pending_req_read_resp_info;
SC_PKT_DEL_PENDING_REQUESTS_REQ con_app_del_pending_req_info;
SC_PKT_DEL_PENDING_REQUESTS_RESP con_app_del_pending_resp_info;
SC_PKT_APP_LIST_RESP_INFO con_app_applications_list_resp_info;
SC_PKT_ALL_EVENTS_REQ con_app_read_events_req_info;
SC_PKT_EVENT_LIST_RESP_INFO con_app_read_events_resp_info;
SC_PKT_PENDING_EVENT_RESP_INFO con_app_pending_events_resp_info;
SC_PKT_CLEAR_EVENTS_REQ con_app_clear_events_req_info;
SC_PKT_CLEAR_EVENTS_RESP con_app_clear_events_resp_info;
/*SC_PACKET_INFO console_app_resp_info;

SC_PACKET_INFO * console_app_begin_prepare_req ()
{
  memset (&console_app_resp_info, 0, sizeof(console_app_resp_info)); 
  return &console_app_resp_info;
}*/

/*! \fn        int handle_console_ip (INT8U u8_input)
    \brief     Handle the current command given by user for HTTP/TCP client 
    \param[in] u8_input  Command of the user 
    \return    int  Zero on success or error code on failure
*/
int handle_console_input (INT8U u8_input)
{  
  int index, app_id, obj_id, inst_id, res_id, timestamp;
  switch (u8_input)
  {
    case 'h':
    {
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
      print_help_menu ();
#else
      print_help_menu_coap();
#endif       
      break;
    }
    case 'e':
    {
      exit (0);
      break;
    }
    
    case 'l':
    {
      memset (&con_app_dev_list_info, 0, sizeof(con_app_dev_list_info));
      sc_set_resp_pkt_info (&con_app_dev_list_info, sizeof (con_app_dev_list_info));
      sc_set_command (SC_CMD_READ_DEVICE_LIST, NULL);
      con_app_last_cmd = SC_CMD_READ_DEVICE_LIST;
     break;
    }
    case 'r':
    {
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
      sc_set_resp_pkt_info (&con_app_reg_resp_info, sizeof (con_app_reg_resp_info));
      sc_set_command (SC_CMD_DEVICE_REGISTER, NULL);
      con_app_last_cmd = SC_CMD_DEVICE_REGISTER;
#else
      lwm2m_connect();
#endif
      break;
    }
    case 'u':
    {
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
      printf ("Enter the Object ID \r\n");
      obj_id = get_int_input ();
      if (obj_id <= 0)
      {
        printf ("Invalid Object ID. Please try again\r\n");
        break;
      }
      printf ("Enter the Instance ID \r\n");
      inst_id = get_int_input ();
      if (inst_id < 0)
      {
        printf ("Invalid Instance ID. Please try again\r\n");
        break;
      }
      con_app_unreg_req_info.u16_obj_id = obj_id;
      con_app_unreg_req_info.u16_inst_id = inst_id;
      memset (&con_app_unreg_resp_info, 0, sizeof (con_app_unreg_resp_info));
      sc_set_resp_pkt_info (&con_app_unreg_resp_info, sizeof (con_app_unreg_resp_info));
      sc_set_command (SC_CMD_DEVICE_UNREGISTER, &con_app_unreg_req_info);
      con_app_last_cmd = SC_CMD_DEVICE_UNREGISTER;
#else
      lwm2m_disconnect();
#endif
      break;
    }
    case 'w':
    {
      printf ("Enter the Object ID \r\n");
      obj_id = get_int_input ();
      if (obj_id <= 0)
      {
        printf ("Invalid Object ID. Please try again\r\n");
        break;
      }
      printf ("Enter the Instance ID \r\n");
      inst_id = get_int_input ();
      if (inst_id < 0)
      {
        printf ("Invalid Instance ID. Please try again\r\n");
        break;
      }
      printf ("Enter the Resource ID \r\n");
      res_id = get_int_input ();
      if (res_id < 0)
      {
        printf ("Invalid Instance ID. Please try again\r\n");
        break;
      }
      memset (&con_app_data_write_resp_info, 0, sizeof (con_app_data_write_resp_info));
      memset (&con_app_data_write_req_info, 0, sizeof (con_app_data_write_req_info));
      sc_set_resp_pkt_info (&con_app_data_write_resp_info, sizeof(con_app_data_write_resp_info));
      sc_req_add_data_write (&con_app_data_write_req_info, obj_id, inst_id, res_id);
      sc_set_command (SC_CMD_DATA_WRITE, &con_app_data_write_req_info);
      con_app_last_cmd = SC_CMD_DATA_WRITE;
      break;
    }
    case 's':
    {
      printf ("Enter the Object ID (or negative value to skip)\r\n");
      obj_id = get_int_input ();
      if (obj_id <= 0)
      {
        printf ("Reading all objects\r\n");
        goto read_data;
      }
      printf ("Enter the Instance ID  (or negative value to skip)\r\n");
      inst_id = get_int_input ();
      if (inst_id < 0)
      {
        printf ("Reading all instances\r\n");
        goto read_data;
      }
      printf ("Enter the Resource ID  (or negative value to skip)\r\n");
      res_id = get_int_input ();
      if (res_id < 0)
      {
        printf ("Reading all resources\r\n");
        goto read_data;
      }
      printf ("Enter the Timestamp (or negative value to skip)\r\n");
      timestamp = get_int_input ();
      if (timestamp < 0)
      {
        printf ("Reading data at all times\r\n");
        goto read_data;
      }
      read_data:
      memset (&con_app_data_read_req_info, 0, sizeof (con_app_data_read_req_info));
      memset (&con_app_data_read_resp_info, 0, sizeof (con_app_data_read_resp_info));
      sc_set_resp_pkt_info (&con_app_data_read_resp_info, sizeof(con_app_data_read_resp_info));
      if (obj_id < 0)
        sc_req_set_data_read_all (&con_app_data_read_req_info);
      else if (inst_id < 0)
        sc_req_set_data_read_obj (&con_app_data_read_req_info, obj_id);
      else if (res_id < 0)
        sc_req_set_data_read_inst (&con_app_data_read_req_info, obj_id, inst_id);
      else if (timestamp < 0)
        sc_req_set_data_read_res (&con_app_data_read_req_info, obj_id, inst_id, res_id);
      else 
        sc_req_set_data_read_time (&con_app_data_read_req_info, obj_id, inst_id, res_id, timestamp);
      sc_set_command (SC_CMD_DATA_READ, &con_app_data_read_req_info);
      con_app_last_cmd = SC_CMD_DATA_READ;
      break;
    }
    case 'c':
    {
      printf ("Enter the Object ID (or negative value to skip)\r\n");
      obj_id = get_int_input ();
      if (obj_id <= 0)
      {
        printf ("Deleting all objects\r\n");
        goto del_data;
      }
      printf ("Enter the Instance ID  (or negative value to skip)\r\n");
      inst_id = get_int_input ();
      if (inst_id < 0)
      {
        printf ("Deleting all instances\r\n");
        goto del_data;
      }
      printf ("Enter the Resource ID  (or negative value to skip)\r\n");
      res_id = get_int_input ();
      if (res_id < 0)
      {
        printf ("Deleting all resources\r\n");
        goto del_data;
      }
      printf ("Enter the Timestamp (or negative value to skip)\r\n");
      timestamp = get_int_input ();
      if (timestamp < 0)
      {
        printf ("Deletings data at all times\r\n");
        goto del_data;
      }
      del_data:
      memset (&con_app_data_del_req_info, 0, sizeof (con_app_data_del_req_info));
      memset (&con_app_data_del_resp_info, 0, sizeof (con_app_data_del_resp_info));
      sc_set_resp_pkt_info (&con_app_data_del_resp_info, sizeof(con_app_data_del_resp_info));
      if (obj_id < 0)
        sc_req_set_data_del_all (&con_app_data_del_req_info);
      else if (inst_id < 0)
        sc_req_set_data_del_obj (&con_app_data_del_req_info, obj_id);
      else if (res_id < 0)
        sc_req_set_data_del_inst (&con_app_data_del_req_info, obj_id, inst_id);
      else if (timestamp < 0)
        sc_req_set_data_del_res (&con_app_data_del_req_info, obj_id, inst_id, res_id);
      else 
        sc_req_set_data_del_time (&con_app_data_del_req_info, obj_id, inst_id, res_id, timestamp);
      sc_set_command (SC_CMD_DATA_DELETE, &con_app_data_del_req_info);
      con_app_last_cmd = SC_CMD_DATA_DELETE;
      break;
    }
    case 'q':
    {
      memset (&con_app_pending_req_read_resp_info, 0, sizeof (con_app_pending_req_read_resp_info));
      sc_set_resp_pkt_info (&con_app_pending_req_read_resp_info, sizeof(con_app_pending_req_read_resp_info));
      sc_set_command (SC_CMD_READ_PENDING_REQUESTS, NULL);
      con_app_last_cmd = SC_CMD_READ_PENDING_REQUESTS;
      break;
    }
    case 'd':
    {
      memset (&con_app_del_pending_req_info, 0, sizeof (con_app_del_pending_req_info));
      for (index = 0; index < con_app_pending_req_read_resp_info.arr_info.num_arr_items; index ++)
      {
        sc_req_add_del_pending_req (&con_app_del_pending_req_info,\
                 con_app_pending_req_read_resp_info.req_info [index].u32_req_id, 0);
      }
      memset (&con_app_del_pending_resp_info, 0, sizeof (con_app_del_pending_resp_info));
      sc_set_resp_pkt_info (&con_app_del_pending_resp_info, sizeof(con_app_del_pending_resp_info));
      sc_set_command (SC_CMD_DEL_PENDING_REQUESTS, &con_app_del_pending_req_info);
      con_app_last_cmd = SC_CMD_DEL_PENDING_REQUESTS;
      break;
    } 
    case 'a':
    {
      memset (&con_app_applications_list_resp_info, 0, sizeof (con_app_applications_list_resp_info));
      sc_set_resp_pkt_info (&con_app_applications_list_resp_info, sizeof (con_app_applications_list_resp_info));
      sc_set_command (SC_CMD_READ_APPLICATIONS_LIST, NULL);
      con_app_last_cmd = SC_CMD_READ_APPLICATIONS_LIST;
      break;
    }
    case 'x':
    {
      printf ("Enter the application ID \r\n");
      app_id = get_int_input ();
      if (app_id <= 0)
      {
        printf ("Invalid Application ID. Please try again\r\n");
        break;
      }
      memset (&con_app_read_events_resp_info, 0, sizeof (con_app_read_events_resp_info));
      con_app_read_events_req_info.u32_app_id = app_id;
      sc_set_resp_pkt_info (&con_app_read_events_resp_info, sizeof (con_app_read_events_resp_info));
      sc_set_command (SC_CMD_READ_ALL_EVENTS, &con_app_read_events_req_info);
      con_app_last_cmd = SC_CMD_READ_ALL_EVENTS;
      break;
    }
    case 'y':
    {
      printf ("Enter the application ID \r\n");
      app_id = get_int_input ();
      if (app_id <= 0)
      {
        printf ("Invalid Application ID. Please try again\r\n");
        break;
      }
      memset (&con_app_pending_events_resp_info, 0, sizeof (con_app_pending_events_resp_info));
      con_app_read_events_req_info.u32_app_id = app_id;
      sc_set_resp_pkt_info (&con_app_pending_events_resp_info, sizeof (con_app_pending_events_resp_info));
      sc_set_command (SC_CMD_READ_PENDING_EVENTS, &con_app_read_events_req_info);
      con_app_last_cmd = SC_CMD_READ_PENDING_EVENTS;
      break;
    }
    case 'z':
    {
      memset (&con_app_clear_events_req_info, 0, sizeof (con_app_clear_events_req_info));
      sc_req_set_clear_pending_event_app_id (&con_app_clear_events_req_info,\
                    con_app_pending_events_resp_info.u32_app_id);
      for (index = 0; index < con_app_pending_events_resp_info.arr_info.num_arr_items; index ++)
      {
        sc_req_add_clear_pending_event (&con_app_clear_events_req_info,\
                 con_app_pending_events_resp_info.event_info [index].u16_event_id, \
                 con_app_pending_events_resp_info.event_info [index].u32_event_count);
      }
      sc_set_command (SC_CMD_CLEAR_PENDING_EVENTS, &con_app_clear_events_req_info);
      con_app_last_cmd = SC_CMD_CLEAR_PENDING_EVENTS;
      break;
    }
    
#if 0
    
    case 'p':
    {
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
      print_setting ();
#else
      print_setting_coap();
#endif   
      break;
    }
    case 'm':
    {
      modify_resource_value();
      break;
    }
#endif
    default:
    {
      printf ("Enter valid options from the above list\r\n");
      break;
    }
  }
  return 0;
}

int print_last_cmd_result (int last_cmd)
{
  int index;
  SC_PKT_DEV_LIST_INFO *ptr_dev_info;
  SC_RES_INFO *ptr_res_info;
  SC_RES_VALUE_INFO *ptr_res_value_info;
  SC_PENDING_REQ_INFO *ptr_pending_req_info;
  SC_DEL_PENDING_REQ_INFO *ptr_del_pending_req_info;
  SC_PKT_APP_LIST_INFO *ptr_app_info;
  SC_PKT_EVENT_INFO *ptr_event_info;
  SC_PENDING_EVENT_INFO *ptr_pending_event_info;
  if (last_cmd == SC_CMD_READ_DEVICE_LIST)
  {
    printf ("Number of Devices available is %d :\r\n", con_app_dev_list_info.u16_num_devices);
    printf ("S.No   ObjID  Inst ID Dev Desc         User Desc          Registered\r\n");
    for (index = 0; index < con_app_dev_list_info.arr_info.num_arr_items; index ++)
    {
      ptr_dev_info = &con_app_dev_list_info.dev_info [index];
      printf ("%d  %d      %d       %s            %s             %s\r\n", index + 1, ptr_dev_info->u16_obj_id, \
              ptr_dev_info->u16_inst_id, ptr_dev_info->u8_dev_desc, ptr_dev_info->u8_user_desc, \
              ptr_dev_info->u16_reg_status ? "Yes" : "No");
    }
  }
  else if (last_cmd == SC_CMD_DEVICE_REGISTER)
  {
    printf ("Device Registered\r\n");
    printf ("S.No   ObjID  Inst ID  Res ID   Status\r\n");
    for (index = 0; index < con_app_reg_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_res_info = &con_app_reg_resp_info.res_info [index];
      printf ("%d   %d      %d       %d        %d\r\n", index + 1, ptr_res_info->u16_obj_id, \
              ptr_res_info->u16_inst_id, ptr_res_info->u16_res_id, ptr_res_info->u16_status);
    }
  }
  else if (last_cmd == SC_CMD_DEVICE_UNREGISTER)
  {
    printf ("Device %s unregistered with status %d\r\n", con_app_unreg_resp_info.device_path, con_app_unreg_resp_info.u16_status);
  }
  else if (last_cmd == SC_CMD_READ_PENDING_REQUESTS)
  {
    printf ("Requests Read\r\n");
    printf ("S.No  ReqID   ObjID  Inst ID  Res ID   Status  Value    Type\r\n");
    for (index = 0; index < con_app_pending_req_read_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_pending_req_info = &con_app_pending_req_read_resp_info.req_info [index];
      printf ("%d   %d      %d       %d        %d  %d  %s     %s\r\n", index + 1, ptr_pending_req_info->u32_req_id, \
              ptr_pending_req_info->u16_obj_id, ptr_pending_req_info->u16_inst_id, ptr_pending_req_info->u16_res_id, 
              ptr_pending_req_info->u16_status, ptr_pending_req_info->u8_value, ptr_pending_req_info->u8_type ? "Write" : "Read");
    }
  }
  else if (last_cmd == SC_CMD_DEL_PENDING_REQUESTS)
  {
    printf ("Requests Deleted\r\n");
    /*printf ("S.No  ReqID   ObjID  Inst ID  Res ID   Status  Value    Type\r\n");
    for (index = 0; index < con_app_del_pending_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_del_pending_req_info = &con_app_del_pending_resp_info.req_info [index];
      printf ("%d   %d      %d       %d        %d  %d  %s     %s\r\n", index + 1, ptr_pending_req_info->u32_req_id, \
              ptr_pending_req_info->u16_obj_id, ptr_pending_req_info->u16_inst_id, ptr_pending_req_info->u16_res_id, 
              ptr_pending_req_info->u16_status, ptr_pending_req_info->u8_value, ptr_pending_req_info->u8_type ? "Write" : "Read");
    }*/
  }
  else if (last_cmd == SC_CMD_READ_APPLICATIONS_LIST)
  {
    printf ("Applications Read (%d found)\r\n", con_app_applications_list_resp_info.u16_num_apps);
    printf ("S.No  AppID  Description   Status\r\n");
    for (index = 0; index < con_app_applications_list_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_app_info = &con_app_applications_list_resp_info.app_info [index];
      printf ("%d   %d   %s     %s\r\n", index + 1, ptr_app_info->u16_app_id, \
              ptr_app_info->u8_user_desc, ptr_app_info->u16_running ? "Running" : "Stopped");
    }
  }
  else if (last_cmd == SC_CMD_READ_ALL_EVENTS)
  {
    printf ("Applications Read for app :%d\r\n", con_app_read_events_resp_info.u32_app_id);
    printf ("S.No  EvtID  Type Enabled Pending   Desc   Source   Param1     Param2\r\n");
    for (index = 0; index < con_app_read_events_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_event_info = &con_app_read_events_resp_info.event_info [index];
      printf ("%d   %d   %d  %s   %s  %s %s   %s    %s\r\n", index + 1, ptr_event_info->u16_event_id, \
              ptr_event_info->u16_type, ptr_event_info->u16_enabled ? "Yes" : "No", 
              ptr_event_info->u16_pending ? "Yes" : "No", ptr_event_info->user_desc, \
              ptr_event_info->source, ptr_event_info->parameter1, ptr_event_info->parameter2);
    }
  }
  else if (last_cmd == SC_CMD_READ_PENDING_EVENTS)
  {
    printf ("Applications Read for app :%d\r\n", con_app_pending_events_resp_info.u32_app_id);
    printf ("S.No  EvtID  Type	Count	Source   Param1     Param2\r\n");
    for (index = 0; index < con_app_pending_events_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_pending_event_info = &con_app_pending_events_resp_info.event_info [index];
      printf ("%d   %d   %d  %d   %s  %s %s   \r\n", index + 1, ptr_pending_event_info->u16_event_id, \
		  ptr_pending_event_info->u16_type, ptr_pending_event_info->u32_event_count, \
              ptr_pending_event_info->source, ptr_pending_event_info->parameter1, ptr_pending_event_info->parameter2);
    }
  }
  else if (last_cmd == SC_CMD_DATA_WRITE)
  {
    printf ("Data Written\r\n");
    printf ("S.No  ObjID  InstID   ResID   Status\r\n");
    for (index = 0; index < con_app_data_write_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_res_info = &con_app_data_write_resp_info.res_info [index];
      printf ("%d   %d  %d  %d  %d\r\n", index + 1, ptr_res_info->u16_obj_id, \
              ptr_res_info->u16_inst_id, ptr_res_info->u16_res_id, ptr_res_info->u16_status);
    }
  }
  else if (last_cmd == SC_CMD_DATA_READ)
  {
    printf ("Data Read\r\n");
    printf ("S.No  ObjID  InstID   ResID   Time   Value\r\n");
    for (index = 0; index < con_app_data_read_resp_info.arr_info.num_arr_items; index ++)
    {
      ptr_res_value_info = &con_app_data_read_resp_info.res_info [index];
      printf ("%d   %d  %d  %d  %d	%s\r\n", index + 1, ptr_res_value_info->u16_obj_id, \
              ptr_res_value_info->u16_inst_id, ptr_res_value_info->u16_res_id, ptr_res_value_info->u16_status, 
              ptr_res_value_info->value);
    }
  }
  else if (last_cmd == SC_CMD_DATA_DELETE)
  {
    printf ("Data deleted at path %s\r\n", con_app_data_del_resp_info.data_path);
  }
  
  return 0;
}

/*! \fn        int get_key_cur_state_coap()
    \brief     Get the user current input for CoAP/UDP client and handle the command  
    \param[in] None 
    \return    int  Zero on success or error code on failure
*/
int console_app_task ()
{
  int input;
  if (sc_get_last_cmd_result ())
  {
    
    return 0;
  }
  if (con_app_last_cmd)
  {
    print_last_cmd_result (con_app_last_cmd);
    con_app_last_cmd = 0;
  }
  input = GetOption ();
  if(input < 0)
    return -1;
  handle_console_input (input);
  return 0;
}

/*! \fn        int sc_validte_app_id ()
    \brief     Validate the application id
    \param[in] None
    \return    INT16S  convert number on success or error code on failure
*/
int get_int_input ()
{
  INT8U u8_buf [50];
  int ret_value = 0;

  scanf ("%s", u8_buf);
  return atoi (u8_buf);
}

#if SASP
/*! structure delcartion for LWM2M write process */
LWM2M_PROCESS_INFO ptr_write_process;

int handle_console_input(INT8U);
void print_help_menu_coap();
int process_write_to_client();
int get_command ();
int set_cmd (INT8U);
void print_setting_coap();
int sc_validte_app_id ();
int validate_input (INT8U*);



/*! \fn        void print_setting ()
    \brief     To print the configuration setting of the  HTTP/TCP  client 
    \param[in] None 
    \return    None 
*/
void print_setting ()
{
#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
  printf ("%sServer Ip Address:%s \r\nPort No: %s\r\n", "Server: SkyCase-IoT\r\nUser: Embien\r\nCommunication-Mode: Request-Response\r\n", SC_SERVER_IP, SC_SERVER_PORT);
  printf ("press 'h' for help\r\n");
#endif 
}
 
/*! \fn        int get_command ()
    \brief     To get the current command for HTTP response packet preparation 
    \param[in] None 
    \return    int Command on sucess or error code on failure
*/
int get_command ()
{
  return console_app.u8_sc_cmd;
}

/*! \fn        int set_cmd (INT8U u8_cmd)s
    \brief     Add the current command to helps in HTTP response packet preparation  
    \param[in] None 
    \return    int Zero on sucess or error code on failure
*/
int set_cmd (INT8U u8_cmd)
{
  console_app.u8_sc_cmd = u8_cmd;
  return 0;
}

/*! \fn        void reset_cmd ()
    \brief     Reset the command after completion of  HTTP response packet preparation  
    \param[in] None 
    \return    None
*/
void reset_cmd ()
{
  console_app.u8_sc_cmd = 0;
}


/*! \fn        void print_help_menu_coap()
    \brief     To print the help menu to select the options of  CoAP/UDP client process 
    \param[in] None 
    \return    None 
*/
void print_help_menu_coap()
{
  printf ("\r\n%s\r\n", "P: Print Settings\r\nR:Register client\r\nM:Modify data to resource\r\n");
}  

/*! \fn        void print_setting_coap ()
    \brief     To print the configuration setting of the  CoAP/UDP  client 
    \param[in] None 
    \return    None 
*/
void print_setting_coap()
{
  #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
  printf ("Server ip address:%s\r\nconnecting portno:%d\r\n",LWM2M_COAP_UDP_SERVER_IP,LWM2M_COAP_UDP_SERVER_PORT);
  #endif 
}

/*! \fn        int modify_resource_value()
    \brief     Change the IPSO resource value from user input  
    \param[in] None
    \return    int  Zero on success or error code on failure
*/
int modify_resource_value ()
{
  int ret_index, ret_value, res_index, index;
  char *ptr_end, str_value [10];
  INT8U u8_value;
  INT16U obj_id,inst_id, res_id, u16_value;
  INT32U u32_value;
  INT32S s32_value = 0;
  LWM2M_OBJECT_INST_INFO *ptr_instance_info;
  LWM2M_OBJECT_RES_INFO *ptr_obj_res_info;
  LWM2M_RESOURCE_INFO *ptr_res_info; 
  printf ("\r\nEnter object id\n");
  scanf ("%s", str_value);
  u16_value = validate_input (str_value); 
  if (u16_value < 0)
  { 
    printf ("\r\nEnter the integer value \n\r");
    return -1;
  }
  else
  {
    ptr_write_process.object_path[LWM2M_PATH_INDEX_OBJECT] = u16_value;
  ret_index = lwm2m_obj_validate_obj_id  (ptr_write_process.object_path [LWM2M_PATH_INDEX_OBJECT]);
    if (ret_index < 0)
    {
      printf ("\r\nEnter the valid object id \n\r");
      return -1;
    }  
    else
    {
      ptr_write_process.u16_obj_id_index = (INT16S)ret_index;
    }
  }
  printf ("\r\nEnter the instance id\n");
  scanf ("%s", str_value);
  u16_value = validate_input (str_value); 
  if (u16_value < 0)
  { 
    printf ("\r\nEnter the integer value \n\r");
  return -1;
  }
  else
  {
    ptr_write_process.object_path[LWM2M_PATH_INDEX_INST] = u16_value;
    ret_index = lwm2m_obj_validate_inst_id (ptr_write_process.object_path [LWM2M_PATH_INDEX_INST],ptr_write_process.u16_obj_id_index);
    if (ret_index < 0)
    {
      printf ("\r\nEnter the valid instance id \n\r");
      return -1;  
    }
    else
    {
      ptr_write_process.u16_inst_id_index = (INT16S)ret_index;
    }
  }
  printf ("\r\nEnter the resource id\n");
  scanf ("%s", str_value);
  u16_value = validate_input (str_value); 
  if (u16_value < 0)
  { 
    printf ("\r\nEnter the integer value \n\r");
  return -1;
  }
  else
  {
    ptr_write_process.object_path[LWM2M_PATH_INDEX_RES] = u16_value;
    ret_index = lwm2m_obj_validate_res_id (ptr_write_process.object_path [LWM2M_PATH_INDEX_RES],\
    ptr_write_process.u16_inst_id_index, ptr_write_process.u16_obj_id_index);
    if ( ret_index < 0)
    { 
      printf ("\r\nEnter the valid resource id \n\r");
      return 0;  
    }
    else
    {
      ptr_write_process.u16_res_id_index = (INT16S)ret_index;
    }
  return 0;
  }
  printf ("\r\nEnter the value to write \r\n");
  scanf ("%s",ptr_write_process.value);
  ptr_instance_info = supported_object_list [ptr_write_process.u16_obj_id_index].ptr_inst_list;
  ptr_obj_res_info = ptr_instance_info [ptr_write_process.u16_inst_id_index].ptr_res_list;
  ptr_res_info = ptr_obj_res_info [ptr_write_process.u16_res_id_index].ptr_resource_info; 
  obj_id = supported_object_list [ptr_write_process.u16_obj_id_index].u16_obj_id;
  inst_id = ptr_instance_info [ptr_write_process.u16_inst_id_index].u16_inst_id;
  res_index = ptr_write_process.u16_res_id_index;
  res_id = ptr_res_info->u16_res_id;
  if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_BOOL)
  {
    u8_value = (INT8U)strtol ((const char *)ptr_write_process.value, (char **)&ptr_end, (int)10);
    ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_write_process.u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE, &u8_value);  
  } 
  if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_INT)
  {
    u32_value = (INT8U)strtol ((const char *)ptr_write_process.value, (char **)&ptr_end, (int)10);
    ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_write_process.u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE, &u32_value);  
  }
  if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_STR)
  {
    ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_write_process.u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
  ptr_write_process.value);  
  }
  if (ptr_res_info->u8_type == LWM2M_OBJ_RES_TYPE_FRAC)
  {
    #if FIXED_POINT
    (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_write_process.u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
            &ptr_proc_req->value);
    #endif
    #if FLOAT_POINT
  ret_value = (ptr_obj_res_info + res_index)->fn_ptr_res_oper(ptr_write_process.u16_inst_id_index, LWM2M_RESOURCE_OPERATION_WRITE,\
  ptr_write_process.value);
    #endif
  }
  if(ret_value == 0)
  {
    printf ("\r\nValue modified sucessfully\n\r");
    if (LWM2M_CLIENT_SUPPORT_OBSERVE)
  { 
      for (index = 0; index < LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS; index ++)
      {
      if (lwm2m_observed_items[index].u8_observe_state & LWM2M_OBSERVE_OBJECT_ENABLE)
      {
      if (lwm2m_observed_items[index].obj_id == obj_id)
        {
            lwm2m_resource_changed (obj_id, inst_id, res_id);
          }
      }
    }
  }
  }
  else if (ret_value < 0)
  {
    printf ("Value not updated enter the correct value\n\r");
  return 0;
  }
}


/*! \fn        int validate_input (char *str_value)
    \brief     Converts the string into numbers   
    \param[in] None
    \return    INT16U  convert number on success or error code on failure
*/ 
int validate_input (INT8U *str_value)
{
  int index;
  for (index = 0; str_value[index];index ++)
  {
    if (str_value[index] >= 48 &&  str_value[index] <= 57);
    else 
    { 
      return -1;
     }
   }
   return (atoi (str_value));
}

#endif


  
    
 
    

  