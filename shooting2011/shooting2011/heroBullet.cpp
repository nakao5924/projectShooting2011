#include "main.h"
#include "heroBullet.h"

HeroBullet::HeroBullet( double x, double y,MovePattern *mp, int type){
  graphic = LoadGraph( "../graphic/heroBullet.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
	firePattern = new FirePatternNone();
  heroType = type;
}

HeroBullet::~HeroBullet(){
  delete movePattern;
}

bool HeroBullet::isValid(){
  return isInStage( graphicRect);
}

