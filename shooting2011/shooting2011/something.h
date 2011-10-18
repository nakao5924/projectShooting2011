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

bool isInStage( double x, double y);
bool isInStage( double x, double y, double w, double h);
bool isInStage( const Rect& r);
bool isHit( const Rect& r1, const Rect& r2);

#endif