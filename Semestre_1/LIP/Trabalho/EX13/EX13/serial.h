/*
 * serial.h
 *
 * Created: 04/05/2019 01:31:22
 *  Author: Microgenios
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>

class Serial
{
	private:
	char txt[20];
	void writebyte( char data );
	void writestr( char *ptr );
	
	public:
	Serial( /* Serial *this */ );
	void print( int i );
	void print( float  f );
	void print( const char * c );
	void print( uint16_t i );
	int adc_read( int channel );

};



#endif /* SERIAL_H_ */