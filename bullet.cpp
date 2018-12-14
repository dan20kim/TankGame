#include "bullet.h"

/* Bullet are created whenever
 * the player or computer decides
 * to shoot. A bullet has properties
 * that have both position and velocity.
 * The accleration is gravity, so it is
 * a constant. */

using namespace std;
// Bullet constructor
Bullet::Bullet(){
  power = 0;
  angle = 0;
  xPosition = 0;
  yPosition = 0;
  xPower = power*cos((angle*PI)/180.0);
  yPower = power*sin((angle*PI)/180.0);
}

// Bullet Constructor
Bullet::Bullet(double initPower, double initAngle, double initXPosition, double initYPosition){
  power = initPower;
  angle = initAngle;
  xPosition = initXPosition;
  yPosition = initYPosition;
  xPower = power*cos((angle*PI)/180.0);
  yPower = power*sin((angle*PI)/180.0);
}

// Bullet Destructor
Bullet::~Bullet(){
	
}

void Bullet::updateBullet(){
  xPosition += .05*xPower; // Multiplied by .05 so that the xPosition and yPosition
  yPosition -= .05*yPower; // increment in small intervals. This makes the curve look more realistic
  yPower -= .0981; // Gravitational Constant
}

double Bullet::getPower(){
  return this->power; // returns power
}

double Bullet::getAngle(){
  return this->angle; // returns angle
}

double Bullet::getXPosition(){
  return this->xPosition; // returns xPosition
}

double Bullet::getYPosition(){
  return this->yPosition; // returns YPosition
}
