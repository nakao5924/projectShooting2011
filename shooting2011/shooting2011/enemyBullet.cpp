#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"

EnemyBullet::EnemyBullet( double x, double y, MovePattern *mp, FirePattern *fp, GraphicPattern *gp){
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
  firePattern = fp;
  graPattern = gp;
}

EnemyBullet::~EnemyBullet(){
//  delete movePattern;
}

bool EnemyBullet::isValid(){
  return isInStage( hitRect);
}

void EnemyBullet::absorbDamage( int damage){
  changeStatus( INVALID);
}

void EnemyBullet::statusShift(){
  if (!isInStage( hitRect)) changeStatus( INVALID);
}
