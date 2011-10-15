#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "movePattern.h"
#include "graphicPattern.h"
#include "firePattern.h"

enum{
  INVALID,
  VALID,
  EXPLOSION,
  REBIRTH
};

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
  int status;

public:
  MovingObject();
  virtual ~MovingObject();
  Rect getGraphicRect();
  Rect getHitRect();
  void action();
  void draw();
  int getStatus();
  void setStatus( int status);
};



#endif