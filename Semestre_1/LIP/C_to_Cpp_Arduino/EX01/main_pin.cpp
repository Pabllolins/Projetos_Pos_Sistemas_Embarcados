/**
 * F_CPU é uma diretiva necessária para utilizar _delay_ms.  
 * Em F_CPU é atribuido o valor da frequência do oscilador.
 */
#define F_CPU 16000000UL

/**
 * Inclui as definições dos registrados do ATMEGA328p ou ATMEGA2560;
 */
#include <avr/io.h>

/**
 * Biblioteca que inclui a macro _delay_ms;
 */
#include <util/delay.h>


class Gpio
{
    private:
        volatile uint8_t * port;
        volatile uint8_t pin;

    public:
        Gpio(volatile uint8_t * port, volatile uint8_t pin)
        {
            this->port = port;
            this->pin = pin;
        }
        
        void on()
        {
            *port |= (1<<pin);
        }

        void off()
        {
            *port &= ~(1<<pin);
        }
};

int main(void)
{
    DDRB |= (1<<5); //precisamos vincular ao objeto
    Gpio led = Gpio(&PORTB, 5); //

    for(;;)
    {
        led.on();
        _delay_ms(1000);
        led.off();
        _delay_ms(1000);
    }
    return 0;
}