# Dog Game using the built-in display (Chrome Dino Game)

By Erik Smit and Hugo Larsson Wilhelmsson.

## Objective and Requirements

The purpose of this project is to develop a game similar to the Chrome Dino Game that appears when trying to browse Chrome while offline. This game shall be developed on the embedded platform, ChipKIT. In this game, the player will control an object/character and try to maneuver various objects/enemies by jumping. These requirements must be met.

- Standard Chrome Dino game rules are implemented (random object/enemy generation).
- Enemies move in both X and Y directions.
- The player must be able to control the playable character's vertical movement by clicking a button.

### Optional features (if time allows)

- Implement a high score system that tracks the top 3 scores (input of initials).
- Another person chooses the spawn of new enemies by clicking a button.
- Realistic and smooth animations.
- Different speeds/difficulties.
- Accessibility features, such as support for blind mode through audio usage (e.g., screaming “BIRD!” when a bird appears or other sounds).

## Solution

We intend to develop our game on the ChipKIT Uno 32 board together with the basic I/O shield. We will use the display on the Basic I/O shield to display the game and the buttons to jump, pause, and reset the game. The switches will be used to decide where the enemies should spawn (if time allows). We are going to use interrupts triggered by the built-in timer to update the screen and control the speed of the game. The code is written in C.

## Verification

We intend to verify our program by performing various extensive tests. Firstly, we intend to carefully test collisions by studying different scenarios to evaluate the accuracy of the hit-box or collision event. For example, we will verify that collisions are measured and registered in all possible directions. We also intend to test the control functionality by testing different button combinations and see how it affects the game and the game performance. We will also write a brief test specification for the most relevant and important tests.

## How to Compile and Install on ChipKITt
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

