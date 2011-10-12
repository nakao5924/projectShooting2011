#ifndef __SOMETHING_H__
#define __SOMETHING_H__

#include "rect.h"

bool isInStage( double x, double y);
bool isInStage( double x, double y, double w, double h);
bool isInStage( Rect r);
bool isHit( const Rect& r1, const Rect& r2);

#endif