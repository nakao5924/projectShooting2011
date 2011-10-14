#ifndef __MOVEPATTERN_H__
#define __MOVEPATTERN_H__
class MovePattern{
public:
	//���̍��W���󂯎���Ď��̍��W��pair�ŕԂ�
	virtual pair<double,double> action(double,double){return pair<double,double>(0,0);};
	virtual ~MovePattern(){};
};
class MovePatternUniformlyAcceleratedLinearMotion : public MovePattern{
public:
	double vx,vy,v,theta,ax,ay;
	int frame;
	MovePatternUniformlyAcceleratedLinearMotion(double vx,double vy,double a = 0);
	pair<double,double> action(double,double);
};

typedef MovePatternUniformlyAcceleratedLinearMotion MovePatternStraight;  //nakao

class MovePatternLissajous : public MovePattern{
public:
	double ampx,freqx,deltax;
	double ampy,freqy,deltay;
	//���S�̈ʒu
	double posx,posy;
	int frame;
	MovePatternLissajous(double,double,double,double,double,double,double,double);
	pair<double,double> action(double,double);
};

class MovePatternHero : public MovePattern{
public:
  pair<double,double> action(double,double);
};
#endif