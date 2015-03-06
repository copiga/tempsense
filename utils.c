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

void stringFloat(char* input, float* out)
{
    *out = 0.00;
}
