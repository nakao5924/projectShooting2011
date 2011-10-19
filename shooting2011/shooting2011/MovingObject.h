#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "movePattern.h"
#include "graphicPattern.h"
#include "firePattern.h"
#include "tag.h"
class MovePattern;

enum Status{
  INVALID,
  VALID,
  EXPLOSION,
  REBIRTH
};

class MovingObject : private NonCopyable{
protected:
  int graphic; //check
  deque<GraphicPattern> graPattern;
  Rect graphicRect;
  Rect hitRect;
  MovePattern *movePattern;
  FirePattern *firePattern;
  //status
  Status status;
  int frameCount; //status ‚ª•Ï‚í‚Á‚Ä‚©‚ç‚ÌƒtƒŒ[ƒ€”
  //status end

private:
  void move();
  void fire();
  
  int attackPower;
  /*
  int status;
//*/
public:
  MovingObject();
  virtual ~MovingObject();
  const Rect& getGraphicRect() const;
  const Rect& getHitRect() const;
  int getAttackPower() const;
  Status getStatus() const;
  void changeStatus( Status _status);
  void action();
  void draw();
  void setPosition(double, double);
  /*
  int getStatus() const;
  void setStatus( int status);
  //*/
	string encode();
	template<class _Obj>
	static _Obj* decode(stringstream&ss){
		string str=tag::pop_tag("Obj",ss);
		if(str==""){
			//¸”s‚µ‚½‚Æ‚«
			return NULL;
		}
//		ss>>graphic;
//		graphicRect.

		return(new _Obj());
	}
};



#endif