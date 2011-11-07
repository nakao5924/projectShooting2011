#include "main.h"
#include "movingObject.h"
#include "enemyBullet.h"
#include "graphicResource.h"
EnemyBullet::EnemyBullet( double x, double y, MovePattern *mp, FirePattern *fp, GraphicPattern *gp){
  hitRect = Rect(x, y, 4, 8);
  movePattern = mp;
	firePattern = fp;
	graPattern = gp;
	//’e‚Ìí—Ş‚É‘Î‚µ‚Ä‰¹‚ğ•Ï‚¦‚é‚È‚çˆø”‚É‰¹‚ğ’Ç‰Á
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
