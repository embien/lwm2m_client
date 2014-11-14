/*! \file 
  \brief  Header implementing neccessary declarations for CoAP/UDP communication
  
   Contains declaration of functions for CoAP/UDP communication
*/

#ifndef COAP_UDP_H
#define COAP_UDP_H

extern int init_coap_udp_socket (); /*!< Extern function for initialising the UDP socket */
extern int coap_send_to_server (INT8U *ptr_tx_buf, int tx_len); /*!< Extern function to send CoAP message packet to server */
extern int coap_recv_from_server (INT8U *ptr_rx_buf, int rx_len); /*!< Extern function to receive CoAP message packet from  server */
extern int init_lwm2m_udp_client (); /*!< Extern function  initialise UDP communication */
extern void lwm2m_udp_client (INT8U);   /*!< Declaration of a function for lwm2m state process */
extern void lwm2m_client_resource_observe_task (INT8U ub_task_id); /*!< Extern function  resource observe task */
#endif
