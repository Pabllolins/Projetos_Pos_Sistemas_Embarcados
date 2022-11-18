#ifndef __adc_cpp_H__
#define __adc_cpp_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define F_CPU 16000000UL					
#define BAUD 9600
#define MYUBRR (((F_CPU/16)/BAUD)-1)
#include <avr/io.h>
#include <util/delay.h>	
#include "adc_cpp.h"


class Uart
{
    public:
        U_Init(void);
        void U_Transmit(unsigned char data);
        unsigned char U_Receive( void );
        void U_StrTx(const char*);
        void U_rxIE(void);        
    private:

};

#ifdef __cplusplus
}
#endif

#endif __adc_cpp_H__