/* This file handles the game and the game loop */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "t_rex.h"

// Define a structure with two int arrays

struct Dog player; // Global for testing

/* Turns on the display pixels for the static ground (which is a line of pixels)*/
void show_ground()
{
    int c;
    for (c = 0; c < COLUMNS; c++)
    {
        display[GROUND_LEVEL][c] = 1;
    }
}

// void show_box()
// {

//     int i;
//     int j;

//     for (i = 0; i < BOX_SIZE; i++)
//     {
//         for (j = 0; j < BOX_SIZE; j++)
//         {
//             display[player.box_y[j]][player.box_x[i]] = 1;
//         }
//     }
// }

/* Takes in start posotion of box, top left corner (x,y)*/
// void preload_box(struct Box *box)
// {
//     int i;

//     for (i = 0; i < BOX_SIZE; i++)
//     {
//         box->box_x[i] = i + box->start_x;
//         box->box_y[i] = i + box->start_y;
//     }
// }
void show_trex(int x, int y)
{
    int i, j;
    for (i = 0; i < T_REX_HEIGHT; i++)
    {
        for (j = 0; j < T_REX_WIDTH; j++)
        {
            if (trexPixels[i][j])
            {
                display[i + y + player.vel][j + x] = 1;
            }
        }
    }
}
void update()
{
    show_trex(20, (GROUND_LEVEL - T_REX_HEIGHT));
    show_ground();
}

/* Function for spawning character and environment on game start*/
void setup_spawn()
{
    player.x = 30;
    player.y = GROUND_LEVEL - 5;
    player.vel = 0;
}

void player_jump()
{
    player.vel = -10;
}

/* Main game function */
void game()
{
    // setup_spawn();
    player_jump(); // test
    while (1)
    {
        display_clear();
        update();
        display_change();
        player.vel++;
        delay(FRAME_RATE);
    }
}