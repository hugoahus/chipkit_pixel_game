/* This file handles the game and the game loop */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "t_rex.h"

Dog player;
int jump_timer = 0;
const int DOG_SPAWN_Y = GROUND_LEVEL - DOG_HEIGHT;
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

/* Changes the players position  */
void update_player()
{
    if (!player.is_grounded)
    {

        player.y += player.vel_y; // Decrement the y position
        jump_timer++;

        // Turning point
        if (jump_timer == 6)
        {
            player.vel_y *= -1;
        }
        // Check if character has landed
        if (player.y >= DOG_SPAWN_Y)
        {
            player.y = DOG_SPAWN_Y;
            player.is_grounded = 1; // Set is_grounded to true
            player.vel_y = 0;
        }
    }
}
void show_trex()
{
    int i, j;
    for (i = 0; i < DOG_HEIGHT; i++)
    {
        for (j = 0; j < DOG_WIDTH; j++)
        {
            if (trexPixels[i][j])
            {
                display[i + player.y][j + player.x] = 1;
            }
        }
    }
}
void update()
{
    update_player();
    show_trex();
    show_ground();
}

/* Function for spawning character and environment on game start*/
void setup_spawn()
{
    player.is_grounded = 1; // Set on ground
    player.x = 30;
    player.y = DOG_SPAWN_Y;
    player.vel_y = 0;
}

void player_jump()
{
    if (player.is_grounded == 1)
    {
        player.is_grounded = 0;
        player.vel_y = JUMP_FORCE;
    }
}

/* Main game function */
void game()
{
    setup_spawn();
    player_jump();
    while (1)
    {
        display_clear();
        update();
        display_change();
        delay(FRAME_SPEED);
    }
}