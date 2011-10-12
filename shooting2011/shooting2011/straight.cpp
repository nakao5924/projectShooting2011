#include "main.h"
#include "movePattern.h"

MovePatternUniformlyAcceleratedLinearMotion::MovePatternUniformlyAcceleratedLinearMotion(double _vx,double _vy,double _a){
	vx = _vx;
	vy = _vy;
	theta = atan2(vy,vx);
	ax = _a*sin(theta);
	ay = _a*cos(theta);
	frame = 0;
}
pair<double,double> MovePatternUniformlyAcceleratedLinearMotion::action(double x,double y){
	pair<double,double> ret;
	ret.first = x+vx+ax*frame;
	ret.second = y+vy+ay*frame;
	frame++;
	return ret;
}
