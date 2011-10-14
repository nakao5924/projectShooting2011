#include "main.h"
#include "hero.h"

Hero::Hero(){
  graphic = LoadGraph( "../graphic/Ball.png" );

  // Debug@neon
  GraphicPattern pattern;
  graPattern.push_back(pattern);
  graPattern[0].testFunc();
  
  graphicRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2, 64, 64);
  hitRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2, 8, 8);

  movePattern = new MovePatternHero();

//  fireWait = 0;
}

Hero::~Hero(){
  delete movePattern;
}

/*
bool Hero::fire(){
//  if( fireWait == 0 && CheckHitKey( KEY_INPUT_Z) == 1){
  if( CheckHitKey( KEY_INPUT_Z) == 1){
//    fireWait = 8;
    return true;
  } else{
    return false;
  }
}
*/

/*
void Hero::transitionState(){
  if( fireWait>0) fireWait--;
}
*/

