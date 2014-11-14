/*! \file 
  \brief      Module implementing the LWM2M client main function 
  
   Contains the logic initialise timer and interrupt 
*/

#include <lwm2m_client.h>
void SysTickIntHandler(void);
extern int lwm2m_client_main ();
int win32_int_block = 0;

/*! \fn        int _tmain(int argc, _TCHAR* argv[])
    \brief     Starts the main function    
    \param[in] argc     Arguement counter indicates the number of arguements
    \param[in] argv[]   Arguement vector indicates arguements to be passed to function
    \return    int         Zero on success  or error code on failure
*/
int _tmain(int argc, _TCHAR* argv[])
{
  lwm2m_client_main ();
  return 0;
}

LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
LARGE_INTEGER Frequency;

/*! \fn        void init_win32_timer ()
    \brief     Initialise the timer     
    \param[in] None    
    \return    None 
*/
void init_win32_timer ()
{
  QueryPerformanceFrequency(&Frequency); 
  QueryPerformanceCounter(&StartingTime);
}

void win32_timer_test ()
{
//
// We now have the elapsed number of ticks, along with the
// number of ticks-per-second. We use these values
// to convert to the number of elapsed microseconds.
// To guard against loss-of-precision, we convert
// to microseconds *before* dividing by ticks-per-second.
//
// Activity to be timed
QueryPerformanceCounter(&EndingTime);
ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
ElapsedMicroseconds.QuadPart *= 1000000;
ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
if (ElapsedMicroseconds.QuadPart > 1000)
{
  //SysTickIntHandler ();
  QueryPerformanceCounter(&StartingTime);
}

}

/*! \fn        int init_hal ()
    \brief     Initialise the abstraction layer
    \param[in] None    
    \return    None 
*/
int init_hal ()
{
  sc_http_init ();
  init_win32_timer ();
  return 0;
}

void lw_sleep_ms (int ms)
{
  Sleep (ms);
}


