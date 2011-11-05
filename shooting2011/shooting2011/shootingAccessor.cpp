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
deque<pair<double,double> > ShootingAccessor::getHeroPos()
{
	deque<pair<double,double> > ret;
	for(size_t i=0;i<shooting_->heros.size();i++){
		Rect r=shooting_->heros[i]->getHitRect();
		ret.push_back(pair<double,double>(r.x,r.y));
	}
	return ret;
}
