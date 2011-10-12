#include "main.h"
#include "something.h"

bool isInStage( double x, double y){
  return 0 <= x && x <= STAGE_WIDTH && 0 <= y && y <= STAGE_HEIGHT;
}

bool isInStage( double x, double y, double width, double height){
  return -width <= x && x <= STAGE_WIDTH + width && -height <= y && y <= STAGE_HEIGHT + height;
}

bool isInStage( Rect r){
  return isInStage(r.x, r.y, r.width, r.height);
}

bool isHit( const Rect& r1, const Rect& r2){
  return (abs(r1.x - r2.x) < (r1.width + r2.width)/2) &&
    (abs(r1.y - r2.y) < (r1.height + r2.height)/2);
}
