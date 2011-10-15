#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "movingObject.h"
#include "stageData.h"

class Enemy : public MovingObject{
private:

public:
	int hp;
  int getHp();
  void addHp( int d);
  Enemy( const EnemyData&);
  ~Enemy();
//  int getPosx(){ return posx;}
//  int getPosy(){ return posy;}
  bool isValid();
};

#endif
