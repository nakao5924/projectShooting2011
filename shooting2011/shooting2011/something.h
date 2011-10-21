#ifndef __SOMETHING_H__
#define __SOMETHING_H__

#include "rect.h"

class NonCopyable{
private:
  NonCopyable( const NonCopyable &);
  NonCopyable &operator = (const NonCopyable &);
public:
  NonCopyable();
};

template<class T, int N>
int getArraySize(T (&array_reference)[N]){
  return N;
}

bool isInStage( double x, double y);
bool isInStage( double x, double y, double w, double h);
bool isInStage( const Rect& r);
bool isHit( const Rect& r1, const Rect& r2);

class NonConstructable : private NonCopyable{
private:
	NonConstructable();
};

#endif