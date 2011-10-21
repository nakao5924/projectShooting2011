#include "main.h"
#include "hero.h"
#include "movePattern.h"
#include "firePattern.h"
#include "graphicPattern.h"
Hero::Hero(int _heroId, int direction){
  hitRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2, 8, 8);

  movePattern = new MovePatternHero(_heroId);

	//createFirePattern start///////////////////////////////////////////////////
	firePattern=new FirePatternHero(5, _heroId, direction);
	//createFirePattern end/////////////////////////////////////////////////////
	string str="Hero";
	stringstream ss;
	ss<<str<<_heroId;
	ss>>str;
	this->graPattern=new GraphicPattern(str);

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

