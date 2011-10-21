#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "movingObject.h"
#include "stageData.h"

class Enemy : public MovingObject{
private:

public:
	Enemy(){}
	int hp;
  int getHp();
  //void addHp( int d);
  Enemy( const EnemyData&);
	Enemy(double x,double y,MovePattern *mp,FirePattern *fp,GraphicPattern *gp,int _hp);
  ~Enemy();
  bool isValid();
  
  void absorbDamage( int damage);
  void statusShift();
};

#endif
