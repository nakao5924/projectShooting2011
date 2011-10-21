#include "main.h"
#include "movePattern.h"


MovePatternLissajous::MovePatternLissajous( double x,double y,
    double _ampx,double _freqx,double _deltax,
    double _ampy,double _freqy,double _deltay)
{
  posx=x;
  posy=y;
  ampx = _ampx;
  freqx = _freqx;
  deltax = _deltax;
  ampy = _ampy;
  freqy = _freqy;
  deltay = _deltay;
  frame=0;
}

void MovePatternLissajous::action(MovingObject *owner){
  if(owner->getStatus()==VALID){
    double x = ampx*sin(freqx*frame+deltax)+posx;
    double y = ampy*sin(freqy*frame+deltay)+posy;
    owner -> setPosition(x, y);
    ++frame;
  }
}
