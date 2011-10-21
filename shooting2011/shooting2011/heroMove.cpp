#include "main.h"
#include "movePattern.h"
#include "shootingAccessor.h"

MovePatternHero::MovePatternHero(int _heroId){
	heroId = _heroId;
}

void MovePatternHero::action(MovingObject *owner){
	if(owner->getStatus()==VALID || owner->getStatus()==REBIRTH){
		Input input = ShootingAccessor::getInput(heroId);
		double x0 = owner -> getHitRect().x;
		double y0 = owner -> getHitRect().y;
		if( input.up() ) y0 -= 5;
		if( input.down() ) y0 += 5;
		if( input.left() ) x0 -= 5;
		if( input.right() ) x0 += 5;
		if( x0 < 0 ) x0 = 0;
		if( x0 > STAGE_WIDTH) x0 = (double)STAGE_WIDTH;
		if( y0 < 0 ) y0 = 0;
		if( y0 > STAGE_HEIGHT) y0 = (double)STAGE_HEIGHT;
		owner -> setPosition(x0, y0);
	}
}
