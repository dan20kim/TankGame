#include "tank.h"
using namespace std;
/* Tanks are created whenever
 * a player or a computer is made.
 * This would be done at the start of
 * each game. Tanks have a name, as well
 * as health, speed, position, and symbol
 * attributes */

// Default Tank Constructor
Tank::Tank(){
  name = "Tank";
  health = 3;
  speed = 1;
  position = 0;
  symbol = 'P';
}

// Overloaded Tank Constructor
Tank::Tank(string initName, int initHealth, int initSpeed, int initPosition, char initSymbol){
  name = initName;
  health = initHealth;
  speed = initSpeed;
  position = initPosition;
  symbol = initSymbol;
}

// Tank Destructor
Tank::~Tank(){
	
}

string Tank::getName(){
  return this->name; // returns name
}

int Tank::getHealth(){
  return this->health; // returns health
}

int Tank::getSpeed(){
  return this->speed; // returns speed
}

int Tank::getPosition(){
  return this->position; // returns position
}

void Tank::decreaseHealth(){
  this->health--; // decresases health
}

void Tank::increaseHealth(){
  this->health++; // increases health
}

void Tank::increaseSpeed(){
  this->speed++; // increases speed
}

void Tank::moveRight(){
  this->position++; // increases position
}

void Tank::moveLeft(){
  this->position--; // decreases position
}

char Tank::getSymbol(){
  return this->symbol; // returns symbol
}
