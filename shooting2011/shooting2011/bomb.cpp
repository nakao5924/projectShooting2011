
#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"
#include "graphicPattern.h"

FirePatternBomb::FirePatternBomb(double _dtheta,double _v,int _graphicID){
	dtheta = _dtheta;
	v = _v;
	first = false;
	graphicID=_graphicID;
}
bool FirePatternBomb::isFire(){
	return false;
}
void FirePatternBomb::action(MovingObject *owner){
	if(owner->getStatus()==EXPLOSION && !first){
		Rect r = owner->getHitRect();
		for(double i=0;i<2*PI;i+=dtheta){
			ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(i),v*sin(i)),new FirePatternNone(),new GraphicPattern(graphicID)));
		}
		first = true;
	}
}
FirePatternBomb::~FirePatternBomb(){
	
}