#include "main.h"
#include "shootingAccessor.h"
#include "attackPattern.h"

Shooting *ShootingAccessor::_shooting;

void ShootingAccessor::setShooting(Shooting *shooting){
  _shooting = shooting;
}

void ShootingAccessor::addHeroBullet(HeroBullet *heroBullet){
  _shooting->heroBullets.push_back(heroBullet);
}

void ShootingAccessor::addEnemy(Enemy *enemy){
  _shooting->enemys.push_back(enemy);
}

void ShootingAccessor::addHero(Hero *hero){
  _shooting->heros.push_back(hero);
  _shooting->systemData.addHero();
}
