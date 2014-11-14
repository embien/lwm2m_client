/*! \file 
  \brief      Header implementing neccessary declarations for IPSO resources 
  
  Contains macros, structures and declarations for user specific IPSO  resources
*/

#ifndef LWM2M_REUSE_RES_H
#define LWM2M_REUSE_RES_H

#define LW_RES_ON_OFF                       "on_off"                                  /*!< IPSO resource onoff */
#define LW_RES_DIMMER                       "dimmer"                                  /*!< IPSO resource dimmer */
#define LW_RES_SET_POINT_VALUE              "set_point_value"                         /*!< IPSO resource set poin value*/
#define LW_RES_DIG_INPUT_STATE              "digital_input_state"                     /*!< IPSO resource digital input state*/
#define LW_RES_DIG_OUTPUT_STATE             "digital_output_state"                    /*!< IPSO resource digital output state */
#define LW_RES_ANLOG_INPUT_CURRENT_VALUE    "analog_input_current_value"              /*!< IPSO resource analog input current value */
#define LW_RES_ANLOG_OUTPUT_CURRENT_VALUE    "analog_output_current_value"            /*!< IPSO resource analog output current value */
#define LW_RES_SENSOR_VALUE                  "sensor_value"                           /*!< IPSO resource sensor value*/
#define LW_RES_INSTANTANEOUS_ACTIVE_POWER    "instantaneous_active_power"             /*!< IPSO resource instantaneous active power*/ 
#define LW_RES_EVENT_IDENTIFIER              "event_identifier"                       /*!< IPSO resource event identifier */
#define LW_RES_X_VALUE                       "x_value"                                /*!< IPSO resource xvalue */ 
#define LW_RES_DURATION_IN_MIN				       "duration_in_min"                        /*!< IPSO resource duration in minitues */
#define LW_RES_LATITUDE						           "latitude"                               /*!< IPSO resource latitude */
#define LW_RES_APPLICATION_TYPE              "application_type"                       /*!< IPSO resource application type */  
#define LW_RES_CUMULATIVE_ACTIVE_POWER         "cumulative_active_power"

#if 0
/* optional resources */
#define LW_RES_DIG_INPUT_COUNTER              "digital_input_counter"
#define LW_RES_DIG_INPUT_POLARITY             "digital_input_polarity"
#define LW_RES_DIG_INPUT_DEBOUNCE_PERIOD      "digital_input_debounce_period"
#define LW_RES_DIG_INPUT_EDGE_SELECTION       "digital_input_edge_selection"
#define LW_RES_DIG_INPUT_COUNTER_RESET        "digital_input_counter_reset"
#define LW_RES_APPLICATION_TYPE               "application_type"
#define LW_RES_SENSOR_TYPE                    "sensor_type"
#define LW_RES_DIG_OUTPUT_POLARITY             "digital_output_polarity"
#define LW_RES_MIN_MEASURED_VALUE              "min_measured_value"
#define LW_RES_MAX_MEASURED_VALUE             "max_measured_value"
#define LW_RES_MIN_RANGE_VALUE                "min_range_value"
#define LW_RES_MAX_RANGE_VALUE                "max_range_value"
#define LW_RES_RESET_MIN_MAX_MEASURE_VALUE    "reset_min_max_measured_value"
#define LW_RES_UNITS                          "units"
#define LW_RES_BUSY_T0_CLEAR_DELAY            "busy_to_clear_delay"
#define LW_RES_CLEAR_TO_BUSY_DELAY            "clear_to_busy_delay"
#define LW_RES_MIN_MEASURED_ACTIVE_POWER      "min_measured_active_power"
#define LW_RES_MAX_MEASURED_ACTIVE_POWER      "max_measured_active_power"
#define LW_RES_MIN_RANGE_ACTIVE_POWER         "min_range_active_power"
#define LW_RES_MAX_RANGE_ACTIVE_POWER         "max_range_active_power"

