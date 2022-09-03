#include <avr/io.h>

void USART_Init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive( void );
void USART_StrTx(const char*);
void USART_rxIE(void);

int main(void)
{
    USART_Init(); 
	USART_StrTx("HELLO NEW LIB\r\n");
	
    while (1) 
    {
    }
}

