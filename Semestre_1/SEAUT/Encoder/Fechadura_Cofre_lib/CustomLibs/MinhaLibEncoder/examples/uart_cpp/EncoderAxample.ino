#include "uart_cpp.h"

int main(void)
{   
    Uart Serial;
	Serial.U_Init(); 
	Serial.U_StrTx("Hello\r\n");

    for(;;){

    }
}