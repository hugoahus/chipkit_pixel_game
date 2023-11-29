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
#define PLAYER_FRAME_OFFSET 2

/* Fire hydrant constants*/
#define FH_WIDTH 5
#define FH_HEIGHT 6

/* Bee constants*/
#define BEE_WIDTH 8
#define BEE_HEIGHT 9
/* Physics constants*/
#define JUMP_FORCE -2 // The initial force of the jump

extern const uint8_t const font[128 * 8];
extern const uint8_t dogPixels[DOG_HEIGHT][DOG_WIDTH];
extern const uint8_t hydrantPixels[FH_HEIGHT][FH_WIDTH];
extern const uint8_t beePixels[BEE_HEIGHT][BEE_WIDTH];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

extern char textbuffer[4][16];

// Define the point structure
typedef struct
{
    int x; // x coordinate
    int y; // y coordinate
} Point;

// typedef struct
// {
//     Point top_left;
//     Point bot_left;
//     Point top_right;
//     Point bot_right;

// } Rectangle;

// Dog/Player character
typedef struct
{
    int vel_y;
    int y;           // Top left in sprite
    int x;           // Top left in sprite
    int is_grounded; // Represents boolean

} Dog;

Dog player;

typedef struct
{
    int vel_x;
    int y;
    int x;
} Hydrant;

typedef struct
{
    int vel_x;
    int vel_y;
    int y;
    int x;
} Bee;

// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

void is_collision();

// Declare display related functions

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_reset();
// void display_string(int line, char *s);
// void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);
void delay(int);

// Alter display functions
void display_change();
void display_clear();
void display_figure();
void display_reset();
void display_string(int line, char *s);
void display_point(Point *p);
void vertical_line(int x, Point *p1, Point *p2);
void display_update();
void menu();
void highscore();

// Game related functions
void spawn_player();
void game_loop();
void select_screen();

int check_switches();
int check_buttons();

// Control related functions
void controls_init();
int getbtns();
int getsw();

#endif