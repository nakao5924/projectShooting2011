#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"
#include "graphicPattern.h"

int FirePatternCreateSelf::counter = 0;
FirePatternCreateSelf::FirePatternCreateSelf(int _interval,double _v,int _hp,int _graphicID){
	interval = _interval;
	graphicID = _graphicID;
	v = _v;
	hp = _hp;
	curFrame = 0;
	counter++;
}
bool FirePatternCreateSelf::isFire(){
	if(counter>50) return false;
	bool ret = (curFrame==(interval-1));
	curFrame=(curFrame+1)%interval;
	return ret;
}
void FirePatternCreateSelf::action(MovingObject *owner){
	if(isFire() && owner->getStatus()==VALID){
		deque<pair<double,double> > pos = ShootingAccessor::getHeroPos();
		Rect r = owner->getHitRect();
		int ind = rand()%(pos.size());
		double dx = pos[ind].first - r.x;
		double dy = pos[ind].second - r.y;
		double theta = atan2(dy,dx);
		theta=theta/3*2+theta/45*(rand()%30);
		ShootingAccessor::addEnemy(new Enemy(r.x,r.y,new MovePatternStraight(v*cos(theta),v*sin(theta)),
			new FirePatternCreateSelf(interval,v,hp,graphicID),new GraphicPattern(graphicID),hp));
	}
}
FirePatternCreateSelf::~FirePatternCreateSelf(){
	counter--;
}