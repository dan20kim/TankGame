#include "functions.h"
using namespace std;

// checks if there is a hit, if it is a winning hit
void winCondition(Tank &tank, string winMessage, int *win, vector<vector<char>> &board){
  if (*win == 1){  
    *win = 0;
    if (tank.getHealth() == 1){
      erase();
      mvprintw((board.size()/2)+1, (board[0].size()/2)+1, winMessage.c_str());
      refresh();
      *win = 1;
    }
    tank.decreaseHealth();
  }
}

// adds the character of a tank to its position
void initTank(Tank &tank, vector<vector<char>> &board){
  board[board.size()-1][tank.getPosition()] = tank.getSymbol();
}

// moves a tank right
void moveRight(Tank &tank, vector<vector<char>> &board){
  for (int i = 0; i < tank.getSpeed(); i++){
    if (tank.getPosition()+1 < board[0].size() && board[board.size()-1][tank.getPosition()+1] == ' '){
      tank.moveRight();
      board[board.size()-1][tank.getPosition()-1] = ' ';
      board[board.size()-1][tank.getPosition()] = tank.getSymbol();
    }
  }
}

// moves a tank left
void moveLeft(Tank &tank, vector<vector<char>> &board){
  for (int i = 0; i < tank.getSpeed(); i++){
    if (tank.getPosition()-1 >= 0 && board[board.size()-1][tank.getPosition()-1] == ' '){
      tank.moveLeft();
      board[board.size()-1][tank.getPosition()+1] = ' ';
      board[board.size()-1][tank.getPosition()] = tank.getSymbol();
    }
  }
}

// initializes the board array
void initBoard(int row, int col, vector<vector<char>> &board){
  int i, j;
  board.resize(row);
  for (i = 0; i < row; i++){
    board[i].resize(col);
  }
  for (i = 0; i < row; i++){
    for (j = 0; j < col; j++){
      board[i][j] = ' ';
    }
  }
  for (j = (col/2)-1; j < (col/2)+4; j++){
    for (i = row-1; i > row-4+abs(j-((col/2)+1)); i--){
      board[i][j] = 'X';
    }
  }
}

// draws the board
void drawBoard(vector<vector<char>> &board, Tank &player, Tank &computer){
  int i, j;
  printw("+");
  for (i = 0; i < board[0].size(); i++){
    printw("-");
  }
  printw("+");
  printw("\n");
  for (i = 0; i < board.size(); i++){
    printw("|");
    for (j = 0; j < board[0].size(); j++){
      printw("%c", board[i][j]);
    }
    printw("|\n");
  }
  printw("+");
  for ( i = 0; i < board[0].size(); i++){
    printw("-");
  }
  printw("+\n");
  // prints health
  printw("%s Health: %d\n", player.getName().c_str(), player.getHealth());
  printw("%s Health: %d\n", computer.getName().c_str(), computer.getHealth());
}

// allows the player to make a move
int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int angleOffset){
  char choice;
  double power = 20;
  double angle = 45;
  int win = 0;
  echo();
  raw();
  printw("What would you like to do? (r<right>/l<left>/s<shoot>) **DO NOT PRESS ENTER**: ");
  refresh();
  do {
    choice = getch();
  }while (choice != 'l' && choice != 'r' && choice != 's');
    if (choice == 'l'){
      moveLeft(player, board);
      refresh();
    }
    else if (choice == 'r'){
      moveRight(player, board);
      refresh();   
    }
    else if (choice == 's'){
      printw("\nEnter a power(0-30): ");
      do{
        scanw("%lf", &power);
      } while(power<0 || power > 30);
      printw("Enter an angle(0-90): ");
      do{
        scanw("%lf", &angle);
      } while(angle<0 || angle > 90);
      angle = abs(angleOffset - angle);
      printw("%lf", angle);
      Bullet pShot = Bullet(power, angle, player.getPosition(), board.size()-2);
      win = drawPath(pShot, board, player, computer);
      raw();
    } 
  return win;
}

// allows the computer to make a move
int computerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int difficulty){
  double angle, power;
  int win = 0;
  int choice = rand() % 3; // random choice of right, left, or shoot
  int offset = 0;
  double distance = computer.getPosition() - player.getPosition()-2.5; // -2.5 is a rough approximation because the bullet actually starts above the tank. This means it has to travel "less" of distance to get to the appropriate distance.
  if (choice == 0){
    moveLeft(computer, board);
    printw("\nI moved Left");
    refresh();
    Sleep(1000);
  }
  else if (choice == 1){
    moveRight(computer, board);
    printw("\nI moved Right");
    refresh();
    Sleep(1000);
  }
  else if (choice == 2){
    angle = rand() % 30 + 121; // angle is between 30 and 60
    // if difficulty > 0, create a random offset based on difficulty to simulate a bad player
    if (difficulty > 0){
      offset = rand() % difficulty;
    }
    power = sqrt(20*.0981*distance/-sin(2*PI*angle/180))+offset/2; // Initial Velocity Formula - I need to multiply by 20 because the acceleration is /20 in the update bullet.
    printw("\nI shot with an angle of %lf and a power of %lf", angle, power);
    refresh();
    Sleep(4000); // sleep for 4 seconds so the player can read the message
    Bullet cShot = Bullet(power, angle, computer.getPosition(), board.size()-2); // create a bullet object
    win = drawPath(cShot, board, computer, player);
  }
  return win;
}

// draws and updates the bullet's arc, returns 1 if it hits the tank
int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &shooter, Tank &enemy){
  int win = 0;
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() >= 0 && bullet.getXPosition() < board[0].size()){
    board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = 'O';
    erase();
    drawBoard(board, shooter, enemy);
    refresh();
  }
  Sleep(10); // sleep for 10 milisec between each update so the player can see the arc
  board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = ' '; // make the previous position ' ', so that a trail of 'O's are not left behind
  // check if the bullet hit the enemy, if it did, return 1
  if ((int)bullet.getXPosition() == enemy.getPosition() && (int)bullet.getYPosition() == board.size()-1){    
    printw("%s got hit", enemy.getName().c_str());
    refresh();
    Sleep(1000); // sleep for 1 sec so the player can read the message
    return 1;
  }
  bullet.updateBullet();
  // check if the bullet hit a wall, if it did, return 0
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() > 0 && bullet.getXPosition() < board[0].size() && board[bullet.getYPosition()][bullet.getXPosition()] == 'X'){
    return 0;
  }
  // update the bullet again
  if ((int)bullet.getYPosition() >= 0 && (int)bullet.getYPosition() < board.size() && (int)bullet.getXPosition() >= 0 && (int)bullet.getXPosition() < board[0].size()){
    win = drawPath(bullet, board, shooter, enemy);
  }
  return win;
}

// redraws the board
void reInitBoard(Tank &tank1, Tank &tank2, int row, int col, vector<vector<char>> &board){
  initBoard(row, col, board);
  initTank(tank1, board);
  initTank(tank2, board);
  drawBoard(board, tank1, tank2);
}
