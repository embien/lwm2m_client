/*! \file 
  \brief      Module implementing the  IPSO resources information   
 
  Contains the logic for user specific IPSO resources implementation 
*/
#include <lwm2m_client.h>

/*!Macro definition of IPSO resource on/off */ 
DECLARE_RES (LW_RES_ON_OFF, LW_RES_ID_ON_OFF, "On/Off", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_BOOL, \
              0, \
              1);
              
/*! Macro definition of IPSO resource dimmer */
DECLARE_RES (LW_RES_DIMMER, LW_RES_ID_DIMMER, "Dimmer", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_INT, \
              0, \
              100);

/*! Macro definition of IPSO resource set point value */              
DECLARE_RES (LW_RES_SET_POINT_VALUE, LW_RES_ID_SET_POINT_VALUE,  "set_point_value", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              0);
              
/*!Macro  definition of IPSO resource digital input state */              
DECLARE_RES (LW_RES_DIG_INPUT_STATE, LW_RES_ID_DIG_INPUT_STATE,  "digital_input_state", \
              LWM2M_OBJ_RES_PROP_READ  | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_BOOL, \
              0, \
              0);
              
/*! Macro definition of IPSO resource digital output state */             
DECLARE_RES (LW_RES_DIG_OUTPUT_STATE, LW_RES_ID_DIG_OUTPUT_STATE,  "digital_output_state", \
              LWM2M_OBJ_RES_PROP_READ  | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_BOOL, \
              0, \
              0);
              
/*! Macro definition of IPSO resource analog input current value */                           
DECLARE_RES (LW_RES_ANLOG_INPUT_CURRENT_VALUE, LW_RES_ID_ANLOG_INPUT_CURRENT_VALUE,  "analog_input_current_value", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              5);
              
/*! Macro definition of IPSO resource analog output current value */                           
DECLARE_RES (LW_RES_ANLOG_OUTPUT_CURRENT_VALUE, LW_RES_ID_ANLOG_OUTPUT_CURRENT_VALUE,  "analog_output_current_value", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              5);
              
/*! Macro definition of IPSO resource sensor_value */                           
DECLARE_RES (LW_RES_SENSOR_VALUE, LW_RES_ID_SENSOR_VALUE,  "sensor_value", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              0);
              
/*! Macro definition of IPSO resource instantaneous_active_power */              
DECLARE_RES (LW_RES_INSTANTANEOUS_ACTIVE_POWER, LW_RES_ID_INSTANTANEOUS_ACTIVE_POWER,  "instantaneous_active_power", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              0);
                           
/*! Macro definition of IPSO resource event_identifier*/
DECLARE_RES (LW_RES_EVENT_IDENTIFIER, LW_RES_ID_EVENT_IDENTIFIER,  "event_identifier", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_STR, \
              0, \
              0);
                           

/*! Macro definition of IPSO resource x_value*/                                  
DECLARE_RES (LW_RES_X_VALUE, LW_RES_ID_X_VALUE,  "x_value", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              0);
                                 
/*! Macro definition of IPSO resource duration_in_min*/                                 
DECLARE_RES (LW_RES_DURATION_IN_MIN, LW_RES_ID_DURATION_IN_MIN,  "duration_in_min", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_INT, \
              0,\
              0);
              
/*! Macro definition of IPSO resource colour*/                                               
DECLARE_RES (LW_RES_COLOUR, LW_RES_ID_COLOUR,  "colour", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJ_RES_PROP_EXECUTE | \
              LWM2M_OBJECT_RES_PROP_MULTI_INST_NO, LWM2M_OBJ_RES_TYPE_STR, \
              0,\
              0);		  
              
/*! Macro definition of IPSO resource latitude*/                                                             
DECLARE_RES (LW_RES_LATITUDE, LW_RES_ID_LATITUDE, "latitude", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_STR, \
              0, \
              0);
              
/*! Macro definition of IPSO resource application_type*/              
DECLARE_RES (LW_RES_APPLICATION_TYPE, LW_RES_ID_APPLICATION_TYPE, "application_type", \
              LWM2M_OBJ_RES_PROP_READ |LWM2M_OBJ_RES_PROP_WRITE | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_STR, \
              0, \
              0);
			                
DECLARE_RES (LW_RES_CUMULATIVE_ACTIVE_POWER, LW_RES_ID_CUMULATIVE_ACTIVE_POWER, "cummulative active power", \
              LWM2M_OBJ_RES_PROP_READ | LWM2M_OBJECT_RES_PROP_MULTI_INST_NO,\
              LWM2M_OBJ_RES_TYPE_FRAC, \
              0, \
              0);
