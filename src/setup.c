/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "t_rex.h"

char textbuffer[4][16];

// Define the T-Rex pixel data in a bit map
const uint8_t const trexPixels[T_REX_HEIGHT][T_REX_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 0}};
