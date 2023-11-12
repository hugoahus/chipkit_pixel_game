/* THIS IS THE HEADER FILE FOR THE PROJECT*/

void display_init(void);
void display_update(void);
void display_start(void);
uint8_t spi_send_recv(uint8_t data);

/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson
   Latest update 2015-08-28 by F Lundevall
   For copyright and licensing, see file COPYING */

// Declare display related functions
void quicksleep(int cyc);
void display_image(int x, const uint8_t *data);
void display_string(int line, char *s);
void display_update(void);
void display_clear(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare display_debug - a function to help debugging.
   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.
   There's one parameter: the address to read and display.
   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug(volatile int *const addr);

/* Declare text buffer for display output */
extern char textbuffer[4][16];
