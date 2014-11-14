/*! \file 
  \brief      Header implementing neccessary declarations for LWM2M objects ,instances and resources
  
  Contains macros, structures and declarations for LWM2M objects ,instances and resources
*/

#ifndef LWM2M_HAL_H
#define LWM2M_HAL_H

#if LWM2M_CLIENT_TARGET_PLAT == LWM2M_CLIENT_PLAT_WIN32
#include <stdafx.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <win32_hal.h>
#include <winsock2.h>
#include <Windows.h>

#endif

int init_hal ();   /*!< Extern function  initialise hardware abstration layer */
void lw_sleep_ms (int ms);
#endif