#include "main.h"
#include "shootingAccessor.h"
#include "firePattern.h"

Shooting *ShootingAccessor::shooting_;

void ShootingAccessor::setShooting(Shooting *shooting){
  shooting_ = shooting;
}

void ShootingAccessor::addHeroBullet(HeroBullet *heroBullet){
  shooting_->heroBullets.push_back(heroBullet);
}


void ShootingAccessor::addEnemyBullet(EnemyBullet *enemyBullet){
  shooting_->enemyBullets.push_back(enemyBullet);
}

void ShootingAccessor::addEnemy(Enemy *enemy){
  shooting_->enemys.push_back(enemy);
}

void ShootingAccessor::addHero(Hero *hero){
  shooting_->heros.push_back(hero);
  shooting_->inputs.push_back(new Input());
  shooting_->systemData.addHero();
	assert(shooting_->heros.size() == shooting_->inputs.size());
}

Input ShootingAccessor::getInput(int heroIndex)
{
	return *(shooting_->inputs[heroIndex]);
}
