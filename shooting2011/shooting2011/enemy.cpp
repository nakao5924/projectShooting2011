#include "main.h"
#include "enemy.h"

Enemy::Enemy( const EnemyData &data){
  graphic = LoadGraph( "../graphic/Hero0Down.bmp" );
  graphicRect = Rect( data.posx, data.posy, 32, 32);
  hitRect = Rect( data.posx, data.posy, 32, 32);
  movePattern = data.moveType;
	firePattern = data.fireType;
  hp = 5;
}

Enemy::~Enemy(){
}

bool Enemy::isValid(){
  return isInStage( graphicRect);
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
