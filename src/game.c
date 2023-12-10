/*
This file is written 2023 by Erik Smit and Hugo Larsson Wilhelmsson.
This file handles the game and the game loop.
*/

#include <stdio.h>
#include <string.h>

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

Dog player;
int temp_timer = 0; // Saves a timer value for seed on game start
// Highscore list with predefined values
Highscore highscores[NR_OF_HIGHSCORES] = {
    {"AXE", 8},
    {"BOB", 4},
    {"CAT", 1},
};

char player_name[] = {0x41, 0x41, 0x41}; // Default value for player name (AAA)
int player_lives = 0x7;                  // Corresponds to lights also

const int spawn_y_levels[] = {BEE_MIN_Y, BEE_MAX_Y};

int game_delay = FRAME_SPEED;

int jump_timer = 0;    // Intitiate jump timer
int game_state = 0;    // 0 (Menu), 1(Game), 2(Pause), 3(highscore)
int map_index = 0;     // Decides which map/difficulty, easy by default
unsigned int seed = 0; // Depends on how long time the player takes to start the game

int score_lim = 20; // Decides after how many delays the score should be updated
int score = 0;      // Keeps track of score

// Timer stuff
int spawn_count = 0;

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
        }
    }
    display_figure(player.x, player.y, DOG_HEIGHT, DOG_WIDTH, dogPixels);
}

void enemy_spawn(Map *map)
{
    if ((spawn_count % map->spawn_timer) == 0)
    {
        int enemy_type = custom_random(0, 1); // Generate random number for enemy type
        switch (enemy_type)
        {
        // Hydrant
        case 0:
            // Next hydrant can spawn

            // Restart the next_hydr index
            if (map->next_hydr >= map->real_size)
            {
                map->next_hydr = 0;
            }
            // Else increment next hydr
            else
            {
                (map->next_hydr)++;
            }
            map->hydrants[map->next_hydr].is_active = 1;

            break;
        // Bee
        case 1:
            // Restart the next_hydr index
            if (map->next_bee >= map->real_size)
            {
                map->next_bee = 0;
            }
            // Else increment next hydr
            else
            {
                (map->next_bee)++;
            }
            map->bees[map->next_bee].is_active = 1;
            // map->bees[map->next_bee].y = spawn_y_levels[custom_random(0, 1)];
            break;
        }
        maps[map_index].spawn_timer = custom_random(45, 100); // Generate new spawn timer
    }
}

/* Updates the position of all the active bees*/
void update_bees(Map *map)
{
    int i;

    // Update all the active bees
    for (i = 0; i < map->real_size; i++)
    {

        if (map->bees[i].is_active)
        {
            map->bees[i].x += map->bees[i].vel_x;

            // Bee vertical movement
            map->bees[i].y += map->bees[i].vel_y;

            // Check if bee has reached the target y-level
            if (map->bees[i].y <= BEE_MIN_Y) // Assuming BEE_MIN_Y is 12
            {
                // Set y to the target y-level
                map->bees[i].y = BEE_MIN_Y;
                // Reverse the vertical movement direction
                map->bees[i].vel_y *= -1;
            }
            else if (map->bees[i].y >= BEE_MAX_Y) // Assuming BEE_MAX_Y is 16
            {
                // Set y to the target y-level
                map->bees[i].y = BEE_MAX_Y;
                // Reverse the vertical movement direction
                map->bees[i].vel_y *= -1;
            }

            // Check boundary
            if (map->bees[i].x < BEE_S_WIDTH)
            {
                map->bees[i].is_active = 0;
                map->bees[i].y = spawn_y_levels[custom_random(0, 1)];
                map->bees[i].x = 128 - BEE_S_WIDTH;
            }
            else
            {
                display_figure(map->bees[i].x, map->bees[i].y, BEE_S_HEIGHT, BEE_S_WIDTH, beeAltPixels);
            }
        }
    }
}

/* Function that updates all the hydrant objects */
void update_hydrants(Map *map)
{
    int i;

    for (i = 0; i < map->real_size; i++)
    {
        if (map->hydrants[i].is_active)
        {
            map->hydrants[i].y = HYDRANT_SPAWN_Y;
            map->hydrants[i].x += map->hydrants[i].vel_x; // Move x-position
            // Check boundary (fixes weird y-movement on end of screen)
            if (map->hydrants[i].x < 0 + FH_WIDTH)
            {
                map->hydrants[i].is_active = 0;
                map->hydrants[i].x = 128 - FH_WIDTH;
            }
            else
            {
                display_figure(map->hydrants[i].x, map->hydrants[i].y, FH_HEIGHT, FH_WIDTH, hydrantPixels);
            }
        }
    }
}

/* Function for spawning character and environment on game start, sets values */
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
    // Check for updated states and movement
    if (check_buttons() == 3)
    {
        player_jump();
    }

    update_player();
    // Display changes
    enemy_spawn(&maps[map_index]);
    update_bees(&maps[map_index]);
    update_hydrants(&maps[map_index]);

    show_ground();

    // Increment spawn count for bee and hydrant
    spawn_count++;
}

