# Dog Game using the built-in display (Chrome Dino Game)

By Erik Smit and Hugo Larsson Wilhelmsson.

## Objective and Requirements

The purpose of this project was to develop the T-Rex game that appears when trying to browse chrome while offline, on the embedded platform. In this game the player controls an object/character and tries to maneuver various objects/enemies by jumping. The main requirements before the project were:
- Standard T-Rex game rules should be implemented (random enemy generation/progressively increasing game speed).
- Enemies should move in both X and Y direction.
- The player must be able to control the playable characters vertical movement by clicking a button.
- Different difficulties (easy, medium, hard) with different speeds and number of enemies.


### Optional features (if time allows)
- We implement a high score system that tracks the top 3 scores with the players initials (up to 3 letters).
- The current score is shown during the gameplay.
- A life system, where the player can die 3 times before game over.
- A pause screen that shows the unique seed of the current map.


## Solution

We developed our game on the ChipKIT Uno 32 board together with the basic I/O shield. We used the display on the Basic I/O shield to display the game, and the buttons to start the game (by selecting a difficulty), jump and write the initials in the high score system. The switches are used to pause the game and show high scores. We used the timer to generate the seed for the map with the random map elements.

We created the random spawn of enemies by using a spawn timer. The spawn timer is a function that randomly picks a number, which is the number of times the game loop will run before a new enemy will be spawned. When a new enemy will spawn, we also randomly choose which enemy type that will spawn. We do this by using our own random generator which will choose the number 0 or 1, where 0 will spawn a hydrant, and 1 will spawn a bee.

## Verification

We verified the program by first creating the dog and then trying to show it on the display. When we understood how we could implement figures, we created the jump function which we tested by creating different jump patterns and showing them on the screen. When we were satisfied with the jump pattern we added the hydrant enemy that would be possible to jump over. When we had a basic game, with the dog and one enemy, we added the collision feature which we verified by trying to approach the enemy in different ways. When the collision worked correctly, we added the second enemy, a “flying” enemy, which was a bee. We verified the correct behavior of the bee by checking it in the same way as we checked the hydrant.

We verified the control system by changing the inputs between different buttons and switches. For example we made the dog jump by both pressing a button but also using the switches. In the end we thought that the jump functions worked best by pressing a button. We did the same tests with the other inputs features to get the best gameplay according to us.

## Contributions

We split the work into two different parts in the beginning of the project. One of the parts was the graphical area, which Erik developed. This part contained how we could display and animate different objects  on the screen, mainly by  turning pixels on and off. This part also included creating the different figures on the display and controlling how they move. The second part was to implement the input of the buttons and the switches, which Hugo coded. This included to understand how we can use them but also to decide which inputs should be used for what. In this part, different game states representing the states we would use in the game (for example game screen, pause screen, menu, high scores), were also created. 

When these two parts were done we coded the different game functions, such as how the score is being counted and how the collision is implemented together. This is more precisely shown in the code.


## Reflections 

We think this was a fun project that we’ve learned a lot from. The most fun part was when we had implemented both the graphical part and the different inputs, so we could focus on creating a fun game. 

The hardest part of the code was trying to implement random spawn of enemies, both by randomly choosing which enemy should spawn, but also exactly when they would spawn. This was the last implemented feature in the game, which we, if we had more time, would work more so for example enemies don't spawn in ways where it is impossible for the user to get past. This is rare but may occur.


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

