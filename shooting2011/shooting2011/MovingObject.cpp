#include "main.h"
#include "movingObject.h"

Rect MovingObject::getGraphicRect(){ return graphicRect; }
Rect MovingObject::getHitRect(){ return hitRect; }

void MovingObject::action(){
  move();
  fire();
}

void MovingObject::draw(){
  DrawGraph( static_cast<int>(SIDE_WIDTH + graphicRect.x - graphicRect.width/2), 
    static_cast<int>(graphicRect.y - graphicRect.height/2), graphic, true);
}

void MovingObject::move(){
  pair<double,double> temp;
  temp = movePattern->action(hitRect.x, hitRect.y);
  graphicRect.x = temp.first;
  graphicRect.y = temp.second;
  hitRect.x = temp.first;
  hitRect.y = temp.second;
}

void MovingObject::fire(){
}

MovingObject::~MovingObject(){}
