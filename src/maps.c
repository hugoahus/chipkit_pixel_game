/* This file contains functions and variables
for intiating and handling different maps/difficulties of the game
*/

#include <stdint.h>
#include <pic32mx.h>
#include "dog.h"



// Array of maps, index 0 (easy), 1 (medium), 2(hard)
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



/* Resets all the maps by setting intial spawn values */
void reset_map(Map *map, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        // Reset hydrants
        map->hydrants[i].x = 128 - FH_WIDTH;
        map->hydrants[i].y = GROUND_LEVEL - FH_HEIGHT;
        map->hydrants[i].is_active = 0; // set inactive
        map->next_hydr = -1;            // Index count start on 0 so set to negative 1

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
