#ifndef __SYSTEMDATA_H__
#define __SYSTEMDATA_H__

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
  {10, 10, 174, 30, 10, 50, 120, 70},
  {10, 490, 174, 510, 10, 550, 120, 570},
  {610, 10, 774, 30, 610, 50, 720, 70},
  {610, 490, 774, 510, 610, 550, 720, 570},
};


class SystemData {
	vector<int> lifes;
	vector<int> scores;

public:
	int COLOR_BLACK;
	int COLOR_GREY;
	int COLOR_WHITE;

	SystemData();
	void addHero();
	void addScore(int heroIndex, int dScore);
	void addLife(int heroIndex, int dLife);
	void draw();
};

#endif
