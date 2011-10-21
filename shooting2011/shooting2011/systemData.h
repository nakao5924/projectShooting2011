#ifndef __SYSTEMDATA_H__
#define __SYSTEMDATA_H__

#include "Dxlib.h"
struct textPosition{
  int lifePosX0;
  int lifePosY0;
  int lifePosX1;
  int lifePosY1;

  int scorePosX0;
  int scorePosY0;
  int scorePosX1;
  int scorePosY1;
};

const textPosition textPositions[] = {
  {610, 10, 756, 10, 610, 50, 720, 50},
  {610, 160, 756, 160, 610, 200, 720, 200},
  {610, 310, 756, 310, 610, 350, 720, 350},
  {610, 460, 756, 460, 610, 500, 720, 500},
};


class SystemData {
  deque<int> lifes;
  deque<int> scores;

public:
  int COLOR_BLACK;
  int COLOR_GREY;
  int COLOR_WHITE;

  SystemData();
  void addHero();
  void addScore(int heroId, int dScore);
  void addLife(int heroId, int dLife);
  int getLife(int heroId);
  void draw();
};

#endif
