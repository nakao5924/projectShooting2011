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

void MovePatternUniformlyAcceleratedLinearMotion::action(MovingObject *owner){
	double x0 = owner -> getHitRect().x;
	double y0 = owner -> getHitRect().y;
	owner -> setPosition(x0 + vx + ax * frame, y0 + vy + ay * frame);
	frame++;
}
