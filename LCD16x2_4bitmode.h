#ifndef LCD16X2_4BITMODE_H_
#define LCD16X2_4BITMODE_H_
#endif /* LCD16X2_4BITMODE_H_ */

#include <msp430g2553.h>

#define D4  BIT0
#define D5  BIT1
#define D6  BIT2
#define D7  BIT3
#define RS  BIT4
#define EN  BIT5


//calibrar MSP a 1 MHz

#define DELAY   __delay_cycles(60)     //tiempo para las demás instrucciones
#define delayWD __delay_cycles(45)   // tiempo para ejecutar la instrucción write data
#define DELAY_RH __delay_cycles(1550) //tiempo para ejectuar la instrucción Return Home
#define DELAY_LONG __delay_cycles(250000)

//Para secuencia de inicialización en 4 bits (diagrama de flujo hoja de datos pagina 46 del Hitachi HD44780U)
#define DELAY_INIT_0  __delay_cycles(60000)
#define DELAY_INIT_1  __delay_cycles(4100)
#define DELAY_INIT_2  __delay_cycles(250)


/*Para escribir al registro de comando o de datos:
* RS = 1 —–> Data Register
* RS = 0 —–> Command Code Register
*/

#define COMM_REG P1OUT &=~RS
#define DATA_REG P1OUT |=RS
#define COMM 0
#define DATA 1

//En el pin E (enable), el edge Hi to Low indica escritura:
void EN_HIGH_TO_LOW(void);
void init4bitmode(void);
void initLCD(void);
void clearLCD(void);
void sendLCD(unsigned char byte, unsigned char RS_flag);
void positionLCD(unsigned char pos);
void writeLCD(char *s);



