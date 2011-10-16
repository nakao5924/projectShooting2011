#include "main.h"
#include "shootingAccessor.h"
#include "firePattern.h"

Shooting *ShootingAccessor::_shooting;

void ShootingAccessor::setShooting(Shooting *shooting){
  _shooting = shooting;
}

void ShootingAccessor::addHeroBullet(HeroBullet *heroBullet){
  _shooting->heroBullets.push_back(heroBullet);
}


void ShootingAccessor::addEnemyBullet(EnemyBullet *enemyBullet){
  _shooting->enemyBullets.push_back(enemyBullet);
}

void ShootingAccessor::addEnemy(Enemy *enemy){
  _shooting->enemys.push_back(enemy);
}

void ShootingAccessor::addHero(Hero *hero, Input *input){
  _shooting->heros.push_back(hero);
  _shooting->inputs.push_back(input); //
  _shooting->systemData.addHero();
}

Input ShootingAccessor::getInput(int heroIndex)
{
	return *(_shooting->inputs[heroIndex]);
}
