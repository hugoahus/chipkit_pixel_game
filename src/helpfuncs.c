/*
This file is written 2023 by Erik Smit.
This file contains helper functions used in other functions.
*/

#include <stdint.h> /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

/*
This function converts int to str

Input: an integer number and a pointer to a string.
Output: none, but the string will be the converted int.
*/

void *stdin, *stdout, *stderr; // Declare pointers for library functions

void int_to_str(int num, char *str)
{
    int i = 0;
    int temp = num;
    int length = 0;

    // Count the number of digits in the number
    while (temp != 0)
    {
        temp /= 10;
        length++;
    }

    // Handle the case of zero separately
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Convert the number to a string in reverse order
    for (i = 0; i < length; i++)
    {
        str[length - i - 1] = '0' + num % 10;
        num /= 10;
    }

    // Null-terminate the string
    str[length] = '\0';
}

/*
Function to concatenate two strings

Input: two strings to concatenate and a pointer to the result string.
Output: none, but the result string will contain the concatenated strings.
*/
void concat_strings(const char *str1, const char *str2, char *result)
{
    int i = 0, j = 0;

    // Copy characters from the first string
    while (str1[i] != '\0')
    {
        result[i] = str1[i];
        i++;
    }

    // Append characters from the second string
    while (str2[j] != '\0')
    {
        result[i + j] = str2[j];
        j++;
    }

    // Null-terminate the result string
    result[i + j] = '\0';
}

/*
Switch the names of two highscore name values

Input: two strings (names) to switch and pointers to the result strings.
Output: none, but the result strings will contain the switched names.
*/
void switch_names(const char *name1, const char *name2, char *result1, char *result2)
{
    int i;
    for (i = 0; i < MAX_NAME_LENGTH; i++)
    {
        result1[i] = name2[i];
        result2[i] = name1[i];
    }

    // Null-terminate the result strings
    result1[MAX_NAME_LENGTH] = '\0';
    result2[MAX_NAME_LENGTH] = '\0';
}

/*
Increments the hex value of player name characters

Input: an index indicating which character to increment.
Output: none, but the corresponding character in the player_name array will be incremented or decremented based on button input.
*/
void increment_hex(int index)
{
    // Only allow alphabetical characters
    if (player_name[index] >= 'A' && player_name[index] <= 'Z')
    {
        switch (check_buttons())
        {
        case 4:
            if (player_name[index] < 'Z')
            {
                (player_name[index])++;
                break;
            }

        case 3:
            if (player_name[index] > 'A')
            {
                (player_name[index])--;
                break;
            }
        }
    }
}

// Custom seed initialization function
void custom_seed_init(unsigned int seed)
{
    // Use some hardware-dependent value, such as analogRead() or a timer value
    srand(seed);
}

// Function to generate a random number between min and max (inclusive)
int custom_random(int min, int max)
{
    // Ensure that max is greater than min
    if (max <= min)
    {
        return min;
    }

    // Generate a random number and scale it to the desired range
    return (rand() % (max - min + 1)) + min;
}
