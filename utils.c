#include <ctype.h>
/***************************/
/* WARNING:		   */
/*     UNAPOLOGETIC GOTOS  */
/***************************/
void floatString(float input, char *out)
{
    int pos = 0;
    int places = 0;
    int x;
    int Cnum;
    
    if(input < 0)
	out[pos++] = '-';
    while(input >= 10.00)
    {
	input /= 10.0;
	places++;
    }
    for(x = 0;x < 3;x++)
    {
	Cnum = (int) input;
	input -= Cnum;
	if(Cnum > 9)
	    goto err;
	//ascii code for the current number
	out[pos++] = 48 + Cnum;
	if(places == 0)
	    out[pos++] = '.';
	input *= 10;
	places--;
    }
    
  fin:
    out[x + 1] = 0;
    return;
    
  err:
    out[x] = 'E';
    goto fin;
}

double thisAtof(char *s)
{
    double a = 0.0;
    int e = 0;
    int c;
    while ((c = *s++) != '\0' && isdigit(c)) 
    {
	a = a*10.0 + (c - '0');
    }
    if (c == '.') 
    {
	while ((c = *s++) != '\0' && isdigit(c)) 
	{
	    a = a*10.0 + (c - '0');
	    e = e-1;
	}
    }
    if (c == 'e' || c == 'E') 
    {
	int sign = 1;
	int i = 0;
	c = *s++;
	if (c == '+')
	    c = *s++;
	else if (c == '-') 
	{
	    c = *s++;
	    sign = -1;
	}
	while (isdigit(c)) 
	{
	    i = i*10 + (c - '0');
	    c = *s++;
	}
	e += i*sign;
    }
    while (e > 0) 
    {
	a *= 10.0;
	e--;
    }
    while (e < 0) 
    {
	a *= 0.1;
	e++;
    }
    return a;
}


void stringFloat(char* input, float *out)
{
    *out = thisAtof(input);
    
}
