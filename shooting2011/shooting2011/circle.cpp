#include "main.h"
#include "movePattern.h"


MovePatternCircle::MovePatternCircle( double _theta,double _r,double _omega)
{
	theta=_theta;
	//r=_r * sin (_omega/2) * 2; 
	v=_r * _omega;
	omega=_omega;
}

void MovePatternCircle::action(MovingObject *owner){
	if(owner->getStatus()==VALID){
		double x = owner->getHitRect().x - v * sin(theta);
		double y = owner->getHitRect().y + v * cos(theta);
		owner -> setPosition(x, y);
		theta+=omega;

	}
}

MovePatternCircle::~MovePatternCircle(){
}