/* This function initiates random elements for the different maps */
void random_map_elements()
{
    // Generate new seed
    temp_timer = TMR2;
    custom_seed_init(TMR2);
    int spawn_cont = maps[map_index].real_size; // Value used for spawning intervall to prevent colision

    // Test values
    maps[map_index].spawn_timer = custom_random(45, 100);
}

/* This functions starts the game and clears necessary stuff */
void start_game()
{
    // Implement random elements
    random_map_elements();

    // Score related actions
    display_clear();
    clear_text_buffer();

    show_lives(player_lives);

    jump_timer = 0; // Reset jump timer so that flying dog bug doesnt happen

    // Map and player spawns
    reset_map(&maps[map_index], maps[map_index].real_size);
    spawn_player();

    game_loop();
}

/* This function evaluates the toggle switches and chooses screen accordingly*/
void select_screen()
{
    int button = 0;

    seed++; // Increment seed (seed depends on the time it takes for the the player to start the game)

    while ((game_state >= 0 && game_state < 16))
    {
        // Switch case displaying the different screens

        switch (game_state)
        {
        case 0:
            // Menu
            menu();
            // Starts game
            if (check_buttons() == 4)
            {
                game_state = 1;
            }
            break;
        case 1:
            // Game loop
            display_score(score);
            display_update();
            game_delay = FRAME_SPEED; // Set original frame speed
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
                map_index = button - 2; // Convert btn press to index in maps array
            }
            break;
        default:
            menu();
            break;
        }

        // Check switches on every iteration (4 bit value meaning 0-15)
        int temp = game_state; // temporary value for comparing switch combinations
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

/* Evaluates if score */
void check_score()
{
    // Increase score and update display
    if (score_lim >= SCORE_TIMER)
    {
        score_lim = 0;
        score++;
        display_score(score);
        display_update();

        // Check to increase game speed
        if (score % 10 == 0 && game_delay > 25)
        {
            game_delay -= 15; // Increase refresh rate, increasing speed (fine tune value)
        }
    }
    score_lim++;
}

/* Main game function */
void game_loop()
{

    while (game_state == 1)
    {

        // Clear current object pixels on the screen (ALTERNATIVE WAY OF CLEARING PIXELS)
        // clear_enemies(&maps[map_index]);
        // clear_figure(player.x, player.y, DOG_HEIGHT, DOG_WIDTH);

        display_clear(); // alternative to above (clears the whole screen)

        // Evaluate the score
        check_score();

        // Update the display
        /* OBS, there is an issue with the display_change and display_update order that makes the screen flicker*/
        update();
        display_change();

        delay(game_delay);

        // Pause Screen
        while (check_switches() == 5)
        {
            // Still show score
            display_score(score);
            // TEST CODE FOR SEEING SEED
            char seed_str[8];
            int_to_str(temp_timer, seed_str);
            display_string(3, seed_str);
            pause();
        }
        // Clear game pause line
        display_string(1, "");
        display_string(2, "");
        display_string(3, "");
    }

    // If game loop is broken, go the screen select
    select_screen();
}

/* Function allows players to enter name, otherwise it uses the default name*/
void name()
{
    int sw = check_switches();
    while ((sw >= 0 && sw < 16))
    {
        switch (sw)
        {
        case 4:
            increment_hex(0);
            break;
        case 2:
            increment_hex(1);
            break;
        case 5:
            increment_hex(2);
            break;
        }
        // Press button 2 to confirm name
        if (check_buttons() == 2)
        {
            break;
        }
        clear_text_buffer();
        sw = check_switches();
        enter_name();
        delay(150); // Small delay to avoid screen flicker
    }
}

/* Checks and updates highscore if needed*/
int check_highscore()
{
    int i;
    int is_highscore = 0;
    int next_score = score;

    // Check if the current score is higher than any of the existing high scores
    for (i = 0; i < NR_OF_HIGHSCORES; i++)
    {
        if (next_score > highscores[i].score)
        {
            is_highscore = 1;
            // Shift down the existing high scores to make room for the new one
            int j;
            for (j = NR_OF_HIGHSCORES - 1; j > i; j--)
            {
                highscores[j] = highscores[j - 1];
            }

            // Insert the new high score
            highscores[i].score = next_score;

            // CHANGE PLAYER NAME HERE
            name();
            switch_names(highscores[i].name, player_name, highscores[i].name, player_name);

            break; // Exit the loop since the high score has been added
        }
    }
    return is_highscore;
}

/* Function is called when game is over (collision)*/
void game_over()
{
    player_lives >>= 1;

    if (player_lives < 1)
    {
        show_lives(player_lives);
        player_lives = 0x7;

        // Save highscore
        check_highscore();

        // Clear score
        clear_text_buffer();
        score = 0;
        game_state = 0;

        select_screen();
    }

    else
    {
        start_game();
    }
}
