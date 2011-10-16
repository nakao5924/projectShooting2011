#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
//  int fireWait;

public:
	int heroId;

	Hero(int _heroId, int direction);
	~Hero();

//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
//  void transitionState();
};

#endif