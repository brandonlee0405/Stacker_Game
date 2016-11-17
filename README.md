# Stacker_Game
The following project was programmed in C with the Atmel Studio 6.2 IDE.

###Components Used

- 16x2 LCD Display
- 8x8 RGB LED
- Joystick
- 74HC595 Shift Registers
- ATmega1284 Micro Controller

###Project Description

This project is an upgraded version of the standard arcade game, Stacker. Through the use of a single ATmega1284 and the use of 
shift registers, this project was able to duplicate the arcade game as well as having some minor upgrades, including a two-player option.
The objective of this game is to successfully stack blocks to the top that are moving horizontally in different speeds. If the player
unsuccessfully lands the correct stack, the game ends. There are two game modes within this project.

Game mode 1 (Single Player): This mode comes with three levels of difficulty: easy, medium, and hard. The easy difficulty is provided with
a two-layer block rather than your average one layer. The block moves from left to right at constant speed throughout each successful
stack. The medium difficulty is your average Stacker game. With one layer of of blocks, the size of the block decreases as you successfully
land a stack. The hard difficulty is your average Stacker game but with higher speeds.

Game mode 2 (Multi Player): This mode gives you the option to play with another player. This game mode is played with the original Stacker
game, however there is power-ups provided in this mode. If a player successfully lands the first 4 layer of the blocks, the oppenent's blocks
temporarily freezes. If the player messes up the stack, it just resets the stack. The first one to reach to the top is the winner.

###Youtube Video

[Stacker Video](https://www.youtube.com/watch?v=v2tnpOUjNDc)

###Original Work Statement

I acknowlegde all content contained herin, excluding template or example code, is my own original work.
