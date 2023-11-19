/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "t_rex.h"

/* Display constants */
#define GROUND_LEVEL 29 // which row that is ground level
#define COLUMNS 128		// nr of columns
#define ROWS 32			// nr of rows
#define BOX_SIZE 4

// Define a structure with two int arrays
struct Box
{
	int box_x[BOX_SIZE];
	int box_y[BOX_SIZE];
};

struct Box player; // Global for testing

char textbuffer[4][16];

/* Turns on the display pixels for the static ground (which is a line of pixels)*/
void spawn_ground()
{
	int c;
	for (c = 0; c < COLUMNS; c++)
	{
		display[GROUND_LEVEL][c] = 1;
	}
}

void spawn_box()
{

	int i;
	int j;

	for (i = 0; i < BOX_SIZE; i++)
	{
		for (j = 0; j < BOX_SIZE; j++)
		{
			display[player.box_y[j]][player.box_x[i]] = 1;
		}
	}
}

/* Takes in start posotion of box, top left corner (x,y)*/
void preload_box(struct Box *box, int start_x, int start_y)
{
	int i;

	for (i = 0; i < BOX_SIZE; i++)
	{
		box->box_x[i] = i + start_x;
		box->box_y[i] = i + start_y;
	}
}

/* Function for spawning character and environment on game start*/
void setup_spawn()
{
	preload_box(&player, 100, (GROUND_LEVEL - 5)); // Preload/create a box
	spawn_ground();
	spawn_box();
}