#ifndef __HEROBULLET_H__
#define __HEROBULLET_H__
#include "movingObject.h"

class HeroBullet : public MovingObject{
private:
  int heroType;
public:
  HeroBullet( double x, double y, double vx,double vy, int heroType);
  ~HeroBullet();
//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
  bool isValid();
};

#endif
