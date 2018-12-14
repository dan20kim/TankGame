# TankGame
Tank game with physics simulations

Author: Daniel Kim
Professor: Hong
Class: ECE-160
Project Name: Tank Game Final Project
Date: 12/14/18

Compilation steps:
make

To start clean:
make clean

To run program:
./game.exe

Dependencies:
You will need to have the NCurses library as well as the Windows.h library installed in order to be able to run this program

Gameplay:
The game will prompt whether you want to play against the computer (1 player) or against someone else (2 player)
If you choose 1 player, you will input a name, a character, and a difficulty (0 hardest, 3 easiest)
If you choose 2 player, you will input a name and character for both players
Once you do that, it will ask whether you want to move left, right, or shoot.
Press r to move right, l to move left, and s to shoot.
Moving right and left will be done automatically.
If shooting, you will be prompted to input a power, and an angle.
Choose your angle and power wisely, so that you can hit the opponenet.
If your shot hits the border or the rock in the middle of the board, it will destroy the bullet and start the other player's turn.
If you hit the opponent, it will tell you who got hit, and will decrease the opponents health by 1.
First player to hit the other player 3 times wins!

Notes:
There is casting of the x and y position of bullets when I want to fit them onto the board.
The board is a 2D vector, so I need integer values. The x and y positions of bullets are 
floating point values to make the arc look better.

There is a compilation warning:
char*’ [-Wwrite-strings]
         scanw("%lf", &power);
                            ^
functions.cpp:119:28: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
         scanw("%lf", &angle)

This is an error within the scanw function.
