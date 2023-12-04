#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "dog.h"

/* Converts int to str*/
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

/* Function to concatenate two strings*/
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

/* Switch the names of two highscore name values */
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

/* Increments the hex value of player name characters*/
void increment_hex(int index)
{
    // Most right character

    switch (check_buttons())
    {
    case 4:
        (player_name[index])++;
        break;

    case 3:
        (player_name[index])--;
        break;
    }
}
