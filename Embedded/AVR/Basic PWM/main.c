#define F_CPU 16000000UL //clock 16MHz.
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define TIME_DELAY 15
#define TIMER_TOP 99
#define TIMER_BOTTOM 0
#define BITMASK(x) (1 << x)

void detrmine_direction(bool* increase);
void updtae_ocr1a(bool increase);

ISR(TIMER1_COMPA_vect) {
    PORTB &= ~BITMASK(PB5); //toggle led off (bit 5)
}

ISR(TIMER1_OVF_vect) {
    PORTB |= BITMASK(PB5); //turn led on (bit 5)
}

int main(void) {
    DDRB |= BITMASK(PB5); //set pin 13 as output
    bool increase = true;

    //Set to fast PWM (mode 14) with 64 prescaler
    TCCR1A = BITMASK(WGM11);
    TCCR1B = (BITMASK(WGM13) | BITMASK(WGM12) | BITMASK(CS11) | BITMASK(CS10));
    //Set compare and counter top
    OCR1A = TIMER_BOTTOM;
    ICR1 = TIMER_TOP;

    //enable interrupts
    TIMSK1 = ((1 << OCIE1A) | (1 << TOIE1));
    sei();

    while (1) {
        _delay_ms(TIME_DELAY);

        detrmine_direction(&increase);

        updtae_ocr1a(increase);
    }
}

void detrmine_direction(bool* increase) {
    if (OCR1A >= TIMER_TOP) {
        *increase = false;
    } else if (OCR1A <= TIMER_BOTTOM) {
        *increase = true;
    }
}

void updtae_ocr1a(bool increase) {
    if (increase) {
        OCR1A++;
    } else {
        OCR1A--;
    }
}