//#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include <vector>
#include <windows.h>
//#include <math.h>
#include <time.h>
#include "tank.h"
#include "bullet.h"
#include "globals.h"

using namespace std;
void initTank(Tank &computer, vector<vector<char>> &board);
void initBoard(int row, int col, vector<vector<char>> &board);
void drawBoard(vector<vector<char>> &board, Tank &player, Tank &computer);
int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int angleOffset);
int computerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int difficulty);
void moveRight(Tank &tank, vector<vector<char>> &board);
void moveLeft(Tank &tank, vector<vector<char>> &board);
int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &player, Tank &computer);
void winCondition(Tank &tank, string winMessage, int *winptr, vector<vector<char>> &board);
void reInitBoard(Tank &tank1, Tank &tank2, int row, int col, vector<vector<char>> &board);
