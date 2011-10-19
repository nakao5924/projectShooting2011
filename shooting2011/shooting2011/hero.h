#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
	
private:

//  int fireWait;

public:
	int heroId;
	Hero(){}
	Hero(int _heroId, int direction);
	~Hero();

  void absorbDamage( int damage);
  void statusShift();

//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
//  void transitionState();
};

#endif