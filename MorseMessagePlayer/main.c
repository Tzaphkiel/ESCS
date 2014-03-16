/*
 * File:   main.c
 * Author: leroyse
 * Creation: 2014.01.15
 * Last-modified: 2014.01.27
 *
 * MCU used: PIC16F628A
 * Compiler: XC8
 *
 * Changelog:
 *  - LEROYSE : cleaned up the code and renamed a couple of variables to make better sense
 */
#include <xc.h>
#include <string.h>
// PIC16F648A Configuration Bit Settings
// CONFIG BITS
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 4000000 // Internal oscillator
/****************************************************************/
/* Built-in delay routine     */
/****************************************************************/
#pragma intrinsic(_delay)
extern void _delay(unsigned long);
// NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
// Pinout definitions
// Relay activation pin
#define MORSE_RELAY PORTBbits.RB0
#define TRIS_MORSE_RELAY TRISBbits.TRISB0
// Message reset LED pin (for example)
#define MESSAGE_RESTART PORTBbits.RB1
#define TRIS_MESSAGE_RESTART TRISBbits.TRISB1
// Morse timing is rather precise, see the following references for more information
// @see http://sv8gxc.blogspot.de/2010/09/morse-code-101-in-wpm-bw-snr.html
// @see http://morsecode.scphillips.com/jtranslator.html
//
// Dot length (Seconds) = 1.2 / Speed (WPM)
// where typical WPM is 20... which is already very fast !
//
// Choosen 10 WPM : 1.2 / 10 = 0.12s : 120ms
#define DOT_LENGTH 120
#define DASH_LENGTH (DOT_LENGTH * 3)
#define LETTER_SEPARATOR DOT_LENGTH
#define WORD_SEPARATOR (DOT_LENGTH * 7)
#define PIN_ON 1
#define PIN_OFF 0
const char *code[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char message[] = "AU QG ARMEE DU POTOMAC DU DEPARTEMENT GUERRE WASHINGTON";


// main loop
void main() {
    TRIS_MORSE_RELAY = 0; // Make it an output;
    TRIS_MESSAGE_RESTART = 0; // Make it an output;
    while (1) {
        MORSE_RELAY = MESSAGE_RESTART = PIN_ON;
        __delay_ms(WORD_SEPARATOR);
        MORSE_RELAY = MESSAGE_RESTART = PIN_OFF;
        __delay_ms(WORD_SEPARATOR);
        for (int i = 0; i < strlen(message); i++) {
            char letter = message[i];
            if (letter == ' ') {
                MESSAGE_RESTART = PIN_ON;
                __delay_ms(WORD_SEPARATOR);
                MESSAGE_RESTART = PIN_OFF;
                continue;
            }
            int pos = (int)letter-(int)'A';
            char *morseCode = (char*) code[pos];
            int numElem = strlen(morseCode);
            for (int j = 0; j < numElem; j++) {
                char elem = morseCode[j];
                if (elem == '.') {
                    MORSE_RELAY = PIN_ON;
                    __delay_ms(DOT_LENGTH);
                } else if (elem == '-') {
                    MORSE_RELAY = PIN_ON;
                    __delay_ms(DASH_LENGTH);
                }
                MORSE_RELAY = PIN_OFF;
                __delay_ms(LETTER_SEPARATOR);
            }//for morse code char
        }//for message
    }
}
