#include <iostream>
#include <ncurses.h>
#include <string>
#include <curses.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <vector>
#include <windows.h>
#include <math.h>

#define PI 3.14159265359

using namespace std;
class Tank{
private:
  int health;
  int speed;
  int position;
  char symbol;
public:
  Tank();
  Tank(int initHealth, int initSpeed, int initPosition, char initSymbol);
  ~Tank();
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
  health = 3;
  speed = 1;
  position = 0;
  symbol = 'P';
}

Tank::Tank(int initHealth, int initSpeed, int initPosition, char initSymbol){
  health = initHealth;
  speed = initSpeed;
  position = initPosition;
  symbol = initSymbol;
}

Tank::~Tank(){
  cout << "dead" << endl;
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
int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board);
void moveRight(Tank &tank, vector<vector<char>> &board);
void moveLeft(Tank &tank, vector<vector<char>> &board);
int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &player, Tank &computer);

int main(){
  int row, col;
  struct winsize w;
  int win = 0;
  initscr();
  //raw();
  noecho();
  keypad(stdscr, true);
  ioctl(0, TIOCGWINSZ, &w);
  row = w.ws_row-10;
  col = w.ws_col-10;
  //printw("row:%d col:%d\n", w.ws_row, w.ws_col);
  Tank player = Tank(3, 3, 0, 'P');
  vector<vector<char>> board;
  initBoard(row, col, board);
  Tank computer = Tank(3,1,board[0].size()-10, 'C');
  initTank(player, board);
  initTank(computer, board);
  drawBoard(board, player, computer);
  while(win != 1){
    clear();
    drawBoard(board, player, computer); 
    win = playerTurn(player, computer, board);
    initTank(player, board);
    initTank(computer, board);
    refresh();
  }
  getchar();
  endwin();
  //cout << y << x << endl;
  return 0;
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
    if (tank.getPosition()-1 >= 0 && board[board.size()-1][tank.getPosition()-1] ==' '){
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
  printw("Your Health: %d\n", player.getHealth());
  printw("Computer Health: %d\n", computer.getHealth());
}

int playerTurn(Tank &player, Tank &computer, vector<vector<char>> &board){
  char choice = 'l';
  double power;
  double angle;
  int win;
  echo();
  printw("\nWhat would you like to do? ");
  do {
    choice = getch();
  } while (choice != 'l' && choice != 'r' && choice != 's');
    if (choice == 'l'){
      moveLeft(player, board);
    }
    else if (choice == 'r'){
      moveRight(player, board);   
    }
    else if (choice == 's'){
      noraw();
      printw("\nEnter a power ");
      do{
        scanw("%lf", &power);
      } while(power<0 || power > 30);
      printw("\n%lf", power);
      printw("\nEnter an angle ");
      do{
        scanw("%lf", &angle);
      } while(angle<0 || angle > 90);
      printw("%lf", angle);
      Bullet pShot = Bullet(power, angle, player.getPosition(), board.size()-2);
      win = drawPath(pShot, board, player, computer);
      //pShot.~Bullet();
      raw();
    } 
  return win;
}

int drawPath(Bullet &bullet, vector<vector<char>> &board, Tank &player, Tank &computer){
  int win = 0;
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() >= 0 && bullet.getXPosition() < board[0].size()){
    board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = 'O';
    clear();
    drawBoard(board, player, computer);
    refresh();
  }
  Sleep(10);
  board[(int)bullet.getYPosition()][(int)bullet.getXPosition()] = ' ';
  if ((int)bullet.getXPosition() == computer.getPosition() && (int)bullet.getYPosition() == board.size()-1){    
    printw("YOU HIT HIM");
    refresh();
    Sleep(1000);
    if (computer.getHealth() == 1){
      clear();
      //computer.~Tank();
      mvprintw((board.size()/2)+1, (board[0].size()/2)+1,"YOU WIN");
      refresh();
      return 1;
    }
    computer.decreaseHealth();
  }
  bullet.updateBullet();
  if (bullet.getYPosition() >= 0 && bullet.getYPosition() < board.size() && bullet.getXPosition() >= 0 && bullet.getXPosition() < board[0].size()){
    win = drawPath(bullet, board, player, computer);
  }
  return win;
}

