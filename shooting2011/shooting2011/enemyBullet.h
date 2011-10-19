#ifndef __ENEMYBULLET_H__
#define __ENEMYBULLET_H__
#include "movingObject.h"

class EnemyBullet : public MovingObject{
private:

public:
	EnemyBullet(){}
  EnemyBullet( double x, double y, MovePattern *mp,FirePattern *fp);
  ~EnemyBullet();
  bool isValid();

  void absorbDamage( int damage);
  void statusShift();
};

#endif
