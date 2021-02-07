/* Selman Tabet (@selmantabet - https://selman.io/) - UIN 724009859
Assignment 2 - Question 1

This function lets LED1 on the board to flash rapidly.
Assuming the board operates at a 1.5MHz frequency, the LED would turn on
for 2 seconds, and off for a second. The LED light is Active Low.

Tested on an EA LPC4088 QuickStart Board and a PC
running Windows 10 Pro x64 19042.789 (20H2).
*/
#include "mbed.h"
#define LPC_SC_PCONP          (*((volatile unsigned long *) 0x400FC0C4))
#define GPIO1_DIR             (*((volatile unsigned long *) 0x20098020))
#define GPIO1_SET             (*((volatile unsigned long *) 0x20098038))
#define GPIO1_CLEAR           (*((volatile unsigned long *) 0x2009803C))

//Simple software delay
void delay(int time){
    volatile int i;
    for(i=0; i<1500000*time; i++); //Assuming 1.5MHz frequency **READ REPORT**
}

int main(void){
    //Enable the power/clock on the GPIO peripheral.
    //See page 30 in UM10562 (Setting Bit 15 in the PCONP register).
    LPC_SC_PCONP |= 0x8000; 
    //Table 84: LED1 = P1[18]
    GPIO1_DIR |= 0x1 << 18; //Set the direction of Pin 18 of Port 1 to output.

    //Blinking LED1 which is connected to PIN18 of Port 1.
    while (1){ //Run forever.
        GPIO1_SET |= 0x1 << 18;  //Turn LED off.
        delay(1);
        GPIO1_CLEAR |= 0x1 << 18; //Turn LED on.
        delay(2);
    }
}