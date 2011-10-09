#include "MovingObject.h"

HeroBullet::HeroBullet( int x, int y){
  graphic = LoadGraph( "../graphic/HeroBullet.bmp" ) ;
  posx = x;
  posy = y;
  size = 8;
}

void HeroBullet::move(){
  posy -= 8;
}

void HeroBullet::draw(){
  DrawGraph( posx - size/2, posy - size/2, graphic, true);
}

bool HeroBullet::isValid(){
  return isInStage( posx, posy, size);
}

