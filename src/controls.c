/*
    This file is written 2023 by Hugo Larsson Wilhelmsson
    Description: Declarations for the controls and related functions used in the labs.
*/

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses, etc. */
#include "dog.h"     /* Declarations for these labs */

/*
    Function: void user_isr(void)
    Description: Interrupt Service Routine. Placeholder function for user-defined interrupt service routine.
    Returns: void
*/

int lights = 0x7;

// Create a volatile pointer to the PORTE register
volatile uint32_t *porte = (volatile uint32_t *)0xbf886110;

void user_isr(void)
{
    return;
}

/*
    Function: void controls_init(void)
    Description: Initialization function for the controls. Sets bits 11 through 5 as input in port D.
    Returns: void
*/

void controls_init(void)
{
    // Create a volatile pointer to the TRISE register at address 0xbf886100
    volatile uint32_t *trise = (volatile uint32_t *)0xbf886100;
    // Set the lower 8 bits of TRISE to configure Port E as outputs
    *trise &= 0xFFFFFF00;

    // Clear the lower bits of porte

    // Set bits 11 through 5 as input in port D
    volatile int *trisd = (volatile int *)0xbf8860d0;
    *trisd = *trisd | 0x0fe0;

    T2CON = 0x00008070; //  configured using family reference manual

    TMR2 = 0x0; // clear Timer 2 counter

    // PR2 - Timer 2 Period Register: The PR2 register is used to set the period for Timer 2,
    // which defines the time between time-out events. The calculation for setting the period as follows:
    // Given a desired time between time-out events of 100 milliseconds (10 timeouts per second)
    // Assuming an 80 MHz clock, divide by 256 (due to the prescaling of 1:256) to get the timer frequency
    // Then divide by 10 to achive 10 timeouts per second
    // This gives 80,000,000 / 256 / 10 = 31,250 (0x7A12 in Hexadecimal)
}

/*
    Function: int getsw(void)
    Description: Reads the state of the switches. The switches are connected to bits 8-11 on PORTD. Performs a right shift by 8 positions and then returns the last 4 bits that represent the switches.
    Returns: An integer representing the state of the switches (bits 0, 1, 2, and 3 of the returned value).
*/

int getsw(void)
{
    return (PORTD >> 8) & 0xF;
}

/*
    Function: int getbtns(void)
    Description: Reads the state of the buttons BTN2, BTN3, and BTN4. The buttons are connected to bits 5-7 on PORTD. Performs a right shift by 5 positions and then applies a bitwise AND operation with 0x7 (binary 0111) to mask and isolate the button states.
    Returns: An integer representing the state of BTN2, BTN3, and BTN4 (bits 0, 1, and 2 of the returned value).
*/

int getbtns(void)
{
    return (PORTD >> 5) & 0x7;
}

/*
    Function: int check_switches(void)
    Description: Checks the state of the switches using the getsw() function and returns a corresponding value based on the switch state. The switch values are interpreted as follows:
        - 0x1: Returns 5
        - 0x2: Returns 2
        - 0x3: Returns 3
        - 0x4: Returns 4
        - Default: Returns 0
    Returns: An integer representing the interpreted state of the switches.
*/

int check_switches(void)
{
    int sw = getsw();

    if (sw == 0x1)
    {
        return 5;
    }
    else if (sw == 0x2)
    {
        return 2;
    }
    else if (sw == 0x3)
    {
        return 3;
    }
    else if (sw == 0x4)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

/*
    Function: int check_buttons(void)
    Description: Checks the state of the buttons using the getbtns() function and returns a corresponding value based on the button state. The button values are interpreted as follows:
        - 0x1: Returns 2
        - 0x2: Returns 3
        - 0x4: Returns 4
    Returns: An integer representing the interpreted state of the buttons.
*/

int check_buttons(void)
{
    int btn = getbtns();

    // Button 2
    if ((btn & 0x1) == 1)
    {
        return 2;
    }
    // Button 3
    else if ((btn & 0x2) == 2)
    {
        return 3;
    }
    // Button 4
    else if ((btn & 0x4) == 4)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

void show_lives(int lights)
{
    *porte &= 0xFFFFFF00; // Clear the lower 8 bits of porte
    *porte |= lights;
}