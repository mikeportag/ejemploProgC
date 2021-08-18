#include <LCD16x2_4bitmode.h>

void EN_HIGH_TO_LOW(void)
{
    //Para indicar en el bit de Enable que vamos a escribir:
    P1OUT |= EN;
    DELAY_INIT_2;
    P1OUT &= ~EN;
}

void sendLCD(unsigned char byte, unsigned char RS_flag)
{
    if (RS_flag == 0)
    {
        //Mandamos instrucción al registro de comandos:
        COMM_REG;
        //Enmascaramos para poner en bajo los bits D4-D7:
        P1OUT &= 0xF0;
        //Corrimiento para mandar los 4 bits más significativos primero:
        P1OUT |= (byte >> 4) & 0x0F;
        //Ejecutamos la escritura:
        EN_HIGH_TO_LOW();

        P1OUT &= 0xF0;
        //Mandamos los 4 bits menos significativos del comando:
        P1OUT |= byte & 0x0F;
        EN_HIGH_TO_LOW();

    }else{

        //Mandamos instrucción al registro de datos:
        DATA_REG;
        P1OUT &= 0xF0;
        P1OUT |= (byte >> 4) & 0x0F;
        EN_HIGH_TO_LOW();

        P1OUT &= 0xF0;
        P1OUT |= byte & 0x0F;
        EN_HIGH_TO_LOW();

    }
}

void positionLCD(unsigned char pos)
{
    //pos > 15 significa que se desea escribir en el segundo renglón, cuya dirección DDRAM empieza en 0x40:
    if (pos > 0x0F) pos = 0x40 + (pos- 0x10);
    //Comando para escribir a la DDRAM es 0x80:
    pos |=0x80;
    sendLCD(pos,COMM);
}

void clearLCD(void)
{
    sendLCD(0x01, COMM);
    DELAY_RH;
}

void writeLCD(char *s)
{
    while (*s)
    {
        sendLCD(*s, DATA);
        s++;
    }
}

void init4bitmode(void)
{
    //Rutina de inicialización de acuerdo al diagrama de flujo de la hoja de datos de Hitachi:

    //Asegurando que hayan pasado más de 40 ms después de que Vcc alcance los 2.7V:
    DELAY_INIT_0;

    //Escribiendo al registro de comandos:
    COMM_REG;

    //Caso especial de Function Set se repite 3 veces:
    P1OUT &= 0xF0;
    P1OUT |= D4 + D5;
    EN_HIGH_TO_LOW();
    DELAY_INIT_1;

    EN_HIGH_TO_LOW();
    DELAY_INIT_2;

    EN_HIGH_TO_LOW();
    DELAY_INIT_2;

    //Cambiando interface a 4 bits:
    P1OUT = 0x02;
    EN_HIGH_TO_LOW();
    DELAY_INIT_2;
}

void initLCD(void)
{
    //Modo 4 bit 2 líneas:
    sendLCD(0x28, COMM);
    DELAY;

    //Limpiar LCD:
    sendLCD(0x01, COMM);
    DELAY_RH;

    //Dirección de la RAM (en 0x0h):
    sendLCD(0x80, COMM);
    DELAY;

    //Display encendido y cursor con blink:
    sendLCD(0x0F, COMM);
    DELAY;

    //Dirección del desplazamiento del cursor:
    sendLCD(0x06, COMM);
    DELAY;
}





