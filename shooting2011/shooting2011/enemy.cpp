#include "main.h"
#include "enemy.h"

Enemy::Enemy( const EnemyData &data){
  graphic = LoadGraph( "../graphic/hero0.bmp" );
  graphicRect = Rect( data.posx, data.posy, 32, 32);
  hitRect = Rect( data.posx, data.posy, 32, 32);
  movePattern = data.moveType;
	firePattern = data.fireType;
  hp = 5;
}

Enemy::~Enemy(){
  delete movePattern;
}

bool Enemy::isValid(){
  return isInStage( graphicRect);
}

int Enemy::getHp(){
  return hp;
}

void Enemy::addHp( int d){
  hp += d;
}
