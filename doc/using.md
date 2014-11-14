                        LWM2M Client for SkyCase/REST and Server/CoAP
                        =============================================
This file provides a brief overview about using this source for your applications.

Configuration:
  All the necessary configuration information is available in app\lwm2m_config.h file. 
  
  Some of the most important configuration includes
  
1. Select the target configuration using LWM2M_CLIENT_TARGET_PLAT macro
#define LWM2M_CLIENT_TARGET_PLAT        LWM2M_CLIENT_PLAT_WIN32

2. Select the main applications using LWM2M_CLIENT_MAIN_APP macro
#define LWM2M_CLIENT_MAIN_APP           LWM2M_CLIENT_MAIN_APP_FULL_DEMO

3. Select the floating point/fixed point mode using LWM2M_CLIENT_FRAC_MODE macro
#define LWM2M_CLIENT_FRAC_MODE          LWM2M_CLIENT_FRAC_MODE_FLOAT

4. Select the underlying communication modeusing LWM2M_CLIENT_COMM_MODE macro
#define LWM2M_CLIENT_COMM_MODE          LWM2M_CLIENT_COMM_HTTP_SKYCASE 

5. Select the receive buffer size in bytes
#define SC_CLIENT_RX_BUFFER_SIZE        1500

Relevant configuration for LWM2M_CLIENT_COMM_UDP_COAP mode includes
#define LWM2M_COAP_UDP_SERVER_IP        "127.0.0.1"     //IP address of the LWM2M server
#define LWM2M_COAP_UDP_SERVER_PORT      5684            //UDP server port
#define LWM2M_CLIENT_NAME               "ep=winclient00"//Client Name to be presented to the server with

Relevant configuration for LWM2M_CLIENT_COMM_HTTP_SKYCASE mode includes
#define SC_SERVER_IP                    "162.251.84.61" //SkyCase Server IP. Need not change
#define SC_SERVER_PORT                  80              //Port Number
#define SC_SERVER_API_URL               "api.skycase-iot.com" //URL for communication
#define SC_COMM_CONTENT_TYPE            SC_COMM_CONTENT_TYPE_JSON //JSON/XML
#define SC_CLIENT_END_POINT_NAME        "demo_client"   //Name to present to the server with
#define SC_HTTP_RESP_READ_TIMEOUT_MSEC  10000           //Read timeout interval


Compilation and Running:
Choose the build path corresponding to the HAL selected
bin/win32 - Open the project using VS2008 or above and build. Once compiled, you can run the same.


Building and Library:
The whole code, except for app directory can be compiled as a library and integrated with your custom code. Refer to the function documentation for major functions to be called along with the sequence.




