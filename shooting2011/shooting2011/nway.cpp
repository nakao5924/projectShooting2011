#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"

FirePatternNway::FirePatternNway(int _interval,int _n,double _v,double _dir,double _dtheta,int _graphicID){
	graphicID=_graphicID;
	v = _v;
	n=_n;
	dir = _dir;
	interval = _interval;
	dtheta = _dtheta;
	curFrame = 0;
}
bool FirePatternNway::isFire(){
	bool ret = (!curFrame);
	curFrame=(curFrame+1)%interval;
	return ret;
}
void FirePatternNway::action(MovingObject *owner){
	if(isFire() && owner->getStatus()==VALID){
		Rect r=owner->getHitRect();
		if(dir<0 || 2*PI<=dir){
			deque<pair<double,double> > dpos = ShootingAccessor::getHeroPos();
			int sel = rand()%dpos.size();
			double x = dpos[sel].first-r.x;
			double y = dpos[sel].second-r.y;
			dir = atan2(y,x);
		}
		if(n%2){
			ShootingAccessor::addEnemyBullet(
				new EnemyBullet(r.x,r.y,
				new MovePatternStraight(v*cos(dir),v*sin(dir)),
				new FirePatternNone(),
				new GraphicPattern(graphicID)));
			for(int i=0;i<n/2;i++){
				ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(dir+(i+1)*dtheta),v*sin(dir+(i+1)*dtheta)),new FirePatternNone(),new GraphicPattern(graphicID)));
			}
			for(int i=0;i<n/2;i++){
				ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(dir+(-i-1)*dtheta),v*sin(dir+(i+1)*dtheta)),new FirePatternNone(),new GraphicPattern(graphicID)));
			}
		}
		else{
			for(int i=0;i<n/2;i++){
				ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(dir+i*dtheta+dtheta*0.5),v*sin(dir+(i+1)*dtheta+dtheta/2)),new FirePatternNone(),new GraphicPattern(graphicID)));
			}
			for(int i=0;i<n/2;i++){
				ShootingAccessor::addEnemyBullet(new EnemyBullet(r.x,r.y,new MovePatternStraight(v*cos(dir+(-i*dtheta)-dtheta*0.5),v*sin(dir+(i+1)*dtheta-dtheta/2)),new FirePatternNone(),new GraphicPattern(graphicID)));
			}
		}
	}
}

FirePatternNway::~FirePatternNway(){
	
}