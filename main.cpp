#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <curses.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <vector>
#include <windows.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265359

using namespace std;
class Tank{
private:
  string name;
  int health;
  int speed;
  int position;
  char symbol;
public:
  Tank();
  Tank(string initName, int initHealth, int initSpeed, int initPosition, char initSymbol);
  ~Tank();
  string getName();
  int getHealth();
  int getSpeed();
  int getPosition();
  void decreaseHealth();
  void increaseHealth();
  void increaseSpeed();
  void moveRight();
  void moveLeft();
  char getSymbol();
};

Tank::Tank(){
  name = "Tank";
  health = 3;
  speed = 1;
  position = 0;
  symbol = 'P';
}

Tank::Tank(string initName, int initHealth, int initSpeed, int initPosition, char initSymbol){
  name = initName;
  health = initHealth;
  speed = initSpeed;
  position = initPosition;
  symbol = initSymbol;
}

Tank::~Tank(){
  cout << "dead" << endl;
}

string Tank::getName(){
  return this->name;
}

int Tank::getHealth(){
  return this->health;
}

int Tank::getSpeed(){
  return this->speed;
}

int Tank::getPosition(){
  return this->position;
}

void Tank::decreaseHealth(){
  this->health--;
}

void Tank::increaseHealth(){
  this->health++;
}

void Tank::increaseSpeed(){
  this->speed++;
}

void Tank::moveRight(){
  this->position++;
}

void Tank::moveLeft(){
  this->position--;
}

char Tank::getSymbol(){
  return this->symbol;
}

class Bullet{
private:
  double power;
  double angle;
  double xPosition;
  double yPosition;
  double xPower;
  double yPower;
public:
  Bullet();
  Bullet(double initPower, double initAngle, double initXPosition, double initYPosition);
  ~Bullet();
  void updateBullet();
  double getPower();
  double getAngle();
  double getXPosition();
  double getYPosition();
};

Bullet::Bullet(){
  power = 0;
  angle = 0;
  xPosition = 0;
  yPosition = 0;
  xPower = power*cos((angle*2*PI)/360.0);
  yPower = power*sin((angle*2*PI)/360.0);
}

Bullet::Bullet(double initPower, double initAngle, double initXPosition, double initYPosition){
  power = initPower;
  angle = initAngle;
  xPosition = initXPosition;
  yPosition = initYPosition;
  xPower = power*cos((angle*2*PI)/360.0);
  yPower = power*sin((angle*2*PI)/360.0);
}

Bullet::~Bullet(){
  //cout << "Bullet dead" << endl;
}

void Bullet::updateBullet(){
  xPosition += .05*xPower;
  yPosition -= .05*yPower;
  yPower -= .0981;
}

double Bullet::getPower(){
  return this->power;
}

double Bullet::getAngle(){
  return this->angle;
}

double Bullet::getXPosition(){
  return this->xPosition;
}

double Bullet::getYPosition(){
  return this->yPosition;
}


void initTank(Tank &computer, vector<vector<char>> &board);
void initBoard(int row, int col, vector<vector<char>> &board);
void drawBoard(vector<vector<char>> &board, Tank &player, Tank &computer);
int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int angleOffset);
int computerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int difficulty);
void moveRight(Tank &tank, vector<vector<char>> &board);
void moveLeft(Tank &tank, vector<vector<char>> &board);
int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &player, Tank &computer);
void winCondition(Tank &tank, string winMessage, int *winptr, vector<vector<char>> &board);


int main(){
  int row, col;
  struct winsize w;
  int difficulty;
  int playerCount;
  int win = 0;
  int *winptr = &win;
  char flush;
  char tempName[100], tempNameTwo[100];
  char p1, p2;
  string name, nameTwo;
  srand(time(NULL));
  initscr();
  raw();
  keypad(stdscr, true);
  ioctl(0, TIOCGWINSZ, &w);
  do{
    printw("1 or 2 players?: ");
    playerCount = getch() - '0';
  }while(playerCount != 1 && playerCount !=2);
  if (playerCount == 1){
    do{
     printw("\nEnter a difficulty(0-3, 3 Cooper Union Physics Students, 0 Alan Wolf): ");
      difficulty = getch() - '0';
    }while(difficulty < 0 || difficulty > 3);
  }
  printw("\nEnter a name: ");
  scanw("%s", tempName);
  name = tempName;
  printw("What do you want to be?: ");
  p1 = getch();
  if (playerCount == 2){
    printw("\nEnter a name for player 2: ");
    scanw("%s", tempNameTwo);
    nameTwo = tempNameTwo;
    printw("Player two, what do you want to be?: ");
    p2 = getch();
  }
  row = w.ws_row-10;
  col = w.ws_col-10;
  noecho();
  //printw("row:%d col:%d\n", w.ws_row, w.ws_col);
  vector<vector<char>> board;
  initBoard(row, col, board);
  if (playerCount == 1){
    Tank computer = Tank("Alan Wolf", 3, 5, board[0].size()-21, 'W');
    Tank player = Tank(name, 3, 5, 20, p1);
    initTank(player, board);
    initTank(computer, board);
    while(win != 1){
      erase();
      drawBoard(board, player, computer);
      refresh();
      win = playerTurn(player, computer, board, 0);
      winCondition(computer, "YOU WIN", winptr, board);
       //while ((flush = getchar()) != '\n' && flush != EOF);
      initBoard(row, col, board);
      initTank(player, board);
      initTank(computer, board);
      win = computerTurn(player, computer, board, difficulty);
      winCondition(player, "YOU LOSE", winptr, board);
      initBoard(row, col, board);
      initTank(player, board);
      initTank(computer, board);
    }
    getchar();
    endwin();
  }
  else if (playerCount ==2){
    Tank player1 = Tank(name, 3, 5, 20, p1);
    Tank player2 = Tank(nameTwo, 3, 5, board[0].size()-21, p2);
    initTank(player1, board);
    initTank(player2, board);
    while(win != 1){
      erase();
      drawBoard(board, player1, player2);
      win = playerTurn(player1, player2, board, 0);
      winCondition(player2, "Player 1 Wins", winptr, board);
      erase();
      drawBoard(board, player1, player2);
      //erase();
       //while ((flush = getchar()) != '\n' && flush != EOF);
      initBoard(row, col, board);
      initTank(player1, board);
      initTank(player2, board);
      win = playerTurn(player2, player1, board, 180);
      winCondition(player1, "Player 2 Wins", winptr, board);
      initBoard(row, col, board);
      initTank(player1, board);
      initTank(player2, board);
    }
    getchar();
    endwin();
  }
  //cout << y << x << endl;
  return 0;
}

