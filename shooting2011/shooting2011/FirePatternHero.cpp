#include "main.h"
#include "movePattern.h"
#include "heroBullet.h"
#include "hero.h"
#include "rect.h"
#include "firePattern.h"
#include "shootingAccessor.h"
FirePatternHero::FirePatternHero(const vector<MovePattern *> &_vm,int _interval){
	vm = _vm;
	interval = _interval;
	curFrame = 0;
	keyPushFlag = false;
}

bool FirePatternHero::isFire( ){
	bool keyFlag = (CheckHitKey(KEY_INPUT_Z)==1);
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

void FirePatternHero::action(MovingObject *self){
	if(isFire()){
		Rect r = self->getHitRect();
		for(int i=0;i<vm.size();i++){ 
			ShootingAccessor::addHeroBullet( new HeroBullet(r.x,r.y,vm[i],heroId));
		}
	}
}

FirePatternHero::~FirePatternHero(){
}