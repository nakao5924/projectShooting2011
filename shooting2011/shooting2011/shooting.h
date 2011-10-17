#ifndef __SHOOTING_H_
#define __SHOOTING_H_
#include "stageData.h"
#include "systemData.h"
#include "hero.h"
#include "enemy.h"
#include "heroBullet.h"
#include "enemyBullet.h"
#include "input.h"

class Shooting{
  friend class ShootingAccessor;
  int gameClock;
  int fpsTimer;
  deque<Hero *> heros;
  deque<Enemy *> enemys;
  deque<HeroBullet *> heroBullets;
  deque<EnemyBullet *> enemyBullets;
  deque<Input *> inputs;
  SystemData systemData;

  void calibrateFps();
  void draw();
  void popUp();

public:
  Shooting();
	Shooting(int HeroNum){}
  ~Shooting();
  void action();
	string encode();
	Shooting* decode(string);
};

#endif