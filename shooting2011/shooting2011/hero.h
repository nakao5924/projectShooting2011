#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
	
private:


public:
  // ‚¢‚Â‚©private‚ÉˆÚ‚µ‚Ü‚µ‚å‚¤@@nakao
	int heroId;
  int getHeroId();
	Hero(){}
	Hero(int _heroId, int direction);
	~Hero();

  void absorbDamage( int damage);
  void statusShift();
};

#endif