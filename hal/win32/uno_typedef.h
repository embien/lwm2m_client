//G

#ifndef __UNO_TYPEDEF_H__


#define __UNO_TYPEDEF_H__

#define NULL        ((void *)0)               /*!< NULL pointer*/

#ifndef  FALSE
#define  FALSE                     0  /*!< False condition*/
#endif

#ifndef  TRUE
#define  TRUE                      1  /*!< True condition*/
#endif


/*Variable Size*/
typedef unsigned char   INT8U;           /*!< Unsigned  8 bit variable*/
typedef signed char     INT8S;           /*!< Signed    8 bit variable*/
typedef unsigned short  INT16U;          /*!< Unsigned 16 bit variable*/
typedef signed short    INT16S;          /*!< Signed   16 bit variable*/
typedef unsigned long   INT32U;          /*!< Unsigned 32 bit variable*/
typedef signed long     INT32S;          /*!< Signed   32 bit variable*/

//Volatile
typedef volatile unsigned char   VINT8U;           /*!< Unsigned  8 bit volatile variable*/
typedef volatile signed char     VINT8S;           /*!< Signed    8 bit volatile variable*/
typedef volatile unsigned short  VINT16U;          /*!< Unsigned 16 bit volatile variable*/
typedef volatile signed short    VINT16S;          /*!< Signed   16 bit volatile variable*/
typedef volatile unsigned long   VINT32U;          /*!< Unsigned 32 bit volatile variable*/
typedef volatile signed long     VINT32S;          /*!< Signed   32 bit volatile variable*/

//
typedef unsigned char   UCHAR;          /*!< Unsigned  8 bit variable*/
typedef unsigned char   BYTE;           /*!< Signed    8 bit variable*/
typedef signed char     CHAR;           /*!< Signed    8 bit variable*/
typedef unsigned short  USHORT;         /*!< Unsigned 16 bit variable*/
typedef unsigned short  WORD;           /*!< Unsigned 16 bit variable*/
typedef signed short    SHORT;          /*!< Signed   16 bit variable*/
typedef unsigned long   ULONG;          /*!< Unsigned 32 bit variable*/
typedef unsigned long   DWORD;          /*!< Unsigned 32 bit variable*/
typedef signed long     LONG;           /*!< Signed   32 bit variable*/
typedef int				      INT;            /*!< Generic Integer Type*/
typedef unsigned int	  UINT;           /*!< Generic Unsigned Integer Type*/      
typedef unsigned char   BOOLEAN;           /*!< Boolean variable*/
typedef int RS_RET_VAL ;
typedef int RS_RET_INT ;


typedef unsigned char   INT8U;           /* Unsigned  8 bit quantity         */
typedef signed char     INT8S;           /* Signed    8 bit quantity         */
typedef unsigned short  INT16U;          /* Unsigned 16 bit quantity         */
typedef signed short    INT16S;          /* Signed   16 bit quantity         */
typedef unsigned long   INT32U;          /* Unsigned 32 bit quantity         */
typedef signed long     INT32S;          /* Signed   32 bit quantity         */

//Volatile
typedef volatile unsigned char   VINT8U;           /* Unsigned  8 bit quantity         */
typedef volatile signed char     VINT8S;           /* Signed    8 bit quantity         */
typedef volatile unsigned short  VINT16U;          /* Unsigned 16 bit quantity         */
typedef volatile signed short    VINT16S;          /* Signed   16 bit quantity         */
typedef volatile unsigned long   VINT32U;          /* Unsigned 32 bit quantity         */
typedef volatile signed long     VINT32S;          /* Signed   32 bit quantity         */

//
typedef unsigned char   UCHAR;           /* Unsigned  8 bit quantity         */
typedef unsigned char   BYTE;           /* Signed    8 bit quantity         */
typedef signed char     CHAR;           /* Signed    8 bit quantity         */
typedef unsigned short  USHORT;          /* Unsigned 16 bit quantity         */
typedef unsigned short  WORD;           /* Unsigned 16 bit quantity         */
typedef signed short    SHORT;          /* Signed   16 bit quantity         */
typedef unsigned long   ULONG;          /* Unsigned 32 bit quantity         */
typedef unsigned long   DWORD;          /* Unsigned 32 bit quantity         */
typedef signed long     LONG;          /* Signed   32 bit quantity         */
typedef int				INT;
typedef unsigned int	UINT;



#define FLOAT_POINT   1
#define FIXED_POINT   0

#if FLOAT_POINT
typedef float FRACTION;  
#endif
#if FIXED_POINT 
typedef INT32S FRACTION;
#endif




typedef int             RS_RET_VAL;
typedef INT							RS_RET_INT;

typedef INT32U					RS_TIMEOUT_VAL;

//TODO
//typedef INT32U					RED_RET_VAL;
//typedef INT							RED_RET_INT;
//typedef INT32U					RED_TIMEOUT;


//typedef INT16U					RED_PIN_NO;//Use the next

typedef INT16U					RS_HW_PIN_NO;

//Modified code
typedef char            GCHAR;


#ifndef  FALSE
#define  FALSE                     0
#endif

#ifndef  TRUE
#define  TRUE                      1
#endif

#define BIT(x)                          (1 << (x))

#define NULL        ((void *)0)

//For Alignment
#define ALIGN_AT_BOUNDARY(x)		__attribute__((aligned(x)))

//Start pre Struct Packing
#define PACKING_PRE_START	

//Start Struct Packing
#define PACKING_START 	__attribute__((__packed__))

#define BIT(x)          (1 << (x))
#endif //__UNO_TYPEDEF_H__