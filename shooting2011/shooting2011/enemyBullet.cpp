#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"
#include "graphicResource.h"
EnemyBullet::EnemyBullet( double x, double y, MovePattern *mp, FirePattern *fp, GraphicPattern *gp){
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
	firePattern = fp;
	graPattern = gp;
	//弾の種類に対して音を変えるなら引数に音を追加
	static const int sound_id=graresource.get_sound_id("EnemyBullet");
	graresource.playsound(sound_id);
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
