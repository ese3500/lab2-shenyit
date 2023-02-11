#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Initialize() {

    // disable global interrupts
    cli();

    // flag
    TIFR1 |= (1<<ICF1);

    // set up input and output pins
    DDRB &= ~(1<<DDB0);
    DDRB |= (1<<DDB5);

    // enable pin change interrupt (rising)
    TCCR1B |= (1<<ICES1);

    // enable trigger
    TIMSK1 |= (1<<ICIE1);

    // enable global interrupts
    sei();
}

ISR(TIMER1_CAPT_vect) {
    TIFR1 |= (1<<ICF1);
    PORTB ^= (1<<PORTB5);
    TCCR1B ^= (1<<ICES1);
}

int main() {
    Initialize();
    while(1);
}
