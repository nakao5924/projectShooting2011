#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"

EnemyBullet::EnemyBullet( double x, double y, MovePattern *mp,FirePattern *fp){
  graphic = LoadGraph( "../graphic/enemyBullet0.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
	firePattern = fp;
}

EnemyBullet::~EnemyBullet(){
}

bool EnemyBullet::isValid(){
  return isInStage( graphicRect);
}

void EnemyBullet::absorbDamage( int damage){
  changeStatus( INVALID);
}

void EnemyBullet::statusShift(){
  if (!isInStage( hitRect)) changeStatus( INVALID);
}
