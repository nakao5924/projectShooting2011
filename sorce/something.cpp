#include "something.h"

bool isInStage( int x, int y){
  return 0<=x && x<=WINDOW_WIDTH && 0<=y && y<=WINDOW_HEIGHT;
}
bool isInStage( int x, int y, int size){
  return -size<=x && x<=WINDOW_WIDTH+size && -size<=y && y<=WINDOW_HEIGHT+size;
}
