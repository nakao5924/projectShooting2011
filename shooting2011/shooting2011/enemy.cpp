#include "MovingObject.h"
#include "stageData.h"

Enemy::Enemy( const EnemyData &data){
  graphic = LoadGraph( "../graphic/Sikaku.png" );
  posx = data.posx;
  posy = data.posy;
  size = 64;
}

void Enemy::move(){
  posy += 3;
}

void Enemy::fire(){
  ;
}

void Enemy::action(){
  move();
  fire();
}

bool Enemy::isValid(){
  return isInStage( posx, posy, size);
}

void Enemy::draw(){
  DrawGraph( posx - size/2, posy - size/2, graphic, true);
}

