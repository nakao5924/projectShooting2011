#include "something.h"

bool isInStage( double x, double y){
  return 0 <= x && x <= STAGE_WIDTH && 0 <= y && y <= STAGE_HEIGHT;
}

bool isInStage( int x, int y, int size){
  return -size <= x && x <= STAGE_WIDTH + size && -size <= y && y <= STAGE_HEIGHT + size;
}
