#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"
#include "graphicPattern.h"

FirePatternAimedRandom::FirePatternAimedRandom(int _interval,int _n,double _v,int _graphicID){
	interval = _interval;
	n = _n;
	v = _v;
	graphicID=_graphicID;
}
bool FirePatternAimedRandom::isFire(){
	bool ret = (!curFrame);
	curFrame=(curFrame+1)%interval;
	return ret;
}
void FirePatternAimedRandom::action(MovingObject *owner){
	if(isFire() && owner->getStatus()==VALID){
		deque<pair<double,double> > pos = ShootingAccessor::getHeroPos();
		Rect r = owner->getHitRect();
		int ind = rand()%(pos.size());
		double dx = pos[ind].first - r.x;
		double dy = pos[ind].second - r.y;
		double theta = atan2(dy,dx);
		ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(theta),v*sin(theta)),new FirePatternNone(),new GraphicPattern(graphicID)));
	}
}
FirePatternAimedRandom::~FirePatternAimedRandom(){
	
}