#include "MovingObject.h"

Bullet::Bullet( int x, int y){
  graphic = LoadGraph( "../graphic/bullet.bmp" ) ;
  posx = x;
  posy = y;
  size = 8;
}

void Bullet::move(){
  posy -= 8;
}

void Bullet::draw(){
  DrawGraph( posx - size/2, posy - size/2, graphic, true);
}

bool Bullet::isValid(){
  return isInStage( posx, posy, size);
}

