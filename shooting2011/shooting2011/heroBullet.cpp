#include "main.h"
#include "heroBullet.h"

HeroBullet::HeroBullet( double x, double y, double vx, double vy, int type){
  graphic = LoadGraph( "../graphic/heroBullet.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
  movePattern = new MovePatternStraight(vx, vy);
  heroType = type;
}

HeroBullet::~HeroBullet(){
  delete movePattern;
}

bool HeroBullet::isValid(){
  return isInStage( graphicRect);
}

