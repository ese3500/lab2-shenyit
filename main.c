#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

/*--------------------Libraries---------------------------*/
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "uart.h"

// stores sequence of characters continuously
char String[20];

// used to print current character
char PrintChar[25];

// store time when button is pressed down
unsigned int i;

// store time when button is released
unsigned int j;

// store element in String array
unsigned int k;

// store time to calculate when the LED should turn off in the main function
unsigned int light;

// store when there is a space in the last
unsigned int checkSpace;

void Initialize() {

    // disable global interrupts
    cli();

    // flag
    TIFR1 |= (1<<ICF1);

    // set up input pin
    DDRB &= ~(1<<DDB0);

    // set up output pins
    DDRB |= (1<<DDB1);
    DDRB |= (1<<DDB2);

    // enable pin change interrupt (rising)
    TCCR1B |= (1<<ICES1);

    // enable prescaler of value 256
    TCCR1B |= (1<<CS12);

    // enable trigger
    TIMSK1 |= (1<<ICIE1);

    // set k = 0
    k = 0;

    sei();
}

void printLetter() {

    if (strcmp(String, "._") == 0) {
        // A
        sprintf(PrintChar, "A");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_...") == 0) {
        // B
        sprintf(PrintChar, "B");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_._.") == 0) {
        // C
        sprintf(PrintChar, "C");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_..") == 0) {
        // D
        sprintf(PrintChar, "D");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".") == 0) {
        // E
        sprintf(PrintChar, "E");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".._.") == 0) {
        // F
        sprintf(PrintChar, "F");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "__.") == 0) {
        // G
        sprintf(PrintChar, "G");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "....") == 0) {
        // H
        sprintf(PrintChar, "H");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "..") == 0) {
        // I
        sprintf(PrintChar, "I");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".___") == 0) {
        // J
        sprintf(PrintChar, "J");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_._") == 0) {
        // K
        sprintf(PrintChar, "K");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "._..") == 0) {
        // L
        sprintf(PrintChar, "L");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "__") == 0) {
        // M
        sprintf(PrintChar, "M");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_.") == 0) {
        // N
        sprintf(PrintChar, "N");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "___") == 0) {
        // O
        sprintf(PrintChar, "O");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".__.") == 0) {
        // P
        sprintf(PrintChar, "P");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "__._") == 0) {
        // Q
        sprintf(PrintChar, "Q");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "._.") == 0) {
        // R
        sprintf(PrintChar, "R");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "...") == 0) {
        // S
        sprintf(PrintChar, "S");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_") == 0) {
        // T
        sprintf(PrintChar, "T");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".._") == 0) {
        // U
        sprintf(PrintChar, "U");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "..._") == 0) {
        // V
        sprintf(PrintChar, "V");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".__") == 0) {
        // W
        sprintf(PrintChar, "W");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_.._") == 0) {
        // X
        sprintf(PrintChar, "X");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_.__") == 0) {
        // Y
        sprintf(PrintChar, "Y");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "__..") == 0) {
        // Z
        sprintf(PrintChar, "Z");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".____") == 0) {
        // 1
        sprintf(PrintChar, "1");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "..___") == 0) {
        // 2
        sprintf(PrintChar, "2");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "...__") == 0) {
        // 3
        sprintf(PrintChar, "3");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "...._") == 0) {
        // 4
        sprintf(PrintChar, "4");
        UART_putstring(PrintChar);
    } else if (strcmp(String, ".....") == 0) {
        // 5
        sprintf(PrintChar, "5");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_....") == 0) {
        // 6
        sprintf(PrintChar, "6");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "__...") == 0) {
        // 7
        sprintf(PrintChar, "7");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "___..") == 0) {
        // 8
        sprintf(PrintChar, "8");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "____.") == 0) {
        // 9
        sprintf(PrintChar, "9");
        UART_putstring(PrintChar);
    } else if (strcmp(String, "_____") == 0) {
        // 0
        sprintf(PrintChar, "0");
        UART_putstring(PrintChar);
    }

    // clear String array after we have printed out the ASCII char to prepare to store new char
    // set k = 0 to clear String array completely
    for (int i = 0; i < 20; i++) {
        String[i] = '\0';
        k = 0;
    }
}



ISR(TIMER1_CAPT_vect) {
    // clear input capture flag
    TIFR1 |= (1<<ICF1);

    // check if the switch is pressed down
    if (PINB & (1<<PINB0)) {
        // reset TCNT1 to 0 to prevent overflow
        TCNT1 = 0;
        // set i to the value of TCNT1 at the rising edge
        i = 0;
        // change to detect falling edge
        TCCR1B ^= (1<<ICES1);
    // check if the switch is released
    } else {
        // set j to the value of TCNT1 at the falling edge
        j = TCNT1;

        // check to see which LED should light up
        if ((j - i >= 1875) & (j - i <= 12500)) {
            // light up red LED
            PORTB |= (1 << PORTB1);
            light = 0;

            // store dot in String array
            String[k] = '.';
            // increment k so that next value can be stored in the next index of String array
            k++;

            // checkSpace is 0 to indicate last index stored a dot or dash
            checkSpace = 0;

        } else if ((j - i > 12500) & (j - i <= 25000)) {
            // light up green LED
            PORTB |= (1 << PORTB2);
            light = 0;

            // store dash in String array
            String[k] = '_';
            // increment k so that next value can be stored in the next index of String array
            k++;

            // checkSpace is 0 to indicate last index stored a dot or dash
            checkSpace = 0;

        }
        // change to detect rising edge
        TCCR1B ^= (1<<ICES1);

    }
}

int main() {
    // prescale TCNT1 by 256
    UART_init(BAUD_PRESCALER);
    Initialize();

    while(1) {
        // increment light
        light++;

        if (light == 5000) {
            // turn off red LED after a few ms
            PORTB &= ~(1 << PORTB1);

            // turn off green LED after a few ms
            PORTB &= ~(1 << PORTB2);
        }

        if (62500 < j + 40000) {
            // if there is possibility of overflow, reset TCNT1 to 0 and subtract 62500 from j
            // 62500 is the maximum value of TCNT1, as we have prescaled it by 256
            j = j - 62500;
            TCNT1 = 0;
        }

        if ((TCNT1 > j + 40000) && (checkSpace == 0)) {
            // checkSpace set to 1 to indicate we have reached a space
            checkSpace = 1;

            // go to printLetter function to print out ASCII character
            printLetter();
        }
    }
}
