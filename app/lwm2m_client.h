/*! \file 
  \brief      Header implementing neccessary inclusion of the header file 
  
  Contains header file for whole project
*/

#ifndef LWM2M_CLIENT_H
#define LWM2M_CLIENT_H

#include <lwm2m_hal.h>
#include <uno_typedef.h>
#include <lwm2m_def.h>
#include <lwm2m_config.h>

#include <lwm2m_object.h>
#include <target_app.h>

#if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_UDP_COAP
#include <coap.h>

#else #if LWM2M_CLIENT_COMM_MODE == LWM2M_CLIENT_COMM_HTTP_SKYCASE
#include <sc_packets.h>
#include <sc_http.h>
#include <sc_pkt_info.h>
#include <sc_pkt_json.h>
#include <lwm2m_http_task.h>
#endif

#include <lwm2m_sup_objects.h>
#include <lwm2m_reuse_res.h>

#include <base64.h>
#endif 
