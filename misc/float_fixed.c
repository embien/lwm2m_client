
#include <lwm2m_client.h>
#if LWM2M_CLIENT_FRAC_MODE == LWM2M_CLIENT_FRAC_MODE_FIXED

    char *q2a(char *buf, fixedp n);
     




    /* **********************************************************************
     *
     * Fixed Point Math Library
     *
     * **********************************************************************
     *
     * qmath.c
     *
     * Alex Forencich
     * alex@alexelectronics.com
     *
     * Jordan Rhee
     * rhee.jordan@gmail.com
     *
     * IEEE UCSD
     * http://ieee.ucsd.edu
     *
     * **********************************************************************/

     
    /**
     * square root
     */
    fixedp qsqrt(fixedp p_Square)
    {
    	fixedp   res;
    	fixedp   delta;
    	fixedp   maxError;
     
    	if ( p_Square <= 0 )
    		return 0;
     
    	/* start at half */
    	res = (p_Square >> 1);
     
    	/* determine allowable error */
    	maxError =  qmul(p_Square, FIXED_SQRT_ERR);
     
    	do
    	{
    		delta =  (qmul( res, res ) - p_Square);
    		res -=  qdiv(delta, ( res << 1 ));
    	}
    	while ( delta > maxError || delta < -maxError );
     
    	return res;
    }
     
    /**
     * log (base e)
     */
    fixedp qlog( fixedp p_Base )
    {
        fixedp w = 0;
    	fixedp y = 0;
    	fixedp z = 0;
    	fixedp num = int2q(1);
    	fixedp dec = 0;
     
    	if ( p_Base == int2q(1) )
    		return 0;
     
    	if ( p_Base == 0 )
    		return 0xffffffff;
     
    	for ( dec=0 ; qabs( p_Base ) >= int2q(2) ; dec += int2q(1) )
    		p_Base = qdiv(p_Base, QLN_E);
     
    	p_Base -= int2q(1);
    	z = p_Base;
    	y = p_Base;
    	w = int2q(1);
     
    	while ( y != y + w )
    	{
    		z = 0 - qmul( z , p_Base );
    		num += int2q(1);
    		w = qdiv( z , num );
    		y += w;
    	}
     
    	return y + dec;
    }
     
    /**
     * log base 10
     */
    fixedp qlog10( fixedp p_Base )
    {
        // ln(p_Base)/ln(10)
        // more accurately, ln(p_Base) * (1/ln(10))
        return qmul(qlog(p_Base), Q1OLN_10);
    }
     
    /**
     * exp (e to the x)
     */
    fixedp qexp(fixedp p_Base)
    {
    	fixedp w;
    	fixedp y;
    	fixedp num;
     
    	for ( w=int2q(1), y=int2q(1), num=int2q(1) ; y != y+w ; num += int2q(1) )
    	{
    		w = qmul(w, qdiv(p_Base, num));
    		y += w;
    	}
     
    	return y;
    }
     
    /**
     * pow
     */
    fixedp qpow( fixedp p_Base, fixedp p_Power )
    {
    	if ( p_Base < 0 && qmod(p_Power, int2q(2)) != 0 )
    		return - qexp( qmul(p_Power, qlog( -p_Base )) );
    	else
    		return qexp( qmul(p_Power, qlog(qabs( p_Base ))) );
    }
     
    /**
     * sinx, internal sine function
     */
    static fixedp sinx(fixedp x)
    {
    	fixedp xpwr;
    	long xftl;
    	fixedp xresult;
    	short positive;
    	int i;
     
    	xresult = 0;
    	xpwr = x;
    	xftl = 1;
    	positive = -1;
     
    	// Note: 12! largest for long
    	for (i = 1; i < 7; i+=2)
    	{
    		if ( positive )
    			xresult += qdiv(xpwr, long2q(xftl));
    		else
    			xresult -= qdiv(xpwr, long2q(xftl));
     
    		xpwr = qmul(x, xpwr);
    		xpwr = qmul(x, xpwr);
    		xftl *= i+1;
    		xftl *= i+2;
    		positive = !positive;
    	}
     
    	return xresult;
    }
     
    /**
     * sine
     */
    fixedp qsin(fixedp theta)
    {
    	fixedp xresult;
    	short bBottom = 0;
    	//static fixed xPI = XPI;
    	//static fixed x2PI = X2PI;
    	//static fixed xPIO2 = XPIO2;
     
    	fixedp x = qmod(theta, Q2PI);
    	if ( x < 0 )
    		x += Q2PI;
     
    	if ( x > QPI )
    	{
    		bBottom = -1;
    		x -= QPI;
    	}
     
    	if ( x <= QPIO2 )
    		xresult = sinx(x);
    	else
    		xresult = sinx(QPIO2-(x-QPIO2));
     
    	if ( bBottom )
    		return -xresult;
     
    	return xresult;
    }
     
    /**
     * cosine
     */
    fixedp qcos(fixedp theta)
    {
    	return qsin(theta + QPIO2);
    }
     
    /**
     * tangent
     */
    fixedp qtan(fixedp theta)
    {
    	return qdiv(qsin(theta), qcos(theta));
    }
     
    /**
     * q2a - converts a fixed point number to a string
     */
    char *q2a(char *buf, fixedp n)
    {
    	long ipart = qipart(n);
    	long fpart = qfpart(n);
    	long intdigits = 0;
     
    	int i = 0;
    	int j = 0;
    	int d = 0;
     
    	int offset = 0;
     
    	long v;
    	long t;
    	long st = 0;
     
    	if (n != 0)
    	{
    		intdigits = qipart(qceil(qlog10(qabs(n))));
    	}
     
    	if (intdigits < 1) intdigits = 1;
     
    	offset = intdigits - 1;
     
    	if (n < 0)
    	{
    		buf[0] = '-';
    		offset++;
    		n = -n;
    		ipart = -ipart;
    		fpart = -fpart;
    	}
     
    	// integer portion
     
    	for (i = 0; i < intdigits; i++)
    	{
    		j = offset - i;
    		d = ipart % 10;
    		ipart = ipart / 10;
    		buf[j] = '0' + d;
    	}
     
    	// decimal point
     
    	buf[offset + 1] = '.';
     
    	// fractional portion
     
    	v = 5;
    	t = FIXED_RESOLUTION >> 1;
     
    	for (i = 0; i < FIXED_DECIMALDIGITS - 1; i++)
    	{
    		v = (v << 1) + (v << 3);
    	}
     
    	for (i = 0; i < FIXED_FRACBITS; i++)
    	{
    		if (fpart & t)
    		{
    			st += v;
    		}
    		v = v >> 1;
    		t = t >> 1;
    	}
     
    	offset += FIXED_DECIMALDIGITS + 1;
     
    	for (i = 0; i < FIXED_DECIMALDIGITS; i++)
    	{
    		j = offset - i;
    		d = st % 10;
    		st = st / 10;
    		buf[j] = '0' + d;
    	}
     
    	// ending zero
    	buf[offset + 1] = '\0';
     
    	return buf;
    }




