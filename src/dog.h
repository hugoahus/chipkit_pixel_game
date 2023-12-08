/* THIS IS THE HEADER FILE FOR THE ENTIRE PROJECT*/

#ifndef DOG_H
#define DOG_H
/* Highscore stuff */

#define NR_OF_HIGHSCORES 3
#define MAX_NAME_LENGTH 3

/* Map specific constants */

#define DOG_SPAWN_Y (GROUND_LEVEL - DOG_HEIGHT)
#define DOG_SPAWN_X 20
#define HYDRANT_SPAWN_Y (GROUND_LEVEL - FH_HEIGHT)
#define JUMP_HEIGHT 6

/* Display constants */
#define GROUND_LEVEL 30 // Which row that is ground level
#define COLUMNS 128     // Nr of columns
#define ROWS 32         // Nr of rows
#define BOX_SIZE 4      // Size of box, meaning 4X4
#define FRAME_SPEED 100 // Frame rate in Milliseconds
#define FONT_WIDTH 5
#define FONT_HEIGHT 7

// Object constants
#define HITBOX_OFFSET 2
#define NR_OF_OBJ 5

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

/* Other Constants */
#define SCORE_TIMER 25

extern const uint8_t const font[128 * 8];
extern const uint8_t dogPixels[DOG_HEIGHT][DOG_WIDTH];
extern const uint8_t hydrantPixels[FH_HEIGHT][FH_WIDTH];
extern const uint8_t beePixels[BEE_HEIGHT][BEE_WIDTH];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

extern char textbuffer[4][16];

// Dog/Player character
typedef struct
{
    int vel_y;
    int y;               // Top left in sprite
    int x;               // Top left in sprite
    uint8_t is_grounded; // Represents boolean

} Dog;

Dog player;

typedef struct
{
    int x;
    int y;
    int vel_x;
    uint8_t is_active;

} Hydrant;

typedef struct
{
    int x;
    int y;
    int vel_x;
    int vel_y;
    int y_mov; // Restricts y-movement

    uint8_t is_active;
} Bee;

typedef struct
{
    int next_hydr;  // Index of next hydrant
    int next_bee;   // Index of next bee
    int hydr_timer; // Timer that decides when hydr spawn
    int bee_timer;  // Timer for bee spawn
    int real_size;  // How many objects there are actually in the array (rest are null, max 4 obj)
    Hydrant hydrants[4];
    Bee bees[4];

} Map;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int score;
} Highscore;

/* Map related stuff */
extern Map maps[3];
extern Highscore highscores[NR_OF_HIGHSCORES];
extern char player_name[3];
extern int player_lives;
extern int lights;
// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

void game_over();
void reset_map();
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
void display_update();
void display_score(int score);
void display_figure(int x, int y, int height, int width, const uint8_t pixels[height][width]);
void clear_figure(int x, int y, int height, int width);
inline void clear_enemies(const Map *map);
void menu();
void highscore();
void pause();
void choose_diff();
void enter_name();

// Game related functions
void spawn_player();
void game_loop();
void select_screen();
void start_game();
void game_over();

int check_switches();
int check_buttons();

// Control related functions
void controls_init();
int getbtns();
int getsw();
void show_lives(int lives);
void is_collision();

void clear_text_buffer();

// Helper functions
void int_to_str(int num, char *str);
void concat_strings(const char *str1, const char *str2, char *result);
void switch_names(const char *name1, const char *name2, char *result1, char *result2);

#endif