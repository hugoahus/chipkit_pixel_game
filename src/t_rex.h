/* THIS IS THE HEADER FILE FOR THE PROJECT*/

// Declare display related functions

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);

extern const uint8_t const font[128 * 8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
extern char textbuffer[4][16];

extern COLUMNS;
// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

void display_change();
void display_clear();

void setup_spawn();

// Trex character
typedef struct Trex
{
    uint8_t *x; // pointer to the x position of trex top left corner
    uint8_t *y; // pointer to the y position of trex top left corner

    // 2x2 box
    int x_positions[2];
    int y_positions[2];

    char dir;  // direction of the Trex
    int state; // the state of the Trex
} Trex;

Trex trex;
