#ifndef __ADC_CPP_H__
#define __ADC_CPP_H__

#ifdef __cplusplus
	extern "C" {
#endif	

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class Adc
{
	private:
		/* data */
	public:
		A_init(void);
		uint16_t A_read(uint8_t ch);
};

#ifdef __cplusplus
	}
#endif	

#endif __ADC_CPP_H__