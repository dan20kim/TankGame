#include "main.h"

/* Author: Daniel Kim
 * Professor: Hong
 * Class: ECE-160
 * Project Name: Tank Game Final Project
 * Date: 12/14/18 */


using namespace std;
int main(){
  //Initialize Variables
  int row, col;
  struct winsize w;
  int difficulty;
  int playerCount;
  int win = 0;
  int *winptr = &win;
  char flush;
  char tempName[100] = "Player 1", tempNameTwo[100] = "Player 2";
  char p1 = 'A', p2 = 'B', tempChar;
  string name, nameTwo;
  vector<vector<char>> board;
  srand(time(NULL));
  // Ncurses setup
  initscr();
  raw();
  keypad(stdscr, true);
  ioctl(0, TIOCGWINSZ, &w);
  // Prompt for 1-2 players, name, character, difficuly
  do{
    printw("1 or 2 players?: ");
    playerCount = getch() - '0';
    printw("\n");
  }while(playerCount != 1 && playerCount !=2);
  // ask only if player count is 1
  if (playerCount == 1){
    do{
     printw("Enter a difficulty(0-3, 3 Cooper Union Physics Students, 0 Alan Wolf): ");
     difficulty = getch() - '0';
     printw("\n");
    }while(difficulty < 0 || difficulty > 3);
  }
  printw("Enter a name: ");
  scanw("%s", tempName);
  name = tempName;
  printw("What do you want to be?(A-Z): ");
  tempChar = getch();
  if (tempChar != 10){
    p1 = tempChar;
  }
  // ask only if player count is 2
  if (playerCount == 2){
    printw("\nEnter a name for player 2: ");
    scanw("%s", tempNameTwo);
    nameTwo = tempNameTwo;
    printw("Player two, what do you want to be?(A-Z): ");
    tempChar = getch();
    if (tempChar != 10){
      p2 = tempChar;
    }
  }
  row = w.ws_row-10; // Gets the curreddnt size of the window, 
  col = w.ws_col-10; //so that the game can be sized accordingly
  erase();
  noecho();
  initBoard(row, col, board);
  if (playerCount == 1){
    Tank computer = Tank("Alan Wolf", 3, 5, board[0].size()-21, 'W'); // create computer tank
    Tank player = Tank(name, 3, 5, 20, p1); // create player tank
    initTank(player, board);
    initTank(computer, board);
    drawBoard(board, player, computer);
    while(win != 1){
      win = playerTurn(player, computer, board, 0); // let player make a move
      winCondition(computer, "YOU WIN", winptr, board); // check if player hit the computer
      // breaks if player 1 won
      if (win == 1){
        break;
      }
      erase();
      //re-init the board, so the player and computer are shown, in the case that it is hit by the computer
      reInitBoard(player, computer, row, col, board);
      win = computerTurn(player, computer, board, difficulty); // let computer make a move
      winCondition(player, "YOU LOSE", winptr, board); // check if computer hit player
      //re-init the board, so the player and computer are shown, in the case that it is hit by the computer
      erase();
      reInitBoard(player, computer, row, col, board);
    }
    getchar();
    endwin();
  }
  else if (playerCount ==2){
    Tank player1 = Tank(name, 3, 5, 20, p1);
    Tank player2 = Tank(nameTwo, 3, 5, board[0].size()-21, p2);
    initTank(player1, board);
    initTank(player2, board);
    drawBoard(board, player1, player2);
    while(win != 1){
      win = playerTurn(player1, player2, board, 0);
      winCondition(player2, "Player 1 Wins", winptr, board);
      // breaks if player 2 won
      if (win == 1){
        break;
      }
      erase();
      //re-init the board, so the player and computer are shown, in the case that it is hit by the computer
      reInitBoard(player1, player2, row, col, board);
      win = playerTurn(player2, player1, board, 180);
      winCondition(player1, "Player 2 Wins", winptr, board);
      erase();
      //re-init the board, so the player and computer are shown, in the case that it is hit by the computer
      reInitBoard(player1, player2, row, col, board);
    }
    getchar();
    endwin();
  }
  return 0;
}



