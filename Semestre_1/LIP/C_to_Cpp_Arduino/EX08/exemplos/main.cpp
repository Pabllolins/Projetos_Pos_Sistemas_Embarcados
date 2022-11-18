#include "adc_cpp.h"

int main(void) {
	char str[20]; 
	Uart serial; 
	Adc temp; 
	
	for(;;)
	{
		snprintf(str, sizeof(str)-1, "%d", temp.read(0)); 
		serial.USART_StrTx((char *)str); 	
	}
	return 0; 
}