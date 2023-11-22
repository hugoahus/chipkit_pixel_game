#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"   /* Declatations for these labs */

/* Interrupt Service Routine */
void user_isr(void)
{
    return;
}
/* Initiation function for the controls*/
void controls_init(void)
{
    // Set bits 11 through 5 as input in port D
    volatile int *trisd = (volatile int *)0xbf8860d0;
    *trisd = *trisd | 0x0fe0;
}
int getsw(void)
{
    /* The switches are connected to the bits 8-11 on
    PORTD. Right shift 8 steps then return the last
    4 bits that represent the switches
    */
    return (PORTD >> 8) & 0xF;
}

int getbtns(void)
{
    /* BTN2,BTN3,BT4 are connected to bit 5-7 on PORTD
    Right shift 5 spaces and then mask with 0111 */
    return (PORTD >> 5) & 0x7;
}