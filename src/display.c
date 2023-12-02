/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "dog.h" //Project header file

/* (TAKEN FROM LAB)*/

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/*If any point in the array is set to one the pixel att the same position be lit*/
uint8_t display[32][128];  // Human readable pixel position and activation, [y][x]
uint8_t oled_display[512]; // Computer readable pixel position and activation

/*(TAKEN FROM LAB) Quick sleep timer*/
void quicksleep(int cyc)
{
    int i;
    for (i = cyc; i > 0; i--)
        ;
}

/*(TAKEN FROM LAB) Send data to the OLED display using the SPI protocol*/
uint8_t spi_send_recv(uint8_t data)
{ // LAB
    while (!(SPI2STAT & 0x08))
        ;
    SPI2BUF = data;
    while (!(SPI2STAT & 1))
        ;
    return SPI2BUF;
}

/*(TAKEN FROM LAB) Initialize OLED display*/
void display_init(void)
{
    // Given sequence for initialising display
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    quicksleep(10);
    DISPLAY_ACTIVATE_VDD;
    quicksleep(1000000);

    spi_send_recv(0xAE);
    DISPLAY_ACTIVATE_RESET;
    quicksleep(10);
    DISPLAY_DO_NOT_RESET;
    quicksleep(10);

    spi_send_recv(0x8D);
    spi_send_recv(0x14);

    spi_send_recv(0xD9);
    spi_send_recv(0xF1);

    DISPLAY_ACTIVATE_VBAT;
    quicksleep(10000000);

    spi_send_recv(0xA1);
    spi_send_recv(0xC8);

    spi_send_recv(0xDA);
    spi_send_recv(0x20);

    spi_send_recv(0xAF);

    display_reset();
}

/* Displays a sprite/figure with given height width and 2d-pixel array*/
void display_figure(int x, int y, int height, int width, const uint8_t pixels[height][width])
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (pixels[i][j])
            {
                // Test for collision
                if (display[i + y][j + x] == 1 && (i + y) < GROUND_LEVEL)
                {
                    display_reset();
                    is_collision();
                }

                display[i + y][j + x] = 1;
            }
        }
    }
}

/*(TAKEN FROM LAB) This will print any image on the display with the help of an array containing the map of the active and inactive pixels*/
void display_image(int x, const uint8_t *data)
{ // LAB
    int i, j;

    for (i = 0; i < 4; i++)
    {
        DISPLAY_CHANGE_TO_COMMAND_MODE;

        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));

        DISPLAY_CHANGE_TO_DATA_MODE;

        for (j = 0; j < 128; j++)
            spi_send_recv(data[i * 128 + j]);
    }
}
/* This function translates the human readable pixel locations to a 512-byte buffer*/
void display_translate()
{
    int page, row, column;
    uint8_t powerOfTwo = 1;
    uint8_t oledNumber = 0;

    for (page = 0; page < 4; page++)
    {
        for (column = 0; column < 128; column++)
        {
            powerOfTwo = 1;
            oledNumber = 0;

            for (row = 0; row < 8; row++)
            {
                if (display[8 * page + row][column])
                {
                    oledNumber |= powerOfTwo;
                }
                powerOfTwo <<= 1;
            }
            oled_display[column + page * 128] = oledNumber;
        }
    }
}

/* Function clears the textbuffer*/
void clear_text_buffer()
{
    int line, i;
    for (line = 0; line < 4; line++)
    {
        for (i = 0; i < 16; i++)
        {
            textbuffer[line][i] = ' ';
        }
    }
}

/*(TAKEN FROM LAB) Display text*/
void display_string(int line, char *s)
{
    int i;
    if (line < 0 || line >= 4)
        return;
    if (!s)
        return;
    for (i = 0; i < 16; i++)
        if (*s)
        {
            textbuffer[line][i] = *s;
            s++;
        }
        else
            textbuffer[line][i] = ' ';
}

/*(TAKEN FROM LAB) Display text*/
void display_update(void)
{
    int i, j, k;
    int c;
    for (i = 0; i < 4; i++)
    {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(0x0);
        spi_send_recv(0x10);

        DISPLAY_CHANGE_TO_DATA_MODE;

        for (j = 0; j < 16; j++)
        {
            c = textbuffer[i][j];
            if (c & 0x80)
                continue;

            for (k = 0; k < 8; k++)
                spi_send_recv(font[c * 8 + k]);
        }
    }
}
/* Function resets all pixels on the array*/
void display_reset()
{
    // Clear the display
    display_clear();
    // Update the display with cleared pixels
    display_image(0, oled_display);
}

/*This function sets all the values in the display array and oled display array into 0s*/
void display_clear()
{
    int row, column, i;

    for (row = 0; row < 32; row++)
    {
        for (column = 0; column < 128; column++)
        {
            display[row][column] = 0;
        }
    }

    for (i = 0; i < 512; i++)
    {
        oled_display[i] = 0;
    }
}

/*This function calls all the necessary functions for the game to start*/
void display_change()
{
    display_translate();
    display_image(0, oled_display);
}

// Highscore screen
void highscore()
{
    display_string(1, "Highscore");
    display_string(2, "");
    display_string(3, "");

    display_update();
}

// Pause screen
void pause()
{
    display_string(1, "Game is paused");
    display_string(2, "");
    display_string(3, "");

    display_update();
}

/*  Menu screen (static display)*/
void menu()
{
    display_string(1, "MENU");
    display_string(2, "BTN4 - Game");
    display_string(3, "SW2 - Highscore");

    display_update();
}

/* Screen that is displayed before the game starts*/
void choose_diff()
{
    display_string(0, "Choose Map");
    display_string(1, "BTN2 - Easy");
    display_string(2, "BTN3 - Medium");
    display_string(3, "BTN4 - Hard");

    display_update();
}