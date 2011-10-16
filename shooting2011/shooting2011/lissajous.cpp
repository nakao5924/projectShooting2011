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
pair<double,double> MovePatternLissajous::action(double x,double y){
	pair<double,double> ret;
	ret.first = ampx*sin(freqx*frame+deltax)+posx;
	ret.second = ampy*sin(freqy*frame+deltay)+posy;
	++frame;
	return ret;

}


/*
MovePatternLissajous::MovePatternLissajous(double cx,double cy,
		double _ampx,double _freqx,double _deltax,
		double _ampy,double _freqy,double _deltay)
{
	posx = cx;
	posy = cy;
	ampx = _ampx;
	freqx = _freqx;
	deltax = _deltax;
	ampy = _ampy;
	freqy = _freqy;
	deltay = _deltay;
	frame=0;
}
pair<double,double> MovePatternLissajous::action(double x,double y){
	pair<double,double> ret;
	ret.first = ampx*sin(freqx*frame+deltax)+posx;
	ret.second = ampy*sin(freqy*frame+deltay)+posy;
	++frame;
	return ret;

}

//*/