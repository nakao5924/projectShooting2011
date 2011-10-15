#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"

EnemyBullet::EnemyBullet( double x, double y, MovePattern *mp,FirePattern *fp){
  graphic = LoadGraph( "../graphic/heroBullet.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
	firePattern = fp;
}

EnemyBullet::~EnemyBullet(){
  delete movePattern;
}

bool EnemyBullet::isValid(){
  return isInStage( graphicRect);
}