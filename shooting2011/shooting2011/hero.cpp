#include "movingObject.h"

Hero::Hero(){
  graphic = LoadGraph( "../graphic/Ball.png" ) ;
  posx = STAGE_WIDTH/2;
  posy = STAGE_HEIGHT - 50;
  size = 64;
  fireWait = 0;
}

void Hero::move(){
	if( CheckHitKey( KEY_INPUT_UP ) == 1 ) posy -= 3;
	if( CheckHitKey( KEY_INPUT_DOWN ) == 1 ) posy += 3;
	if( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) posx -= 3;
	if( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) posx += 3;
	if( posx < 0 ) posx = 0;
	if( posx > STAGE_WIDTH) posx = STAGE_WIDTH;
	if( posy < 0 ) posy = 0;
	if( posy > STAGE_HEIGHT) posy = STAGE_HEIGHT;
}

bool Hero::fire(){
  if( fireWait == 0 && CheckHitKey( KEY_INPUT_Z) == 1){
    fireWait = 8;
    return true;
  } else{
    return false;
  }
}

void Hero::draw(){
  DrawGraph( SIDE_WIDTH + posx - size/2, posy - size/2, graphic, true);
}

void Hero::transitionState(){
  if( fireWait>0) fireWait--;
}


