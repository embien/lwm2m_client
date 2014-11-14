/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M objects ,instances and resources
  
  Contains macros, structures and declarations for LWM2M objects ,instances and resources
*/

#ifndef LWM2M_DEF_H
#define LWM2M_DEF_H

#define LWM2M_CLIENT_PLAT_WIN32           1   /*!< To enable the windows header file */
#define LWM2M_CLIENT_PLAT_FRDM_KL25       2   /*!< To enable the freedom board kl25 header file */
#define LWM2M_CLIENT_PLAT_RPI             3    /*!< To enable the raspberry pi header file */

#define LWM2M_CLIENT_COMM_UDP_COAP        0  /*!< To enable the CoAP/UDP andriod server */
#define LWM2M_CLIENT_COMM_HTTP_SKYCASE    1  /*!< To enable the http_skycase server */

#define SC_COMM_CONTENT_TYPE_JSON         1  /*!< To select HTTP  content type JSON */
#define SC_COMM_CONTENT_TYPE_XML          2  /*!< To select HTTP  content type JSON */

#define LWM2M_CLIENT_FRAC_MODE_FIXED      1
#define LWM2M_CLIENT_FRAC_MODE_FLOAT      2

#define LWM2M_CLIENT_MAIN_APP_FULL_DEMO   1
#define LWM2M_CLIENT_MAIN_APP_XOR_DEMO    2


//SASP tbd reviewed
#endif