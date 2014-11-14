/*! \file 
  \brief    Header implementing neccessary declarations for CoAP message packet information 
  
  Contains macros, structures and declarations for CoAP message packet information
*/

#ifndef COAP_H
#define COAP_H

#include <lwm2m_client.h>

INT8U *get_coap_data_buf (); /*!< Declaration of a function to get the CoAP packet buffer size */

#define COAP_MAX_URI_PATH_LEN               8   /*!< CoAP maximum uri path length */
//#define COAP_MAX_URI_PATH_IDS               3   /*!< CoAP maximum uri path identifier */
#define COAP_MAX_URI_QUERY_LEN              64  /*!< CoAP maximum client name length */
#define COAP_MAX_PAYLOAD_LEN                250 /*!< CoAP maximum length to prepare object list for registration*/
#define COAP_MAX_NUM_LOCATION               3   /*!< CoAP maximum number of location for process */
#define COAP_MAX_LOCATION_PATH_LEN          16  /*!< CoAP maximum length each location path */
//#define COAP_TRANSCATION_ID_MAX             2         //maximum message id     
#define COAP_MAX_TOKEN_LEN					        8   /*!< CoAP maximum token length */
#define COAP_PACKET_TOKEN_LEN_FIELDS				0xF /*!< CoAP packet type token length field */
#define COAP_PACKET_CLASS_REQ							  0  /*!< CoAP packet class request */
#define COAP_PACKET_CLASS_SUC_RESP					2 /*!< CoAP packet class success response*/
#define COAP_PACKET_CLASS_CLI_ERR						4 /*!< CoAP packet class client error*/
#define COAP_PACKET_CLASS_SER_ERR					  5 /*!< CoAP packet class server error*/

#define COAP_PACKET_CLASS_SUC_RESP_CREATED  1 /*!< CoAP packet class success response for creation*/
#define COAP_PACKET_CLASS_SUC_RESP_DELETED  2 /*!< CoAP packet class success response for deletion*/
#define COAP_PACKET_CLASS_SUC_RESP_VALID    3 /*!< CoAP packet class success response for validation*/
#define COAP_PACKET_CLASS_SUC_RESP_CHANGED  4 /*!< CoAP packet class success response for changed */
#define COAP_PACKET_CLASS_SUC_RESP_CONTENT  5 /*!< CoAP packet class success response for content */

#define COAP_PACKET_CLASS_REQ_GET						1 /*!< CoAP packet class request get */
#define COAP_PACKET_CLASS_REQ_POST					2 /*!< CoAP packet class request post */
#define COAP_PACKET_CLASS_REQ_PUT						3 /*!< CoAP packet class request put */

#define COAP_PACKET_VALID_URI_PATH    			BIT(0) /*!< CoAP packet valid bit field for uri path*/
#define COAP_PACKET_VALID_URI_QUERY					BIT(2) /*!< CoAP packet valid bit field for uri querry*/
#define COAP_PACKET_VALID_URI_PAYLOAD				BIT(3) /*!< CoAP packet valid bit field for uri payload*/
#define COAP_PACKET_VALID_LOCATION		   		BIT(4) /*!< CoAP packet valid bit field for valid location*/
#define COAP_PACKET_VALID_PAYLOAD           BIT(5) /*!< CoAP packet valid bit field for valid payload*/
#define COAP_PACKET_VALID_OBSERVE			      BIT(6) /*!< CoAP packet valid bit field for valid observe */
#define COAP_PACKET_VALID_OBSERVE_CANCEL    BIT(7) /*!< CoAP packet valid bit field for observe cancel */

#define COAP_HEADER_VERSION                  0x40  /*!< version of CoAP protocol */  
#define COAP_HEADER_TYPE_CONFIRMABLE         0x00  /*!< CoAP packet type confirmable */
#define COAP_HEADER_TYPE_ACKNOWLEDGEMENT     0x20  /*!< CoAP packet type acknowledgement */

#define COAP_OPTION_OBSERVE					         6  /*!< CoAP option field for observe */
#define COAP_OPTION_CANCEL					         0x70 /*!< CoAP option field for cancel*/
#define COAP_OPTION_PAYLOAD_MARKER           0xFF /*!< CoAP option field for payload marker*/
#define COAP_OPTION_LOCATION_PATH            8 /*!< CoAP option field for location path*/
#define COAP_OPTION_URI_PATH                 11 /*!< CoAP option field for uri path*/
#define COAP_OPTION_URI_QUERY                15 /*!< CoAP option field for uri querry*/
#define COAP_OPTION_FIELD(x)                 ((x) << 4) /*!< To find CoAP option field */

#define COAP_OPTION_LENGTH_8BITS                13 /*!< maximum length of CoAP option field */ 
#define COAP_OPTION_OBSERVE_MARKER			        0x60	/*!< CoAP observe option field marker */
#define LWM2M_OBSERVE_RESOURCE_CHANGED_MARKER	  0x61	/*!< CoAP observe option field resource changed marker */
#define COAP_OBSERVE_STATE_RESET				        0x30	/*!< CoAP packet type to cancel observe */
#define COAP_OBSERVE_STATE_ENABLE				        BIT(0) /*!< CoAP valid bit field to enable observes*/


/*! Structure member declartion for CoAP message packet information */
typedef struct __coap_packet_info 
{
	INT8U u8_packet_type;                                          //ack or confirmable
	INT8U u8_packet_class;                                            //3 bit 0-req 2-response 4- client 5-server
	INT8U u8_packet_detail;                                               //5 bit 
  INT16U u16_msg_id;     
  INT8U client_id;                                              // 2 bytes of  message id
	INT8U u8_valid_fields;                                              //COAP_PACKET_VALID_LOCATION
	INT8U u8_valid_ids;                                                //not yet used 
	INT8U u8_valid_locations;                                         // no of locations in uri path
  INT8U u8_payload_len;                                            //length of the payload
	INT8U uri_path_str [COAP_MAX_URI_PATH_LEN];                     //used for registered device
//	INT16U uri_path_ids [COAP_MAX_URI_PATH_IDS];                   // not yet used
	INT8U uri_path_query [COAP_MAX_URI_QUERY_LEN];                //
  INT8U uri_location_path_str [COAP_MAX_NUM_LOCATION] [COAP_MAX_LOCATION_PATH_LEN]; //0-rd, 1 - 6
	INT8U payload [COAP_MAX_PAYLOAD_LEN];    
	INT8U u8_token_value [COAP_MAX_TOKEN_LEN];
	INT8U u8_observe_count;
	INT8U  u8_misc_req;
	INT8S u8_token_len;// data to be send after payload marker
} COAP_PACKET_INFO;

extern COAP_PACKET_INFO coap_tx_packet; /*!< Declaration of a structure for CoAP transmit packet */
extern COAP_PACKET_INFO coap_rx_packet; /*!< Declaration of a structure for CoAP receive packet */
int coap_decode_packet (COAP_PACKET_INFO *, INT8U *, int); /*!< Declaration of a function for dismantling the CoAP packet comes from server*/
int coap_transmit_packet (COAP_PACKET_INFO *ptr_packet); /*!< Declaration of a function for assembling  the CoAP packet and send to server*/

#endif
