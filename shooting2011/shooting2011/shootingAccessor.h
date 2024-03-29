#ifndef __SHOOTINGACCESSOR_H__
#define __SHOOTINGACCESSOR_H__

#include "shooting.h"
#include "hero.h"
#include "enemy.h"
#include "heroBullet.h"
#include "input.h"
// #include "enemyBullet.h"

class ShootingAccessor : private NonConstructable{
private:
  static Shooting *shooting_;
public:
  static void setShooting(Shooting *);
  static void addHeroBullet(HeroBullet *);
  static void addEnemyBullet(EnemyBullet *);
  static void addEnemy(Enemy *);
  static void addHero(Hero *);
  static Input getInput(int heroIndex);
	static deque<pair<double,double> > getHeroPos();
};

#endif // __SHOOTINGACCESSOR_H__
