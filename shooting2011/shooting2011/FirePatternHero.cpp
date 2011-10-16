#include "main.h"
#include "movePattern.h"
#include "heroBullet.h"
#include "hero.h"
#include "rect.h"
#include "firePattern.h"
#include "shootingAccessor.h"
FirePatternHero::FirePatternHero(int _interval,int _heroId,int _shotType){
	interval = _interval;
	heroId = _heroId;
	shotType = _shotType;
	curFrame = 0;
	keyPushFlag = false;
}

bool FirePatternHero::isFire() {
	bool keyFlag = ( ShootingAccessor::getInput(heroId).buttonA() );
	if(keyFlag){
		if(!keyPushFlag){
			keyPushFlag = true;
			curFrame++;
			return true;
		}
		else{
			curFrame=(curFrame+1)%interval;
			return !curFrame;
		}
	}
	curFrame = 0;
	return keyPushFlag=false;
}

void FirePatternHero::action(MovingObject *owner){
	if(isFire()){
		Rect r = owner->getHitRect();
		if(shotType==0){
			ShootingAccessor::addHeroBullet( new HeroBullet(r.x,r.y,-8,0,heroId));//up
		}
		else if(shotType==1){
			ShootingAccessor::addHeroBullet( new HeroBullet(r.x,r.y,8,0,heroId));//down
		}
		else if(shotType==2){
			ShootingAccessor::addHeroBullet( new HeroBullet(r.x,r.y,0,-8,heroId));//left
		}
		else if(shotType==3){
			ShootingAccessor::addHeroBullet( new HeroBullet(r.x,r.y,0,8,heroId));//right
		}
	}
}

FirePatternHero::~FirePatternHero(){
}