#define LW_RES_ACTIVE_POWER_CALIBRATION         "active_power_calibration"
#define LW_RES_INSTANTANEOUS_REACTIVE_POWER    "instantaneous_reactive_power"
#define LW_RES_MIN_MEASURED_REACTIVE_POWER     "min_measured_reacitve_power"
#define LW_RES_MAX_MEASURED_REACTIVE_POWER     "max_measured_reacitve_power"
#define LW_RES_MIN_RANGE_REACTIVE_POWER         "min_range_reactive_power"
#define LW_RES_MAX_RANGE_REACTIVE_POWER         "max_range_reactive_power"
#define LW_RES_CUMULATIVE_REACTIVE_POWER        "cumulative_reactive_power"
#define LW_RES_REACTIVE_POWER_CALIBRATION       "reactive_power_calibration"
#define LW_RES_POWER_FACTOR                     "power_factor"
#define LW_RES_CURRENT_CALIBRATION              "current_calibration"
#define LW_RES_RESET_CUMULATIVE_ENERGY          "reset_cumulative_energy"
#define LW_RES_ON_TIME                          "on_time"
#define LW_RES_MUTI_STATE_OUTPUT                "muti_state_output"
#define LW_RES_COLOUR                           "colour"
#define LW_RES_START_TIME                       "start_time"
#define LW_RES_CRITICALITY_LEVEL                "criticality_level"      
#define LW_RES_AVG_LOAD_ADJ_PCT                 "avg_load_adj_pct"
#define LW_RES_DUTY_CYCLE                       "duty_cycle"
#define LW_RES_Y_VALUE                         "y_value" 
#define LW_RES_z_VALUE                          "z_value"
#define LW_RES_MEASUREMENT_RANGE                "measurement_range"
#define LW_RES_COMPASS_DIRECTION                "compass_direction"
#define LW_RES_MIN                              "min" 
#endif



#define LW_RES_ID_ON_OFF                       5850        /*!< IPSO resource id for onoff  */
#define LW_RES_ID_DIMMER                       5851        /*!< IPSO resource id for dimmer*/
#define LW_RES_ID_SET_POINT_VALUE              5900        /*!< IPSO resource id for set point value */
#define LW_RES_ID_DIG_INPUT_STATE              5500        /*!< IPSO resource id for digital input state*/
#define LW_RES_ID_DIG_OUTPUT_STATE             5550        /*!< IPSO resource id for digital output state*/
#define LW_RES_ID_ANLOG_INPUT_CURRENT_VALUE    5600        /*!< IPSO resource id for analog input current value */
#define LW_RES_ID_ANLOG_OUTPUT_CURRENT_VALUE   5650        /*!< IPSO resource id for analog output current value */
#define LW_RES_ID_SENSOR_VALUE                 5700        /*!< IPSO resource id for sensor value*/
#define LW_RES_ID_INSTANTANEOUS_ACTIVE_POWER   5800        /*!< IPSO resource id for instantaneous active power*/ 
#define LW_RES_ID_EVENT_IDENTIFIER             0           /*!< IPSO resource id for event identifier */ 
#define LW_RES_ID_X_VALUE                      0           /*!< IPSO resource id for xvalue */ 
#define LW_RES_ID_DURATION_IN_MIN			         2           /*!< IPSO resource id for duration in minitues */
#define LW_RES_ID_LATITUDE					           0           /*!< IPSO resource id for latitude */
#define LW_RES_ID_COLOUR					             0           /*!< IPSO resource id for colour*/  
#define LW_RES_ID_APPLICATION_TYPE             5750        /*!< IPSO resource id application type */  
#define LW_RES_ID_CUMULATIVE_ACTIVE_POWER     5805


