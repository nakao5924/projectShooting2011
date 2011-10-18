#include "main.h"
#include "something.h"

NonCopyable::NonCopyable(){
  ;
};

bool isInStage( double x, double y){
  return 0 <= x && x <= STAGE_WIDTH && 0 <= y && y <= STAGE_HEIGHT;
}

bool isInStage( double x, double y, double width, double height){
  return -width <= x && x <= STAGE_WIDTH + width && -height <= y && y <= STAGE_HEIGHT + height;
}

bool isInStage( const Rect& r){
  return isInStage(r.x, r.y, r.width, r.height);
}

bool isHit( const Rect& r1, const Rect& r2){
  return (abs(r1.x - r2.x)*2 < (r1.width + r2.width)) &&
    (abs(r1.y - r2.y)*2 < (r1.height + r2.height));
}
