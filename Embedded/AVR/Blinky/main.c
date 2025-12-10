#define F_CPU 16000000UL //clock 16MHz. Slow as me
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << 5); //set pin 13 as output

    while (1) {
        PORTB ^= (1 << 5); //toggle led (bit 5)
        _delay_ms(100);
    }
}
