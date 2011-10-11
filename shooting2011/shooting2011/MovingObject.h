#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__
#include "main.h"
#include "stageData.h"
#include "attackPattern.h"
#include "movePattern.h"

//class MovingObject{
//}

class Hero{
  int posx, posy;
  int graphic;
  int size;
  int fireWait;

public:
  Hero();
  int getPosx(){ return posx;};
  int getPosy(){ return posy;};
  void move();
  bool fire();
	void draw();
  void transitionState();
};

class Enemy{
  double posx, posy;
  int graphic;
  int size;
  MovePattern *mp;
  AttackPattern *ap;

  void move();
  void fire();

public:
  Enemy( const EnemyData&);
  void action();
	void draw();
  bool isValid();
};

class HeroBullet{
  int posx, posy;
  int graphic;
  int size;

public:
  HeroBullet( int x, int y);
  void move();
	void draw();
  bool isValid();
};

#endif