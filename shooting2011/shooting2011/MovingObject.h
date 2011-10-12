#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "attackPattern.h" 
#include "movePattern.h"

//#include "firePattern.h"

class MovingObject{
protected:
  int graphic; //check
  Rect graphicRect;
  Rect hitRect;
  MovePattern* movePattern;
  //FirePattern* firePattern;

private:
  void move();
  void fire();

public:
  Rect getGraphicRect();
  Rect getHitRect();
  void action();
  void draw();
  virtual ~MovingObject();
};



#endif