void winCondition(Tank &tank, string winMessage, int *win, vector<vector<char>> &board){
  if (*win == 1){  
    *win = 0;
    if (tank.getHealth() == 1){
      erase();
      //computer.~Tank();
      mvprintw((board.size()/2)+1, (board[0].size()/2)+1, winMessage.c_str());
      refresh();
      *win = 1;
    }
    tank.decreaseHealth();
  }
}

void initTank(Tank &tank, vector<vector<char>> &board){
  board[board.size()-1][tank.getPosition()] = tank.getSymbol();
}


void moveRight(Tank &tank, vector<vector<char>> &board){
  for (int i = 0; i < tank.getSpeed(); i++){
    if (tank.getPosition()+1 < board[0].size() && board[board.size()-1][tank.getPosition()+1] == ' '){
      tank.moveRight();
      board[board.size()-1][tank.getPosition()-1] = ' ';
      board[board.size()-1][tank.getPosition()] = tank.getSymbol();
    }
  }
}

void moveLeft(Tank &tank, vector<vector<char>> &board){
  for (int i = 0; i < tank.getSpeed(); i++){
    if (tank.getPosition()-1 >= 0 && board[board.size()-1][tank.getPosition()-1] == ' '){
      tank.moveLeft();
      board[board.size()-1][tank.getPosition()+1] = ' ';
      board[board.size()-1][tank.getPosition()] = tank.getSymbol();
    }
  }
}

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
  printw("%s Health: %d\n", player.getName().c_str(), player.getHealth());
  printw("%s Health: %d\n", computer.getName().c_str(), computer.getHealth());
}

int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int angleOffset){
  char choice;
  double power;
  double angle;
  int win;
  echo();
  raw();
  printw("What would you like to do? (r<right>/l<left>/s<shoot>) **DO NOT PRESS ENTER**: ");
  refresh();
  do {
    choice = getch();
  }while ((choice != 'l' && player.getPosition() > 0) && (choice != 'r' && (player.getPosition() < (board[0].size()/2)-2)) && choice != 's');
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
      //printw("\n%lf", power);
      printw("Enter an angle(0-90): ");
      do{
        scanw("%lf", &angle);
      } while(angle<0 || angle > 90);
      angle = abs(angleOffset - angle);
      printw("%lf", angle);
      Bullet pShot = Bullet(power, angle, player.getPosition(), board.size()-2);
      win = drawPath(pShot, board, player, computer);
      //pShot.~Bullet();
      raw();
    } 
  return win;
}

int computerTurn(Tank &player, Tank &computer, vector<vector<char>> &board, int difficulty){
  double angle, power;
  int win = 0;
  int choice = rand() % 3;
  int offset = 0;
  double distance = computer.getPosition() - player.getPosition()-2.5; // -3 because the bullet actually starts above the tank. This means it has to travel "less" of distance to get to the appropriate distance.
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
    angle = rand() % 30 + 120;
    if (difficulty > 0){
      offset = rand() % difficulty;
    }
    power = sqrt(20*.0981*distance/-sin(2*PI*angle/180))+offset/2; // Initial Velocity Formula - I need to multiply by 20 because the acceleration is /20 in the update bullet.
    printw("\nI shot with an angle of %lf and a power of %lf", angle, power);
    refresh();
    Sleep(4000);
    Bullet cShot = Bullet(power, angle, computer.getPosition(), board.size()-2);
    win = drawPath(cShot, board, computer, player);
  }
  return win;
  
}

int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &shooter, Tank &enemy){
  int win = 0;
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() >= 0 && bullet.getXPosition() < board[0].size()){
    board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = 'O';
    erase();
    drawBoard(board, shooter, enemy);
    refresh();
  }
  Sleep(10);
  board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = ' ';
  if ((int)bullet.getXPosition() == enemy.getPosition() && (int)bullet.getYPosition() == board.size()-1){    
    printw("%s got hit", enemy.getName().c_str());
    refresh();
    Sleep(1000);
    bullet.~Bullet();
    return 1;
  }
  bullet.updateBullet();
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() > 0 && bullet.getXPosition() < board[0].size() && board[bullet.getYPosition()][bullet.getXPosition()] == 'X'){
    return 0;
  }
  if ((int)bullet.getYPosition() >= 0 && (int)bullet.getYPosition() < board.size() && (int)bullet.getXPosition() >= 0 && (int)bullet.getXPosition() < board[0].size()){
    win = drawPath(bullet, board, shooter, enemy);
  }
  return win;
}

