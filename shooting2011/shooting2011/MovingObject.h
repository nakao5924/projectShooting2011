#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "movePattern.h"
#include "graphicPattern.h"
#include "firePattern.h"

class MovingObject{
protected:
  int graphic; //check
  vector<GraphicPattern> graPattern;
  Rect graphicRect;
  Rect hitRect;
  MovePattern* movePattern;
  FirePattern* firePattern;

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