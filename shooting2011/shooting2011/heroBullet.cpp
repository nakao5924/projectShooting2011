#include "main.h"
#include "heroBullet.h"
#include "firePattern.h"
#include "movePattern.h"
#include "graphicPattern.h"
HeroBullet::HeroBullet( double x, double y,double vx,double vy, int id){
  hitRect = Rect(x, y, 4, 8);
	movePattern = new MovePatternUniformlyAcceleratedLinearMotion(vx,vy,0);
	firePattern = new FirePatternNone();
 	//string str="herobulletup8";

  string dirTmp;
  if (vx < 0) dirTmp = "left";
  if (vx > 0) dirTmp = "right";
  if (vy < 0) dirTmp = "up";
  if (vy > 0) dirTmp = "down";
 	string str = string("herobullet") + dirTmp + string("8");
	this->graPattern=new GraphicPattern(str);
	static const int sound_id=graresource.get_sound_id("HeroBullet");
	graresource.playsound(sound_id);
  heroId = id;
}

HeroBullet::~HeroBullet(){
}

bool HeroBullet::isValid(){
  return isInStage( hitRect);
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
