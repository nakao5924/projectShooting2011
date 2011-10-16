
#ifndef __MOVEPATTERN_H__
#define __MOVEPATTERN_H__


class MovePattern{
public:
	virtual pair<double,double> action(double x,double y) {return pair<double, double> (0, 0);};
	virtual ~MovePattern() {};
	int frame;
};




class MovePatternUniformlyAcceleratedLinearMotion : public MovePattern{
public:
	double vx,vy,v,theta,ax,ay;
	MovePatternUniformlyAcceleratedLinearMotion(double vx,double vy,double a = 0);
	pair<double,double> action(double,double);
};

typedef MovePatternUniformlyAcceleratedLinearMotion MovePatternStraight;  //nakao

class MovePatternLissajous : public MovePattern{
public:
	double ampx,freqx,deltax;
	double ampy,freqy,deltay;
	//íÜêSÇÃà íu
	double posx,posy;
	MovePatternLissajous(double,double,double,double,double,double,double,double);
	pair<double,double> action(double,double);
};

class MovePatternHero : public MovePattern{
public:
  pair<double,double> action(double,double);
};
#endif