#ifndef __RECT_H__
#define __RECT_H__
#include "shape.h"

struct Rect:public Shape{
  double x,y,width,height;
  Rect();
  Rect(double x, double y, double width, double height);
};

#endif // __RECT_H__