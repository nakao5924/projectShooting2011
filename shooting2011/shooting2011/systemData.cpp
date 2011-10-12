#include "main.h"
#include "systemData.h"

SystemData::SystemData() {
	COLOR_BLACK = GetColor(0, 0, 0);
	COLOR_GREY = GetColor(128, 128, 128);
	COLOR_WHITE = GetColor(255, 255, 255);
}

void SystemData::addHero() {
	lifes.push_back(1);
	scores.push_back(0);
}

void SystemData::addLife(int heroIndex, int dLife)
{
	lifes[heroIndex] += dLife;
}

void SystemData::addScore(int heroIndex, int dScore)
{
	scores[heroIndex] += dScore;
}


void SystemData::draw() {
	int color = COLOR_WHITE;

	DrawBox(SIDE_WIDTH, 0, SIDE_WIDTH + STAGE_WIDTH, STAGE_HEIGHT, COLOR_WHITE, FALSE);

	for(int i=0; i<(int)lifes.size(); i++) {
			DrawString(textPositions[i].lifePosX0, textPositions[i].lifePosY0, "Life:", color);
			DrawFormatString(textPositions[i].lifePosX1, textPositions[i].lifePosY1, color, "%02d", scores[i]);
			DrawString(textPositions[i].scorePosX0, textPositions[i].scorePosY0, "Score:", color);
			DrawFormatString(textPositions[i].scorePosX1, textPositions[i].scorePosY1, color, "%08d", lifes[i]);
	}
}
