/*
This file contains functions and variables for initiating and handling different maps/difficulties of the game.

Include Statements:
- <stdint.h>: Declarations of uint_32 and similar types.
- <pic32mx.h>: Declarations of system-specific addresses and configurations.
- "dog.h": Custom header file with declarations and configurations.

Data Structure:
- Map: Structure representing a game map with hydrants and bees. Each map has different characteristics such as timers, sizes, and initial positions.

Global Variable:
- maps: An array of Map structures representing different difficulty levels (easy, medium, hard).

Functions:
- reset_map(Map *map, int size): Resets all the elements of a given map, including hydrants and bees, by setting initial spawn values.

Note: Portions of the code are marked as "TAKEN FROM LAB," indicating code derived from a laboratory setting.

Author: [Erik Smit, Hugo Larsson Wilhelmsson]
Date: [2023-12-06]
*/

#include <stdint.h>
#include <pic32mx.h>
#include "dog.h"

// Array of maps, index 0 (easy), 1 (medium), 2 (hard)
Map maps[3] = {
    // Easy Map
    {
        .next_hydr = -1,
        .next_bee = -1,
        .hydr_timer = 30,
        .bee_timer = 50,
        .real_size = 2,
        .hydrants = {
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -2, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -2, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        .bees = {
            {128 - BEE_WIDTH, 17, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 18, -1, -1, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
        }
    },
    // Medium map
    {
        .next_hydr = -1,
        .next_bee = -1,
        .hydr_timer = 20,
        .bee_timer = 30,
        .real_size = 3,
        .hydrants = {
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {0, 0, 0, 0}
        },
        .bees = {
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {0, 0, 0, 0, 0, 0}
        }
    },
    // Hard map
    {
        .next_hydr = -1,
        .next_bee = -1,
        .hydr_timer = 20,
        .bee_timer = 25,
        .real_size = 4,
        .hydrants = {
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0},
            {128 - FH_WIDTH, GROUND_LEVEL - FH_HEIGHT, -3, 0}
        },
        .bees = {
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0},
            {128 - BEE_WIDTH, 10, -1, -1, 0, 0}
        }
    }
};

/*
Resets all the maps by setting initial spawn values.

Input:
- Map *map: Pointer to the map structure to be reset.
- int size: Size of the map, specifying the number of elements to reset.

Output: None
*/
void reset_map(Map *map, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        // Reset hydrants
        map->hydrants[i].x = 128 - FH_WIDTH;
        map->hydrants[i].y = GROUND_LEVEL - FH_HEIGHT;
        map->hydrants[i].is_active = 0; // set inactive
        map->next_hydr = -1;            // Index count starts at 0, so set to negative 1

        // Reset bees
        map->bees[i].x = 128 - BEE_WIDTH;
        map->bees[i].y = 10;
        map->bees[i].vel_x = -1;
        map->bees[i].vel_y = -1;
        map->bees[i].y_mov = 0;
        map->bees[i].is_active = 0;
        map->next_bee = -1;
    }
}

