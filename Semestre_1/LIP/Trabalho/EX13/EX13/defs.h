/*
 * defs.h
 *
 * Created: 04/05/2019 00:59:49
 *  Author: Microgenios
 */ 


#ifndef DEFS_H_
#define DEFS_H_


#define F_CPU 	16000000UL
#define BAUD 	9600
#define MYUBRR 	(((F_CPU/16)/BAUD)-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <util/atomic.h>

#endif /* DEFS_H_ */