INT32U rs_uno_divider_value (INT32U u32_count)
{
    INT32U u32_divder = 1;
	while (u32_count)
	{
      u32_divder *= 10;
	  u32_count --;
	}
    return u32_divder;
}

int power_of_two (INT32S num)
{ 
  num = 1 << num;
  return num;
}


int init = 0;

FRACTION a2q (INT8U* ptr_str)
{
	INT32S s32_max_pos_range = 0, s32_max_neg_range = 0;
    int integer_num = 0, count = 0, index = 0, negetive_flag = 0 , range = 0; 
    int fractional_num = 0; 
	INT32U u32_divder = 0;
    INT8U* ptr_src = ptr_str;
	INT8U* ptr_frac;
	INT8U* ptr_int;
	float frac_num = 0; 
	FRACTION fixed_num = 0;
	int fractional_part = 0;
	
    if (*ptr_str == '-')
	{
      negetive_flag = 1;
	  ptr_str ++;
	  ptr_int = ptr_str;
	}
	else
	{
      ptr_int = ptr_str;
	}
	while (*ptr_str != '.' && *ptr_str != '\0')
	{
      ptr_str ++;
	}
	
    *ptr_str = '\0';
    integer_num = atoi (ptr_int);//atoi (ptr_src);
	
#if 1	
	printf ("integer_part = %d\r\n", integer_num);
#endif 
    ptr_str ++;
	ptr_frac = ptr_str;
	while (*ptr_str)
	{
      ptr_str ++;
	  count ++;
	}
	fractional_num = atoi (ptr_frac);
	//printf ("fractional_num = %d\r\n", fractional_num);
    u32_divder = rs_uno_divider_value (count);
    //printf ("u32_divder = %d\r\n", u32_divder);
    frac_num = (float)((float)fractional_num / (float)u32_divder);
	//printf ("frac_num = %f\r\n", frac_num);
	fractional_part =(INT32U) frac_num * 8192;  //256 == 8 bit frac part   8192 == 13 bit frac part
#if 0
	printf ("fractional_part = %x\r\n", fractional_part);
#endif     
	integer_num <<= FIXED_FRACBITS;
#if 0
    printf ("integer_num = %x\r\n", integer_num);
#endif     
	fixed_num = (FRACTION)(integer_num | fractional_part);
#if 1
    printf ("fixed_num = %x\r\n", fixed_num);
#endif     
	
	if (negetive_flag)
	{
       fixed_num = 0 - fixed_num;
	  /* if ((fixed_num  < MAX_FP_NEG_RANGE))
	   {
          return FIXED_INVALID_NUM;
	   }*/
	}
	else
	{
      /*if ((fixed_num  & MAX_FP_NEG))
	  {
         return FIXED_INVALID_NUM;
	  }*/
	}
	
	//power_of_two (-FIXED_FRACBITS);
	//s32_max_pos_range = power_of_two (FIXED_INTBITS) - power_of_two (-FIXED_FRACBITS);//0.5;
	//printf ("s32_max_pos_range = %x\r\n", s32_max_pos_range);
    //s32_max_neg_range = -(power_of_two (FIXED_INTBITS));  
    //printf ("s32_max_neg_range = %x\r\n", s32_max_neg_range);
    
	return fixed_num;

}



FRACTION  str_to_float (INT8U * str_val, int total_len)
{      
  FRACTION frac_part = 0, dec_part = 0, value = 0;
  int index = 0, fraction_value = 1;
  for (index = 0; index < total_len && str_val [index] != '.' ; index ++)
  {
    dec_part = dec_part * 10 + (str_val [index] - 48);
  }
  if ( str_val [index] == '.' && index < total_len)
  {
    for (index ++;index < total_len ;index ++)
    {
      frac_part = frac_part * 10 +(str_val [index] - 48);
	    fraction_value = fraction_value * 10;
    }
    frac_part =  frac_part / fraction_value;
    value = dec_part + frac_part;
  }
  return value;
}






#endif
