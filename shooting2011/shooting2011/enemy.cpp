#include "movingObject.h"
#include "stageData.h"

Enemy::Enemy( const EnemyData &data){
  graphic = LoadGraph( "../graphic/Sikaku.png" );
  posx = data.posx;
  posy = data.posy;
  mp = data.moveType;
  size = 64;
}

void Enemy::move(){
	pair<double,double> nextpos = pair<double,double>(mp->action(posx,posy));
	posx = nextpos.first;
	posy = nextpos.second;
}

void Enemy::fire(){
	//ap->action();
}

void Enemy::action(){
  move();
  fire();
}

bool Enemy::isValid(){
  return isInStage( posx, posy, size);
}

void Enemy::draw(){
  DrawGraph( SIDE_WIDTH + posx - size/2, posy - size/2, graphic, true);
}

