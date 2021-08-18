#include "LCD16x2_4bitmode.h"

/*
 * Display LCD 16x2 en modo 4 bits, utilizar fuente externa de 5V.
 *
 * Pines 1, 5 y 16 - GND (Como solo es escritura, Pin 5 (R/W) va a GND)
 * Pin 2 - Vcc a 5V
 * Pin 3 - potenciómetro para contraste
 * Pin 15 (LEDS) a 5V con resistencia de 330 Ohms aprox
 *
 * Conexiones al MSP:
 *
 *  MSP         LCD
 *
 *  PORT1.0     D4
 *  PORT1.1     D5
 *  PORT1.2     D6
 *  PORT1.3     D7
 *  PORT1.4     RS
 *  PORT1.5     EN
 *
*/

void main(void)
{

    volatile unsigned int i;

    //CLK a 1 MHz
    if (CALBC1_1MHZ==0xFF)
    {
        while(1);
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

	WDTCTL = WDTPW + WDTHOLD;

	P1OUT = 0;
	P1DIR |= D4 + D5 + D6 + D7 + RS + EN;

	init4bitmode();
	initLCD();

	writeLCD("SECUENCIADORES Y");
	positionLCD(16);
	writeLCD("MICROPROCESADORES 18I");

	/*__delay_cycles(500000);

	for (i=0; i<8; i++)
	{
	    sendLCD(0x18, COMM);
	    __delay_cycles(500000);
	}
	for (i=0; i<8; i++)
	    {
	        sendLCD(0x1C, COMM);
	        __delay_cycles(500000);
	    }
	__delay_cycles(1000000);
	clearLCD();*/
}
