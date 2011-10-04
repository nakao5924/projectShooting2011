#ifndef __SHOOTING_H_
#define __SHOOTING_H_
#include "main.h"
#include "MovingObject.h"
#include "stageData.h"

class Shooting{
  int gameClock;
  int fpsTimer;
  vector<Hero> heros;
  vector<Enemy> enemys;
  vector<HeroBullet> HeroheroBullets;

  void draw();
  void calibrateFps();
  void popUp();

public:
  Shooting();
  void action();
};

#endif