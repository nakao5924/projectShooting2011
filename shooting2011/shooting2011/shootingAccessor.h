#ifndef __SHOOTINGACCESSOR_H__
#define __SHOOTINGACCESSOR_H__

#include "shooting.h"
#include "hero.h"
#include "enemy.h"
#include "heroBullet.h"
#include "input.h"
// #include "enemyBullet.h"

class ShootingAccessor{
private:
  static Shooting *_shooting;
public:
  static void setShooting(Shooting *);
  static void addHeroBullet(HeroBullet *);
  static void addEnemyBullet(EnemyBullet *);
  static void addEnemy(Enemy *);
  static void addHero(Hero *);
  static Input getInput(int heroIndex);
};

#endif // __SHOOTINGACCESSOR_H__
