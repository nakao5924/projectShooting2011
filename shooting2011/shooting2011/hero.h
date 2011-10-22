#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
private:
  int direction;

public:
  // Ç¢Ç¬Ç©privateÇ…à⁄ÇµÇ‹ÇµÇÂÇ§Å@@nakao
	int heroId;
  int getHeroId();
  void setDirection( int dir);
	Hero(){}
	Hero(int _heroId, int direction);
	~Hero();

  void absorbDamage( int damage);
  void statusShift();
};

#endif