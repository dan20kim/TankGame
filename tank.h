#ifndef tankincluded // include only if not included before
#define tankincluded

#include <string>
#include "globals.h"

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

#endif
