#include <iostream>
#include <string>
#include <curses.h>
int main(){
  int id;
  char deptname[25]; 
  mvprintw(5,0,"Enter your i.d. followed by the department name:\n");
  refresh();
  scanw("%d %s", &id, deptname);
  mvprintw(7,0,"i.d.: %d, Name: %s\n", id, deptname);
  refresh();
  return 0;
}
