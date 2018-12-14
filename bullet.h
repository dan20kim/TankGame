#ifndef bulletincluded // include only if it has not been included before
#define bulletincluded

#include <iostream>
#include <math.h>
#include "globals.h"

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

#endif
