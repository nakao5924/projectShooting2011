#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "main.h"
class MovePattern;
class GraphicPattern;
class FirePattern;
class MovingObject : private NonCopyable{
protected:
  Rect hitRect;
  MovePattern *movePattern;
  FirePattern *firePattern;
  GraphicPattern *graPattern;//upa
  //status
  Status status;
  int frameCount; //status ‚ª•Ï‚í‚Á‚Ä‚©‚ç‚ÌƒtƒŒ[ƒ€”
  //status end

private:
  void move();
  void fire();
  
  int attackPower;
public:
  MovingObject();
  virtual ~MovingObject();
  const Rect& getGraphicRect() const;
  const Rect& getHitRect() const;
  int getframeCount();
  int getAttackPower() const;
  Status getStatus() const;
  void changeStatus( Status _status);
  void action();
  void draw();
  void setPosition(double, double);
	Status getStatus();
  /*
  int getStatus() const;
  void setStatus( int status);
  //*/
};



#endif