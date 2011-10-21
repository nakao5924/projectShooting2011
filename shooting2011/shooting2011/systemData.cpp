#include "main.h"
#include "systemData.h"
#include"tag.h"
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


void SystemData::draw() {
	int color = COLOR_WHITE;
	//int strWidthLife, strWidthScore;

	graresource.drawbox(SIDE_WIDTH, 0, SIDE_WIDTH + STAGE_WIDTH, STAGE_HEIGHT, COLOR_WHITE, FALSE);
	graresource.drawbox(0, 0, SIDE_WIDTH, STAGE_HEIGHT, COLOR_BLACK, TRUE);
	graresource.drawbox(SIDE_WIDTH + STAGE_WIDTH, 0, WINDOW_WIDTH, STAGE_HEIGHT, COLOR_BLACK, TRUE);
	graresource.drawline(SIDE_WIDTH + STAGE_WIDTH, 150, WINDOW_WIDTH, 150, COLOR_GREY);
	graresource.drawline(SIDE_WIDTH + STAGE_WIDTH, 300, WINDOW_WIDTH, 300, COLOR_GREY);
	graresource.drawline(SIDE_WIDTH + STAGE_WIDTH, 450, WINDOW_WIDTH, 450, COLOR_GREY);


	for(int i=0; i<(int)lifes.size(); i++) {
			//strWidthLife = GetDrawFormatStringWidth("%04d", lifes[i]);
			//strWidthScore = GetDrawFormatStringWidth("%08d", scores[i]);
			graresource.drawstring<string>(textPositions[i].lifePosX0, textPositions[i].lifePosY0, "Life:", color);
			graresource.drawstring<int>(textPositions[i].lifePosX1, textPositions[i].lifePosY1, lifes[i], color);
			graresource.drawstring<string>(textPositions[i].scorePosX0, textPositions[i].scorePosY0, "Score:", color);
			graresource.drawstring<int>(textPositions[i].scorePosX1, textPositions[i].scorePosY1, scores[i],color);
	}
}
