#include "main.h"
#include "enemy.h"

Enemy::Enemy( const EnemyData &data){
  hitRect = Rect( data.posx, data.posy, 32, 32);
  movePattern = data.moveType;
  firePattern = data.fireType;
  graPattern=data.graType;
  hp = 5;
}

Enemy::~Enemy(){
 // delete movePattern;
}

bool Enemy::isValid(){
  return isInStage( hitRect);
}

int Enemy::getHp(){
  return hp;
}

void Enemy::absorbDamage( int damage){
  hp -= damage;
  if (hp < 0) changeStatus( EXPLOSION);
}

void Enemy::statusShift(){
  if (status == VALID){
    if (hp < 0) changeStatus( EXPLOSION);
  } else if (status == EXPLOSION){
    if (frameCount > 120){
      changeStatus( INVALID);
    }
  }
  
  if (!isInStage( getHitRect())){
    changeStatus( INVALID);
  }
  
}
/*
void Enemy::vanishAction(){
	firePattern->vanishAction(this);
}
//*/
