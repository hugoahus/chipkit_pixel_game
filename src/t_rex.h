/* THIS IS THE HEADER FILE FOR THE PROJECT*/

// Declare display related functions

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);

extern const uint8_t const font[128 * 8];
extern char textbuffer[4][16];

// Own
uint8_t display[32][128];  // Human readable pixel position and activation
uint8_t oled_display[512]; // Computer readable pixel position and activation

void display_start();
void display_clear();
