#include "main.h"
#include "movePattern.h"
#include "shootingAccessor.h"

MovePatternHero::MovePatternHero(int _heroId){
	heroId = _heroId;
}

void MovePatternHero::action(MovingObject *owner){
	Input input = ShootingAccessor::getInput(heroId);
	double x0 = owner -> getHitRect().x;
	double y0 = owner -> getHitRect().y;
	if( input.up() ) y0 -= 3;
	if( input.down() ) y0 += 3;
	if( input.left() ) x0 -= 3;
	if( input.right() ) x0 += 3;
	if( x0 < 0 ) x0 = 0;
	if( x0 > STAGE_WIDTH) x0 = (double)STAGE_WIDTH;
	if( y0 < 0 ) y0 = 0;
	if( y0 > STAGE_HEIGHT) y0 = (double)STAGE_HEIGHT;
	owner -> setPosition(x0, y0);
}
