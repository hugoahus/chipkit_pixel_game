## How to Compile and Install on ChipKIT
To be able to compile and run this code on the ChipKIT, you need to install the latest version of the MCB32 toolchain, which is a c-compiler and assembler for the Uno32 boards.

Firstly the correct serial path needs to be located by running one of the following commands
- Linux: This is normally /dev/ttyUSB0
- Windows: In MSYS2, this is normally /dev/ttyS2
- Mac: This is normally /dev/cu.usbserial-* (replace * with something)

After finding the correct path run
- make
- make install TTYDEV=/dev/"your_serial_path"

## Controls
From the menu screen the controls for switching screens are displayed. These are the controls for playing the game:
- BTN 2: Reset game
- BTN 3: Jump

If the player has achieved a new highscore, they will be confronted to enter a name for the highscore list. The name must be 3 characters in length. To select which character to change in the name, the player needs to toggle the corresponding switch first. These are the switch combinations
- SW1: Right-most character
- SW2: Middle character
- SW3: Left-most character

After toggling a switch the button presses to alter the character, move up or down in the ASCII-table, are:
- BTN4: Up
- BTN3: Down
