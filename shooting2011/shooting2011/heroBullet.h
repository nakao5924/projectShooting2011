#ifndef __HEROBULLET_H__
#define __HEROBULLET_H__
#include "movingObject.h"

class HeroBullet : public MovingObject{
private:
  int heroId;
public:
  HeroBullet(){}
  HeroBullet( double x, double y, double vx,double vy, int heroId);
  ~HeroBullet();
  int getHeroId();
  bool isValid();
  //status
  Status status;
  void absorbDamage( int damage);
  void statusShift();

};

#endif
