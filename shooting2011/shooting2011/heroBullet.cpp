#include "main.h"
#include "heroBullet.h"

HeroBullet::HeroBullet( double x, double y,double vx,double vy, int id){
  graphic = LoadGraph( "../graphic/heroBulletUp.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
	movePattern = new MovePatternUniformlyAcceleratedLinearMotion(vx,vy,0);
	firePattern = new FirePatternNone();
  heroId = id;
}

HeroBullet::~HeroBullet(){
}

bool HeroBullet::isValid(){
  return isInStage( graphicRect);
}

int HeroBullet::getHeroId(){
  return heroId;
}

void HeroBullet::absorbDamage( int damage){
  changeStatus( INVALID);
}

void HeroBullet::statusShift(){
  if (!isInStage( hitRect)) changeStatus( INVALID);
}
