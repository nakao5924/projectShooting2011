#include "main.h"
#include "hero.h"
#include "movePattern.h"
#include "firePattern.h"
#include "graphicPattern.h"
Hero::Hero(int _heroId, int dir){
  if (_heroId == 0) hitRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2 - 64, 8, 8);
  if (_heroId == 1) hitRect = Rect( STAGE_WIDTH/2 + 64, STAGE_HEIGHT/2, 8, 8);
  if (_heroId == 2) hitRect = Rect( STAGE_WIDTH/2, STAGE_HEIGHT/2 + 64, 8, 8);
  if (_heroId == 3) hitRect = Rect( STAGE_WIDTH/2 -64, STAGE_HEIGHT/2, 8, 8);

  movePattern = new MovePatternHero(_heroId);

	//createFirePattern start///////////////////////////////////////////////////
	firePattern=new FirePatternHero(5, _heroId, dir);
	//createFirePattern end/////////////////////////////////////////////////////
	string str="hero";
	stringstream ss;
	ss<<str<<_heroId;
	ss>>str;
	this->graPattern=new GraphicPattern(str);

	heroId = _heroId;
  direction = 0;
//  fireWait = 0;
}

Hero::~Hero(){
  //delete movePattern;
}

void Hero::setDirection( int dir){
  direction = dir;
	//firePattern=new FirePatternHero(5, _heroId, dir);
  FirePatternHero *temp = dynamic_cast<FirePatternHero *>(firePattern);
  if(temp != NULL){
    temp -> setDirection(dir);
  }

  const static string direction[4] = {"up", "right", "down", "left"};
	string str="hero";
	stringstream ss;
	ss<<str<<heroId;
  ss<<direction[dir]<<"32";
	ss>>str;
	this->graPattern=new GraphicPattern(str);

}

int Hero::getHeroId(){
  return heroId;
}

void Hero::absorbDamage( int damage){
  changeStatus( EXPLOSION);
}

void Hero::statusShift(){
  if (status == VALID){
  } else if (status == EXPLOSION){
    if (frameCount > 104){
      changeStatus( REBIRTH);
    }
  } else if (status == REBIRTH){
    if (frameCount > 60){
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

