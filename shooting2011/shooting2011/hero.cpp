#include "main.h"
#include "hero.h"

Hero::Hero(int _heroId, int direction){
  graphic = LoadGraph( "../graphic/Ball.png" );

  // Debug@neon
  GraphicPattern pattern;
  graPattern.push_back(pattern);
  graPattern[0].testFunc();
  
  graphicRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2, 64, 64);
  hitRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2, 8, 8);

  movePattern = new MovePatternHero(_heroId);

	//createFirePattern start///////////////////////////////////////////////////
	firePattern=new FirePatternHero(5, _heroId, direction);
	//createFirePattern end/////////////////////////////////////////////////////

	heroId = _heroId;
//  fireWait = 0;
}

Hero::~Hero(){
  //delete movePattern;
}


void Hero::absorbDamage( int damage){
  changeStatus( EXPLOSION);
}

void Hero::statusShift(){
  if (status == VALID){
  } else if (status == EXPLOSION){
    if (frameCount > 10){
      changeStatus( REBIRTH);
    }
  } else if (status == REBIRTH){
    if (frameCount > 180){
      changeStatus( VALID);
    }
  }
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

