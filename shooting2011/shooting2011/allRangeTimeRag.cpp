#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"

FirePatternAllRangeTimeRag::FirePatternAllRangeTimeRag(double _dtheta,double startTheta,double _v,int _interval){
	dtheta = _dtheta;
	curTheta = startTheta;
	v = _v;
	interval = _interval;
	curFrame = 0;
}
bool FirePatternAllRangeTimeRag::isFire(){
	bool ret = (!curFrame);
	curFrame=(curFrame+1)%interval;
	return ret;
}
void FirePatternAllRangeTimeRag::action(MovingObject *owner){
	if(isFire()){
		Rect r = owner->getHitRect();
		ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternUniformlyAcceleratedLinearMotion(v*cos(curTheta),v*sin(curTheta),0.01),new FirePatternNone()));
		curTheta+=dtheta;
		if(dtheta >= PI*2) dtheta-=PI*2;
	}
}
FirePatternAllRangeTimeRag::~FirePatternAllRangeTimeRag(){
	
}