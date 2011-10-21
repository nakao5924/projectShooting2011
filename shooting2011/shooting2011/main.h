// all cpp files include "main.h" at first line !!
#ifndef __MAIN_H__
#define __MAIN_H__
#define _DEBUG_
#include <deque>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <fstream>
#include "DxLib.h"
#include "rect.h"
#include "something.h"
#include "windows.h"
using namespace std;

enum Status{
  INVALID,
  VALID,
  EXPLOSION,
  REBIRTH
};
enum TagCode{
	DRAWGRAPH,
	DRAWBOX,
	DRAWLINE,
	DRAWSTRING,
  DRAWINT,
	END
};

enum Mode{
  TITLE,
  SELECT,
  SHOOTING,
  CONNECTED,
  UNCONNECTED
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int STAGE_WIDTH = 600;
const int STAGE_HEIGHT = 600;
const int SIDE_WIDTH = 0;
const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);
const int GREY = GetColor(128, 255, 128);

const double PI = acos(-1.0);


#endif