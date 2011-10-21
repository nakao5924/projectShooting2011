#include "main.h"
#include "movePattern.h"
#include "heroBullet.h"
#include "hero.h"
#include "rect.h"
#include "firePattern.h"
#include "shootingAccessor.h"
FirePatternNone::FirePatternNone(){
}

bool FirePatternNone::isFire( ){
  return false;
}
void FirePatternNone::action(MovingObject *owner){  
}
//void FirePatternNone::vanishAction(MovingObject *owner){}
FirePatternNone::~FirePatternNone(){
}