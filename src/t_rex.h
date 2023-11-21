/* THIS IS THE HEADER FILE FOR THE PROJECT*/
#ifndef TREX_H
#define TREX_H

/* Display constants */
#define GROUND_LEVEL 29 // Which row that is ground level
#define COLUMNS 128     // Nr of columns
#define ROWS 32         // Nr of rows
#define BOX_SIZE 4      // Size of box, meaning 4X4
#define FRAME_RATE 10

/* Trex constants*/
#define T_REX_WIDTH 9
#define T_REX_HEIGHT 6

// Declare display related functions

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);
void delay(int);

extern const uint8_t const font[128 * 8];
extern const uint8_t trexPixels[T_REX_HEIGHT][T_REX_WIDTH];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
extern char textbuffer[4][16];

// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

void display_change();
void display_clear();

void setup_spawn();
void create_trex();

void game();

// Define a structure with two int arrays
struct Box
{
    int start_x;
    int start_y;
    int box_x[BOX_SIZE];
    int box_y[BOX_SIZE];
};

// Trex character
struct Dog
{
    int vel;
    int x;
    int y;
    char dir;  // direction of the Trex
    int state; // the state of the Trex
};

#endif // STRUCTURES_H