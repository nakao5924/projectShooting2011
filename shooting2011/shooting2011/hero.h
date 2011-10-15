#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"

class Hero : public MovingObject{
//  int fireWait;

public:
	int heroType;
  Hero();
  ~Hero();
//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
//  void transitionState();
};

#endif