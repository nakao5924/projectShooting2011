#include "main.h"
#include "movingObject.h"
#include "shootingAccessor.h"

MovingObject::MovingObject(){
  attackPower = 1;
  status = VALID;
  frameCount = 0;
}

const Rect& MovingObject::getGraphicRect() const { return graphicRect; }
const Rect& MovingObject::getHitRect() const { return hitRect; }
int MovingObject::getAttackPower() const { return attackPower; }
Status MovingObject::getStatus() const { return status; }

void MovingObject::changeStatus( Status _status){
  frameCount = 0;
  status = _status;
}

void MovingObject::action(){
  if (status == VALID){
    move();
    fire();
  }
  frameCount++;
}


void MovingObject::move(){
  movePattern->action(this);
}

void MovingObject::setPosition(double x, double y) {
  graphicRect.x = x;
  graphicRect.y = y;
  hitRect.x = x;
  hitRect.y = y;
}

void MovingObject::fire(){
	firePattern->action(this);
}

MovingObject::~MovingObject(){
  delete movePattern;
  delete firePattern;
}
/*
void MovingObject::setStatus( int _status){
  status = _status;
}
//*/


void MovingObject::draw(){
  if (graPattern.empty()) {
    res.drawgraph( static_cast<int>(SIDE_WIDTH + graphicRect.x - graphicRect.width/2), 
      static_cast<int>(graphicRect.y - graphicRect.height/2), graphic, true);
  } else {
		res.drawgraph( static_cast<int>(SIDE_WIDTH + graphicRect.x - graphicRect.width/2), 
      static_cast<int>(graphicRect.y - graphicRect.height/2), graPattern[0].getDrawImage(), true);
  }
}

string MovingObject::encode(){
	stringstream ss;
	ss<<graphic;
	string str;
	ss>>str;
//	str+=graphicRect.encode();
	
		
		
	return tag::make_tag("Obj",str);
}