/* This file handles the game and the game loop */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

#define HITBOX_OFFSET 2

Dog player;
Hydrant hydrant;
Point top_left, bot_left, top_right, bot_right;

int jump_timer = 0; // Intitiate jump timer
int game_state = 1; // 0 (Menu), 1(Game), 2(Pause), 3(highscore)

const int DOG_SPAWN_Y = 23;
const int DOG_SPAWN_X = 20;
const int HYDRANT_SPAWN_Y = GROUND_LEVEL - FH_HEIGHT;
const int JUMP_HEIGHT = 6; // Jump vertical boundary

const int HITBOX_HEIGHT = DOG_HEIGHT + (2 * HITBOX_OFFSET);
const int HITBOX_WIDTH = DOG_WIDTH + (2 * HITBOX_OFFSET);

/* Turns on the display pixels for the static ground (which is a line of pixels)*/
void show_ground()
{
    int c;
    for (c = 0; c < COLUMNS; c++)
    {
        display[GROUND_LEVEL][c] = 1;
    }
}

/* Collision with objects */
void collision()
{
    int x = top_right.x;
    int y;
    for (y = top_left.y; y <= bot_right.y; y++)
    {
        if (display[y][x] == 1)
        {
            game_state = 0;
        }
    }
}

/* Changes the players position  */
void update_player()
{
    if (!player.is_grounded)
    {
        // TODO: Update hitbox coordinates so it follows the characters sprite

        player.y += player.vel_y; // Decrement the y position
        jump_timer++;

        // Turning point
        if (jump_timer == JUMP_HEIGHT)
        {
            player.vel_y *= -1;
        }
        // Check if character has landed
        if (player.y >= DOG_SPAWN_Y)
        {
            player.y = DOG_SPAWN_Y;
            player.is_grounded = 1; // Set is_grounded to true
            player.vel_y = 0;
            jump_timer = 0; // Reset jump timer so that dog doesnt fly away
        }
    }

    // Update hitbox
}

void update_hydrant()
{

    hydrant.y = HYDRANT_SPAWN_Y;
    hydrant.x += hydrant.vel_x; // Move x-position

    // TODO: Update the hydrants hitbox
}
/* Test function for spawning a hydrant*/
void spawn_hydrant()
{
    hydrant.x = 128 - FH_WIDTH;
    hydrant.y = HYDRANT_SPAWN_Y;
    hydrant.vel_x = -2; // Set test speed of 2 pixels

    // Spawn Hitbox to hydrant
}
/* Function for spawning character and environment on game start*/
void spawn_player()
{
    player.is_grounded = 1; // Set on ground
    player.x = DOG_SPAWN_X;
    player.y = DOG_SPAWN_Y;
    player.vel_y = 0;

    // Initiate points for players hitbox
    top_left.x = player.x - HITBOX_OFFSET;
    top_left.y = player.y - HITBOX_OFFSET;

    bot_left.x = top_left.x;
    bot_left.y = top_left.y + HITBOX_HEIGHT;

    top_right.x = top_left.x + HITBOX_WIDTH;
    top_right.y = top_left.y;

    bot_right.x = top_left.x + HITBOX_WIDTH;
    bot_right.y = top_left.y + HITBOX_HEIGHT;
}

void player_jump()
{
    if (player.is_grounded == 1)
    {
        player.is_grounded = 0;
        player.vel_y = JUMP_FORCE;
    }
}
/* This function check for button presses and handles it accordingly */
void check_buttons()
{
    int btn = getbtns();

    // Button 2 makes the player jump when pressed
    if ((btn & 0x1) == 1)
    {
        player_jump();
    }
}

void update()
{
    // Check for updated states and movement
    check_buttons();
    update_player();
    update_hydrant();
    collision();

    // Display changes
    show_ground();
    vertical_line(top_right.x, &top_right, &bot_right);
    display_figure(player.x, player.y, DOG_HEIGHT, DOG_WIDTH, dogPixels);
    display_figure(hydrant.x, hydrant.y, FH_HEIGHT, FH_WIDTH, hydrantPixels);
}

/* This function check for switch toggles and handles it accordingly */
int check_switches()
{
    int sw = getsw();
    if (sw == 0x1)
    {
        return 1;
    }

    {
        return 0;
    }
}

/* This function evaluates the toggle switches and chooses screen accordingly*/
void select_screen()
{
    // Clear all current pixels on the display
    display_reset();

    while ((game_state >= 0 && game_state < 16))
    {
        switch (game_state)
        {
        case 0:
            // Menu
            menu();
            break;
        case 1:
            // Game loop

            // Set the intitial spawn locations of the characters
            spawn_player();
            spawn_hydrant();
            game_loop();
            break;
        case 2:
            // Highscore
            highscore();
            break;
        case 3:
            // Pause
            break;
        default:
            menu();
            break;
        }

        // Check switches on every iteration (4 bit value meaning 0-15)
        int temp = game_state; // temporary value for comparing switch combinations
        game_state = getsw();
        if (temp != game_state)
        {
            // Clear display only if there is another switch combination
            display_reset();
        }
    }
}

/* Main game function */
void game_loop()
{

    while (game_state == 1)
    {
        display_clear();
        update();
        display_change();
        delay(FRAME_SPEED);

        game_state = check_switches();
    }

    // If game loop is broken, go the screen select
    select_screen();
}