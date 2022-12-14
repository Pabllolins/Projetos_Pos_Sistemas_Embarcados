#include "uart_cpp.h"


Uart::U_Init()
{
    UBRR0H = (uint8_t) (MYUBRR>>8);				// Ajuste da transmissão em 9600 bps
    UBRR0L = (uint8_t)(MYUBRR);
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);				// Habilita transmissão e recepção
    UCSR0C = (3<<UCSZ00);						// Modo assincrono, 8 bits, 1 stop, sem paridade
}
//-------------------------------------------------------------------------------------------------------

void Uart::U_Transmit(unsigned char data)
{
    while(!(UCSR0A & (1<<UDRE0)));				// Espera o dado ser enviado
    UDR0 = data;								// Envia o dado pela porta serial
}

//-------------------------------------------------------------------------------------------------------

unsigned char Uart::U_Receive()
{
    while(!(UCSR0A & (1<<RXC0)));				// Espera o dado ser recebido
    return UDR0;
}

//-------------------------------------------------------------------------------------------------------

void Uart::U_StrTx(const char* ptr)
{
    while(*ptr != '\0')
    {
        U_Transmit(*ptr);
        ptr++;
    }
}
//-------------------------------------------------------------------------------------------------------

void Uart::U_rxIE()
{
    UCSR0B |= (1 << RXCIE0 );
}
