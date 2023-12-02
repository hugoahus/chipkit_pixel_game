/* This file handles the game and the game loop */

#include <stdio.h>
#include <string.h>

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

#define HITBOX_OFFSET 2
#define NR_OF_OBJ 5

Dog player;

// Test structs, implement array with multiple structs instead
// Bee bee;
// Bee bees[NR_OF_OBJ];

int jump_timer = 0; // Intitiate jump timer
int game_state = 0; // 0 (Menu), 1(Game), 2(Pause), 3(highscore)
int map_index = 0;  // Decides which map/difficulty, easy by default
int score = 0;      // keeps track of score

// Timer stuff
int spawn_count = 0;

// Constants (may be moved)
const int DOG_SPAWN_Y = 23;
const int DOG_SPAWN_X = 20;
const int HYDRANT_SPAWN_Y = GROUND_LEVEL - FH_HEIGHT;
const int JUMP_HEIGHT = 6; // Jump vertical boundary

/* Turns on the display pixels for the static ground (which is a line of pixels)*/
void show_ground()
{
    int c;
    for (c = 0; c < COLUMNS; c++)
    {
        display[GROUND_LEVEL][c] = 1;
    }
}

/* Changes the players position  */
void update_player()
{
    if (!player.is_grounded)
    {

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
    display_figure(player.x, player.y, DOG_HEIGHT, DOG_WIDTH, dogPixels);
}

/* Updates the position of all the active bees*/
void update_bees(Map *map)
{
    int i;
    if ((spawn_count % map->bee_timer) == 0 && map->next_bee < map->real_size)
    {
        (map->next_bee)++;
        map->bees[map->next_bee].is_active = 1;
    }
    for (i = 0; i < map->real_size; i++)
    {
        if (map->bees[i].is_active)
        {
            map->bees[i].x += map->bees[i].vel_x;
            if (map->bees[i].y_mov >= 4)
            {
                map->bees[i].vel_y *= -1;
                map->bees[i].y_mov = 0;
            }
            map->bees[i].y += map->bees[i].vel_y;
            (map->bees[i].y_mov)++;
            // Check boundary
            if (map->bees[i].x < 0)
            {
                map->bees[i].x = 124;
            }
            display_figure(map->bees[i].x, map->bees[i].y, BEE_HEIGHT, BEE_WIDTH, beePixels);
        }
    }
}
void update_hydrants(Map *map)
{
    int i;
    if ((spawn_count % map->hydr_timer) == 0 && map->next_hydr < map->real_size)
    {
        (map->next_hydr)++;
        map->hydrants[map->next_hydr].is_active = 1;
    }
    for (i = 0; i < map->real_size; i++)
    {
        if (map->hydrants[i].is_active)
        {
            map->hydrants[i].y = HYDRANT_SPAWN_Y;
            map->hydrants[i].x += map->hydrants[i].vel_x; // Move x-position
            // Check boundary (fixes weird y-movement on end of screen)
            if (map->hydrants[i].x < 0)
            {
                map->hydrants[i].x = 126;
            }
            display_figure(map->hydrants[i].x, map->hydrants[i].y, FH_HEIGHT, FH_WIDTH, hydrantPixels);
        }
    }
}

/* Function for spawning character and environment on game start*/
void spawn_player()
{
    player.is_grounded = 1; // Set on ground
    player.x = DOG_SPAWN_X;
    player.y = DOG_SPAWN_Y;
    player.vel_y = 0;
}

/* Function that handles the*/

void player_jump()
{
    if (player.is_grounded == 1)
    {
        player.is_grounded = 0;
        player.vel_y = JUMP_FORCE;
    }
}

/* Main update function */
void update()
{
    int i;
    // Check for updated states and movement
    if (check_buttons() == 3)
    {
        player_jump();
    }

    update_player();
    // Display changes

    update_bees(&maps[map_index]);
    update_hydrants(&maps[map_index]);

    show_ground();

    // Increment spawn count for bee and hydrant
    spawn_count++;
}

void start_game()
{
    clear_text_buffer();
    jump_timer = 0; // reset jump timer so that flying dog bug doesnt happen
    // Set the intitial spawn locations of the characters whick starts the game

    reset_map(&maps[map_index], maps[map_index].real_size);
    spawn_player();

    game_loop();
}

/* This function evaluates the toggle switches and chooses screen accordingly*/
void select_screen()
{
    int button = 0;
    // Clear all current pixels on the display

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
            start_game();
            break;
        case 2:
            // Highscore
            highscore();
            break;
        case 4:
            // Choose difficulty
            choose_diff();
            button = check_buttons();
            if (button > 0)
            {
                map_index = button - 2;
            }
            break;
        default:
            menu();
            break;
        }

        // Check switches on every iteration (4 bit value meaning 0-15)
        int temp = game_state; // temporary value for comparing switch combinations
        // Starts game
        if (game_state == 0 && check_buttons() == 4)
        {
            game_state = 1;
        }
        // Change game_state when not in game
        if (game_state != 1)
        {
            game_state = check_switches();
        }
        // Clear display only if there is another switch combination
        if (temp != game_state)
        {
            clear_text_buffer();
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

        //  Pause Screen
        while (check_switches() == 5)
        {
            pause();
        }
        // Reset game
        if (check_buttons() == 2)
        {
            start_game();
        }
    }

    // If game loop is broken, go the screen select
    select_screen();
}

/* Function is called when game is over (collision)*/
void game_over()
{

    // Save highscore

    //
}

void is_collision(int g)
{
    game_state = 0;
    select_screen();
}