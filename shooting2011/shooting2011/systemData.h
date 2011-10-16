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
  {610, 10, 794, 10, 610, 50, 794, 50},
  {610, 160, 794, 160, 610, 200, 794, 200},
  {610, 310, 794, 310, 610, 350, 794, 350},
  {610, 460, 794, 460, 610, 500, 794, 500},
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
	void addScore(int heroId, int dScore);
	void addLife(int heroId, int dLife);
	void draw();
};

#endif
