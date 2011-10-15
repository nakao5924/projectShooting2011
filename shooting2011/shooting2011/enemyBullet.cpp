#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"

EnemyBullet::EnemyBullet( double x, double y, double vx, double vy){
  graphic = LoadGraph( "../graphic/heroBullet.bmp" ) ;
  graphicRect = Rect(x, y, 8, 8);
  hitRect = Rect(x, y, 4, 8);
  movePattern = new MovePatternStraight(vx, vy);
}

EnemyBullet::~EnemyBullet(){
  delete movePattern;
}

bool EnemyBullet::isValid(){
  return isInStage( graphicRect);
}