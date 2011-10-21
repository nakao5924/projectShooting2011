
#ifndef __MOVEPATTERN_H__
#define __MOVEPATTERN_H__

#include "movingObject.h"

class MovingObject;

class MovePattern{
public:
	virtual void action(MovingObject *) {};
	virtual ~MovePattern() {};
	//virtual void vanishAction(MovingObject *)=0;
	int frame;
};

class MovePatternUniformlyAcceleratedLinearMotion : public MovePattern{
public:
	double vx,vy,v,theta,ax,ay;
	MovePatternUniformlyAcceleratedLinearMotion(double vx,double vy,double a = 0);
	void action(MovingObject *);
};

typedef MovePatternUniformlyAcceleratedLinearMotion MovePatternStraight;  //nakao

class MovePatternLissajous : public MovePattern{
public:
	double ampx,freqx,deltax;
	double ampy,freqy,deltay;
	//íÜêSÇÃà íu
	double posx,posy;
	MovePatternLissajous(double,double,double,double,double,double,double,double);
	void action(MovingObject *);
};

class MovePatternHero : public MovePattern{
public:
	int heroId;

	MovePatternHero(int _heroId);
	void action(MovingObject *);
};
class MovePatternCircle : public MovePattern{
	double theta,v,omega;
public:
	MovePatternCircle(double theta,double r,double omega);
	void action(MovingObject *);
	~MovePatternCircle();
};
#endif