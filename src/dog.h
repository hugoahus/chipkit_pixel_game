/* THIS IS THE HEADER FILE FOR THE PROJECT*/
#ifndef TREX_H
#define TREX_H

/* Display constants */
#define GROUND_LEVEL 29 // Which row that is ground level
#define COLUMNS 128     // Nr of columns
#define ROWS 32         // Nr of rows
#define BOX_SIZE 4      // Size of box, meaning 4X4
#define FRAME_SPEED 100 // Frame rate in Milliseconds

// Object constants

/* Dog constants*/
#define DOG_WIDTH 9
#define DOG_HEIGHT 6

/* Fire hydrant constants*/
#define FH_WIDTH 5
#define FH_HEIGHT 6

/* Physics constants*/
#define GRAVITY 9.8f  // Acceleration due to gravity (m/s^2)
#define JUMP_FORCE -2 // The initial force of the jump

extern const uint8_t const font[128 * 8];
extern const uint8_t dogPixels[DOG_HEIGHT][DOG_WIDTH];
extern const uint8_t hydrantPixels[FH_HEIGHT][FH_WIDTH];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

extern char textbuffer[4][16];

// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

// Declare display related functions

void display_image(int x, const uint8_t *data);
void display_init(void);
// void display_string(int line, char *s);
// void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);
void delay(int);

void display_change();
void display_clear();
void display_figure();
void display_string(int line, char *s);
void display_update();

// Game related functions
void spawn_player();
void game_loop();
int check_switches();

// Control related functions
void controls_init();
int getbtns();
int getsw();
// Define a structure with two int arrays
struct Box
{
    int start_x;
    int start_y;
    int box_x[BOX_SIZE];
    int box_y[BOX_SIZE];
};

// Dog/Player character
typedef struct
{
    int vel_y;
    int y;
    int x;
    int is_grounded; // Represents boolean

} Dog;

Dog player;

typedef struct
{
    int vel_x;
    int y;
    int x;
} Hydrant;
#endif