/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M client configuration   
  
  Contains macros for LWM2M client configure as skycase server or andriod server     
*/

#ifndef LWM2M_CONFIG_H
#define LWM2M_CONFIG_H


#define LWM2M_CLIENT_TARGET_PLAT        LWM2M_CLIENT_PLAT_WIN32

#define LWM2M_CLIENT_COMM_MODE          LWM2M_CLIENT_COMM_HTTP_SKYCASE       /*!< To select the supported */

#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
#define LWM2M_COAP_UDP_SERVER_IP        "127.0.0.1" //"192.168.137.51" //  /*!< Ip address of the CoAP/UDP server */
#define LWM2M_COAP_UDP_SERVER_PORT      5684        /*!< port numberto be connect on server */
#define LWM2M_REQ_REGISTER_DEVICE       "rd"              /*!< LWM2M registration device name */
#define LWM2M_REQ_END_POINT             "ep="             /*!< LWM2M client endpoint name */
#define LWM2M_CLIENT_NAME               "ep=winclient_02"     /*!< LWM2M client name */ 
#endif

#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
#define SC_LOCAL_TOMCAT_SERVER          0
#define SC_LOCAL_TOMCAT_URI             "/api"
//#define SC_SERVER_IP                    "192.168.137.75"   //"192.168.137.1"   //skycase-"162.251.84.61"*/
#define SC_SERVER_IP                    "162.251.84.61"                /*!< Ip address of the cloud server */
#define SC_SERVER_PORT                  80         //9999                                       //80                           /*!< Port number to be connect on server */
#define SC_SERVER_API_URL               "api.skycase-iot.com"          /*!< url of the server */ 
#define SC_COMM_CONTENT_TYPE            SC_COMM_CONTENT_TYPE_JSON
#define SC_CLIENT_END_POINT_NAME        "demo_client"  /*!< End poin name for HTTP skycase server */
#define SC_HTTP_RESP_READ_TIMEOUT_MSEC  10000        /*!< Waiting time response read */ 
#define SC_HTTP_RESP_READ_TIMEOUT_MSEC  10000        /*!< Waiting time response read */ 

#define SC_PKT_DEV_REG_REQ_MAX_NUM_RESOURCES    10
#define SC_PKT_DATA_WRITE_REQ_MAX_WRITES        10
#define SC_PKT_DATA_READ_REQ_MAX_READS        10
#define SC_PKT_PENDING_REQ_MAX_REQS             10
#define SC_PKT_DEL_PENDING_REQUEST_NUM_REQS     10
#define SC_PKT_DEV_LIST_MAX_DEVICES             10
#define SC_PKT_APP_LIST_MAX_APPLICATIONS        10
#define SC_PKT_EVENT_LIST_MAX_EVENTS            10

#endif

#define LWM2M_CLIENT_MAIN_APP           LWM2M_CLIENT_MAIN_APP_FULL_DEMO
#define LWM2M_CLIENT_FRAC_MODE          LWM2M_CLIENT_FRAC_MODE_FLOAT

#define SC_CLIENT_RX_BUFFER_SIZE             7500      /*!< HTTP response buffer size */

//SASP tbd reviewed

#if 0
#define COAP_UDP_MAX_DATA_SIZE                   100 /*!< CoAP/UDP maximum buffer size */ 
#define LWM2M_MAX_SUPPORTED_OBSERVE_ITEMS        3  /*!< LWM2M maximum supported observed items */
#define LWM2M_CLIENT_SUPPORT_OBSERVE_FEATURE             1  /*!< LWM2M client enable or disalbe the observe */ 
#endif
#define SC_ENABLE_DEBUG_PRINTS                   0 /*!< Debugging print for HTTP/skycase server */


#endif
