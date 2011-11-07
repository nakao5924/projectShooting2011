#include "main.h"
#include "systemData.h"
#include "graphicResource.h"
SystemData::SystemData() {
	
	COLOR_BLACK = GetColor(0, 0, 0);
	COLOR_GREY = GetColor(128, 255, 128);
	COLOR_WHITE = GetColor(255, 255, 255);
}

void SystemData::addHero() {
	lifes.push_back(0);
	scores.push_back(0);
}

void SystemData::addLife(int heroId, int dLife)
{
	lifes[heroId] += dLife;
}

void SystemData::addScore(int heroId, int dScore)
{
	scores[heroId] += dScore;
}

int SystemData::getLife( int heroId){
  return lifes[heroId];
}

void SystemData::draw() {
  // replace @nakao
  static const int backGroundSystemId = graresource.get_graphic_id( "systemBg");
  graresource.drawgraph( 600, 0, backGroundSystemId, 0, false);
	int color = COLOR_WHITE;

	for(int i=0; i<(int)lifes.size(); i++) {
			//strWidthLife = GetDrawFormatStringWidth("%04d", lifes[i]);
			//strWidthScore = GetDrawFormatStringWidth("%08d", scores[i]);
    graresource.drawint( textPositions[i].lifePosX1, textPositions[i].lifePosY1, lifes[i], color);
    graresource.drawint( textPositions[i].scorePosX1, textPositions[i].scorePosY1, scores[i],color);
//      graresource.drawstring<int>(textPositions[i].lifePosX1, textPositions[i].lifePosY1, lifes[i], color);
      //graresource.drawstring<int>(textPositions[i].scorePosX1, textPositions[i].scorePosY1, scores[i],color);
	}
}
