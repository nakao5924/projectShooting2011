#include "main.h"
#include "heroBullet.h"
#include "firePattern.h"
#include "movePattern.h"
#include "graphicPattern.h"
HeroBullet::HeroBullet( double x, double y,double vx,double vy, int id){
  hitRect = Rect(x, y, 4, 8);
  movePattern = new MovePatternUniformlyAcceleratedLinearMotion(vx,vy,0);
  firePattern = new FirePatternNone();
  string str="HeroBullet";
  stringstream ss;
  ss<<str<<id;
  ss>>str;
  this->graPattern=new GraphicPattern(str);

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
