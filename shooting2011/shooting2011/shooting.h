#ifndef __SHOOTING_H_
#define __SHOOTING_H_
#include "main.h"
#include "movingObject.h"
#include "stageData.h"
#include "systemData.h"

class Shooting{
  int gameClock;
  int fpsTimer;
  vector<Hero> heros;
  vector<Enemy> enemys;
  vector<HeroBullet> heroBullets;
  SystemData systemData;

  void addHero();
  void calibrateFps();
  void draw();
  void popUp();

public:
  Shooting();
  void action();
};

#endif