#ifndef __ENEMYBULLET_H__
#define __ENEMYBULLET_H__
#include "movingObject.h"

class EnemyBullet : public MovingObject{
private:

public:
  EnemyBullet( double x, double y, double vx, double vy);
  ~EnemyBullet();
//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
  bool isValid();
};

#endif
