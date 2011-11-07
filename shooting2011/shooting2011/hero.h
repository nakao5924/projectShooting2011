#ifndef __HERO_H__
#define __HERO_H__
#include "movingObject.h"
#include "systemData.h"

class Hero : public MovingObject{
private:
  int direction;
public:
  // ����private�Ɉڂ��܂��傤�@@nakao
	int heroId;
	double delta_x;
	double delta_y;
	void add_delta();
  int getHeroId();
	const Round& get_pushed_round();
  void setDirection( int dir);
	Hero(){}
	Hero(int _heroId, int direction);
	~Hero();
	
  void absorbDamage( int damage);
  void statusShift();
};

#endif