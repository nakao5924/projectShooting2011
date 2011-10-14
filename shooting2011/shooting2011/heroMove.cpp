#include "main.h"
#include "movePattern.h"

pair<double,double> MovePatternHero::action( double posx, double posy){
  if( CheckHitKey( KEY_INPUT_UP ) == 1 ) posy -= 3;
	if( CheckHitKey( KEY_INPUT_DOWN ) == 1 ) posy += 3;
	if( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) posx -= 3;
	if( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) posx += 3;
	if( posx < 0 ) posx = 0;
	if( posx > STAGE_WIDTH) posx = STAGE_WIDTH;
	if( posy < 0 ) posy = 0;
	if( posy > STAGE_HEIGHT) posy = STAGE_HEIGHT;

  return make_pair( posx, posy);
}

