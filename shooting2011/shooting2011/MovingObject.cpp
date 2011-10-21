#include "main.h"
#include "movingObject.h"
#include "shootingAccessor.h"
#include "movePattern.h"
#include "graphicPattern.h"
#include "firePattern.h"

MovingObject::MovingObject(){
  attackPower = 1;
  status = VALID;
  frameCount = 0;
}

const Rect& MovingObject::getHitRect() const { return hitRect; }
int MovingObject::getAttackPower() const { return attackPower; }
Status MovingObject::getStatus() const { return status; }

int MovingObject::getframeCount(){return (frameCount);}

void MovingObject::changeStatus( Status _status){
  frameCount = 0;
  status = _status;
}

void MovingObject::action(){
  move();
  fire();
  frameCount++;
}


void MovingObject::move(){
  movePattern->action(this);
}

void MovingObject::setPosition(double x, double y) {
  hitRect.x = x;
  hitRect.y = y;
}

Status MovingObject::getStatus(){
  return status;
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
  if(graPattern)graPattern->action(this);
}
