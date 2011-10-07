#ifndef __MOVEPATTERN_H__
#define __MOVEPATTERN_H__
#include "main.h"
class MovePattern{
public:
	//今の座標を受け取って次の座標をpairで返す
	virtual pair<double,double> action(double,double){return pair<double,double>(0,0);};
	virtual ~MovePattern(){};
};
class MovePatternUniformlyAcceleratedLinearMotion : public MovePattern{
public:
	double vx,vy,v,theta,ax,ay;
	int frame;
	MovePatternUniformlyAcceleratedLinearMotion(double vx,double vy,double a);
	pair<double,double> action(double,double);
};
class MovePatternLissajous : public MovePattern{
public:
	double ampx,freqx,deltax;
	double ampy,freqy,deltay;
	//中心の位置
	double posx,posy;
	int frame;
	MovePatternLissajous(double,double,double,double,double,double,double,double);
	pair<double,double> action(double,double);
};
#endif