#if 0
/* optional resources id */
#define LW_RES_ID_DIG_INPUT_COUNTER             
#define LW_RES_ID_DIG_INPUT_POLARITY             
#define LW_RES_ID_DIG_INPUT_DEBOUNCE_PERIOD      
#define LW_RES_ID_DIG_INPUT_EDGE_SELECTION       
#define LW_RES_ID_DIG_INPUT_COUNTER_RESET        
#define LW_RES_ID_APPLICATION_TYPE               
#define LW_RES_ID_SENSOR_TYPE                    
#define LW_RES_ID_DIG_OUTPUT_POLARITY             
#define LW_RES_ID_MIN_MEASURED_VALUE              
#define LW_RES_ID_MAX_MEASURED_VALUE             
#define LW_RES_ID_MIN_RANGE_VALUE                
#define LW_RES_ID_MAX_RANGE_VALUE                
#define LW_RES_ID_RESET_MIN_MAX_MEASURE_VALUE    
#define LW_RES_ID_UNITS                          
#define LW_RES_ID_BUSY_T0_CLEAR_DELAY            
#define LW_RES_ID_CLEAR_TO_BUSY_DELAY            
#define LW_RES_ID_MIN_MEASURED_ACTIVE_POWER      
#define LW_RES_ID_MAX_MEASURED_ACTIVE_POWER      
#define LW_RES_ID_MIN_RANGE_ACTIVE_POWER         
#define LW_RES_ID_MAX_RANGE_ACTIVE_POWER         
#define LW_RES_ID_CUMULATIVE_ACTIVE_POWER        
#define LW_RES_ID_ACTIVE_POWER_CALIBRATION       
#define LW_RES_ID_INSTANTANEOUS_REACTIVE_POWER    
#define LW_RES_ID_MIN_MEASURED_REACTIVE_POWER     
#define LW_RES_ID_MAX_MEASURED_REACTIVE_POWER     
#define LW_RES_ID_MIN_RANGE_REACTIVE_POWER         
#define LW_RES_ID_MAX_RANGE_REACTIVE_POWER         
#define LW_RES_ID_CUMULATIVE_REACTIVE_POWER        
#define LW_RES_ID_REACTIVE_POWER_CALIBRATION       
#define LW_RES_ID_POWER_FACTOR                     
#define LW_RES_ID_CURRENT_CALIBRATION              
#define LW_RES_ID_RESET_CUMULATIVE_ENERGY          
#define LW_RES_ID_ON_TIME                          
#define LW_RES_ID_MUTI_STATE_OUTPUT                
#define LW_RES_ID_START_TIME            
#define LW_RES_ID_CRITICALITY_LEVEL                
#define LW_RES_ID_AVG_LOAD_ADJ_PCT                 
#define LW_RES_ID_DUTY_CYCLE                       
#define LW_RES_ID_Y_VALUE                         
#define LW_RES_ID_z_VALUE                         
#define LW_RES_ID_MEASUREMENT_RANGE                
#define LW_RES_ID_COMPASS_DIRECTION                
#define LW_RES_ID_MIN                              
#endif
           
/*! Declaration of the structure for LWM2M resource information */  
#define DECLARE_RES(res_name,res_id,name,prop,type,min,max)    \
const LWM2M_RESOURCE_INFO  lwm2m_res_##res_name##_info = \
{\
  res_id,\
  name,\
  prop,\
  type,\
  min,\
  max\
};

 
#define DECLARE_RES_EXTERN(res_name)    \
extern const LWM2M_RESOURCE_INFO  lwm2m_res_##res_name##_info;    /*!< macro for extern IPSO resources */ 

/*! create a structure variable for every IPSO resources */
#define LWM2M_RES_PROP(res_name)    &lwm2m_res_##res_name##_info

DECLARE_RES_EXTERN (LW_RES_ON_OFF);                      /*!< Extern IPSO resource onoff */
DECLARE_RES_EXTERN (LW_RES_DIMMER);                      /*!< Extern IPSO resource dimmer*/   
DECLARE_RES_EXTERN (LW_RES_SET_POINT_VALUE);             /*!< Extern IPSO resource set point value */
DECLARE_RES_EXTERN (LW_RES_DIG_INPUT_STATE);            /*!< Extern IPSO resource digital input state*/
DECLARE_RES_EXTERN (LW_RES_DIG_OUTPUT_STATE);          /*!< Extern IPSO resource digital output state*/
DECLARE_RES_EXTERN (LW_RES_SENSOR_VALUE);                /*!< Extern IPSO resource sensor value*/
DECLARE_RES_EXTERN (LW_RES_ANLOG_INPUT_CURRENT_VALUE);   /*!< Extern IPSO resource analog input current value*/
DECLARE_RES_EXTERN (LW_RES_ANLOG_OUTPUT_CURRENT_VALUE);  /*!< Extern IPSO resource analog output current value*/ 
DECLARE_RES_EXTERN (LW_RES_INSTANTANEOUS_ACTIVE_POWER);  /*!< Extern IPSO resource instantaneous active power*/
DECLARE_RES_EXTERN (LW_RES_EVENT_IDENTIFIER);            /*!< Extern IPSO resource event identifier*/
DECLARE_RES_EXTERN (LW_RES_X_VALUE);                      /*!< Extern IPSO resource xvalue*/    
DECLARE_RES_EXTERN (LW_RES_DURATION_IN_MIN);              /*!< Extern IPSO resource duration in minitues*/
DECLARE_RES_EXTERN (LW_RES_COLOUR);                       /*!< Extern IPSO resource colour*/
DECLARE_RES_EXTERN (LW_RES_LATITUDE);                     /*!< Extern IPSO resource latitude */  
DECLARE_RES_EXTERN (LW_RES_APPLICATION_TYPE);             /*!< Extern IPSO resource application type */
DECLARE_RES_EXTERN (LW_RES_CUMULATIVE_ACTIVE_POWER);
#endif