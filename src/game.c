/* This file handles the game and the game loop */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

#define HITBOX_OFFSET 2

Dog player;
// Test structs, implement array with multiple structs instead
Hydrant hydrant;
Bee bee;
Point top_left_dog, bot_left_dog, top_right_dog, bot_right_dog, top_left_hydrant, bot_left_hydrant, top_right_hydrant, bot_right_hydrant;

int jump_timer = 0; // Intitiate jump timer
int game_state = 0; // 0 (Menu), 1(Game), 2(Pause), 3(highscore)

const int DOG_SPAWN_Y = 23;
const int DOG_SPAWN_X = 20;
const int HYDRANT_SPAWN_Y = GROUND_LEVEL - FH_HEIGHT;
const int JUMP_HEIGHT = 6; // Jump vertical boundary

const int DOG_HITBOX_HEIGHT = DOG_HEIGHT + (2 * HITBOX_OFFSET);
const int DOG_HITBOX_WIDTH = DOG_WIDTH + (2 * HITBOX_OFFSET);
const int HYDRANT_HITBOX_HEIGHT = FH_HEIGHT + (2 * HITBOX_OFFSET);
const int HYDRANT_HITBOX_WIDTH = FH_WIDTH + (2 * HITBOX_OFFSET);

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
int check_collision(Point top_left_dog, Point bot_left_dog, Point top_right_dog, Point bot_right_dog,
                    Point top_left_hydrant, Point bot_left_hydrant, Point top_right_hydrant, Point bot_right_hydrant)
{
    // Check if any of the conditions for non-collision are true
    if (
        (bot_left_hydrant.x >= bot_left_dog.x && bot_left_hydrant.x <= bot_right_dog.x && bot_left_hydrant.y >= bot_left_dog.y && bot_left_hydrant.y <= top_left_dog.y) ||
        (bot_right_hydrant.x >= bot_left_dog.x && bot_right_hydrant.x <= bot_right_dog.x && bot_right_hydrant.y >= bot_left_dog.y && bot_right_hydrant.y <= top_left_dog.y) ||
        (top_left_hydrant.x >= bot_left_dog.x && top_left_hydrant.x <= bot_right_dog.x && top_left_hydrant.y >= bot_left_dog.y && top_left_hydrant.y <= top_left_dog.y) ||
        (top_right_hydrant.x >= bot_left_dog.x && top_right_hydrant.x <= bot_right_dog.x && top_right_hydrant.y >= bot_left_dog.y && top_right_hydrant.y <= top_left_dog.y))
    {
        return 1; // Collision detected
    }
    else
    {
        return 0; // No collision
    }
}

void collision(Point top_left_dog, Point bot_left_dog, Point top_right_dog, Point bot_right_dog,
               Point top_left_hydrant, Point bot_left_hydrant, Point top_right_hydrant, Point bot_right_hydrant)
{
    // Check collision between player and hydrant
    int is_collision = check_collision(top_left_dog, bot_left_dog, top_right_dog, bot_right_dog,
                                       top_left_hydrant, bot_left_hydrant, top_right_hydrant, bot_right_hydrant);

    if (is_collision == 1)
    {
        // Handle collision action, e.g., end the game, decrease player health, etc.
        game_state = 0; // Set game state to menu or any other appropriate state
    }
}

void update_dog_hitbox()
{
    // Update hitbox coordinates based on the player's position

    // Top left corner
    top_left_dog.x = player.x - HITBOX_OFFSET;
    top_left_dog.y = player.y - HITBOX_OFFSET;

    // Update other corners based on width and height
    bot_left_dog.x = top_left_dog.x;
    bot_left_dog.y = top_left_dog.y + DOG_HITBOX_HEIGHT;

    top_right_dog.x = top_left_dog.x + DOG_HITBOX_WIDTH;
    top_right_dog.y = top_left_dog.y;

    bot_right_dog.x = top_left_dog.x + DOG_HITBOX_WIDTH;
    bot_right_dog.y = top_left_dog.y + DOG_HITBOX_HEIGHT;
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
            // update_dog_hitbox();
        }
    }

    // Update hitbox
}

void update_hydrant_hitbox()
{
    // Update hydrant hitbox coordinates based on the hydrant's position

    // Top left corner
    top_left_hydrant.x = hydrant.x;
    top_left_hydrant.y = hydrant.y;

    // Update other corners based on width and height
    bot_left_hydrant.x = top_left_hydrant.x;
    bot_left_hydrant.y = top_left_hydrant.y + HYDRANT_HITBOX_HEIGHT;

    top_right_hydrant.x = top_left_hydrant.x + HYDRANT_HITBOX_WIDTH;
    top_right_hydrant.y = top_left_hydrant.y;

    bot_right_hydrant.x = top_left_hydrant.x + HYDRANT_HITBOX_WIDTH;
    bot_right_hydrant.y = top_left_hydrant.y + HYDRANT_HITBOX_HEIGHT;
}
void update_bee()
{
    bee.x += bee.vel_x;
}
void update_hydrant()
{

    hydrant.y = HYDRANT_SPAWN_Y;
    hydrant.x += hydrant.vel_x; // Move x-position

    update_hydrant_hitbox();
}
void spawn_bee()
{
    bee.x = 128;
    bee.y = 10;

    bee.vel_x = -2;
    bee.vel_y = 2; // downwards to begin with
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
    // top_left_dog.x = player.x - HITBOX_OFFSET;
    // top_left_dog.y = player.y - HITBOX_OFFSET;

    // bot_left_dog.x = top_left.x;
    // bot_left_dog.y = top_left.y + HITBOX_HEIGHT;

    // top_right_dog.x = top_left.x + HITBOX_WIDTH;
    // top_right_dog.y = top_left.y;

    // bot_right_dog.x = top_left.x + HITBOX_WIDTH;
    // bot_right_dog.y = top_left.y + HITBOX_HEIGHT;
}

void player_jump()
{
    if (player.is_grounded == 1)
    {
        player.is_grounded = 0;
        player.vel_y = JUMP_FORCE;
    }
}

void update()
{
    // Check for updated states and movement
    if (check_buttons() == 2)
    {
        player_jump();
    }

    update_player();
    update_hydrant();
    update_bee();

    // collision(top_left_dog, bot_left_dog, top_right_dog, bot_right_dog,
    //           top_left_hydrant, bot_left_hydrant, top_right_hydrant, bot_right_hydrant);

    // Display changes
    show_ground();
    display_figure(player.x, player.y, DOG_HEIGHT, DOG_WIDTH, dogPixels);
    display_figure(hydrant.x, hydrant.y, FH_HEIGHT, FH_WIDTH, hydrantPixels);
    display_figure(bee.x, bee.y, BEE_HEIGHT, BEE_WIDTH, beePixels);
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
            spawn_bee();
            game_loop();
            while (check_switches() == 2)
            {
                highscore();
            }

            break;
        case 2:
            // Pause
            break;
        case 3:
            // Highscore
            highscore();
            break;
        default:
            menu();
            break;
        }

        // Check switches on every iteration (4 bit value meaning 0-15)
        int temp = game_state; // temporary value for comparing switch combinations
        if (game_state == 0 && check_buttons() == 4)
        {
            game_state = 1;
        }
        if (game_state != 1)
        {
            game_state = check_switches();
        }
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

        update_hydrant();
    }

    // If game loop is broken, go the screen select
    select_screen();
}

void is_collision(int g)
{
    game_state = 0;
    select_screen();
}