/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

char textbuffer[4][16];

// Define the Dog pixel data in a bit map
const uint8_t const dogPixels[DOG_HEIGHT][DOG_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 0}};

const uint8_t const hydrantPixels[FH_HEIGHT][FH_WIDTH] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0},

};