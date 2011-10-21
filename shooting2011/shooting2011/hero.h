#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
  
private:


public:
  // いつかprivateに移しましょう　@nakao
  int heroId;
  int getHeroId();
  Hero(){}
  Hero(int _heroId, int direction);
  ~Hero();

  void absorbDamage( int damage);
  void statusShift();
};

#endif