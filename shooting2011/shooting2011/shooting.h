#ifndef __SHOOTING_H_
#define __SHOOTING_H_
#include "stageData.h"
#include "systemData.h"
#include "hero.h"
#include "enemy.h"
#include "heroBullet.h"
#include "enemyBullet.h"

class Shooting{
  friend class ShootingAccessor;
  int gameClock;
  int fpsTimer;
  vector<Hero *> heros;
  vector<Enemy *> enemys;
  vector<HeroBullet *> heroBullets;
  SystemData systemData;

  void calibrateFps();
  void draw();
  void popUp();

public:
  Shooting();
  ~Shooting();
  void action();
};

#endif