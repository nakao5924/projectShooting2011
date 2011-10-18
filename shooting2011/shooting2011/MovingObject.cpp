#include "main.h"
#include "movingObject.h"
#include "shootingAccessor.h"

MovingObject::MovingObject(){
  status = VALID;
}

Rect MovingObject::getGraphicRect() const { return graphicRect; }
Rect MovingObject::getHitRect() const  { return hitRect; }

void MovingObject::action(){
  move();
  fire();
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

MovingObject::~MovingObject(){}

int MovingObject::getStatus() const{
  return status;
}

void MovingObject::setStatus( int _status){
  status = _status;
}


void MovingObject::draw(){
  if (graPattern.empty()) {
    DrawGraph( static_cast<int>(SIDE_WIDTH + graphicRect.x - graphicRect.width/2), 
      static_cast<int>(graphicRect.y - graphicRect.height/2), graphic, true);
  } else {
    DrawGraph( static_cast<int>(SIDE_WIDTH + graphicRect.x - graphicRect.width/2), 
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