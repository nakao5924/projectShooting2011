#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "movePattern.h"
#include "graphicPattern.h"
#include "firePattern.h"

class MovePattern;

enum{
  INVALID,
  VALID,
  EXPLOSION,
  REBIRTH
};

class MovingObject{
protected:
  int graphic; //check
  deque<GraphicPattern> graPattern;
  Rect graphicRect;
  Rect hitRect;
  MovePattern *movePattern;
  FirePattern *firePattern;

private:
  void move();
  void fire();
  int status;

public:
  MovingObject();
  virtual ~MovingObject();
  Rect getGraphicRect() const;
  Rect getHitRect() const;
  void action();
  void draw();
  void setPosition(double, double);
  int getStatus() const;
  void setStatus( int status);
};



#endif