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

	res.drawbox(SIDE_WIDTH, 0, SIDE_WIDTH + STAGE_WIDTH, STAGE_HEIGHT, COLOR_WHITE, FALSE);
	res.drawbox(0, 0, SIDE_WIDTH, STAGE_HEIGHT, COLOR_BLACK, TRUE);
	res.drawbox(SIDE_WIDTH + STAGE_WIDTH, 0, WINDOW_WIDTH, STAGE_HEIGHT, COLOR_BLACK, TRUE);
	res.drawline(SIDE_WIDTH + STAGE_WIDTH, 150, WINDOW_WIDTH, 150, COLOR_GREY);
	res.drawline(SIDE_WIDTH + STAGE_WIDTH, 300, WINDOW_WIDTH, 300, COLOR_GREY);
	res.drawline(SIDE_WIDTH + STAGE_WIDTH, 450, WINDOW_WIDTH, 450, COLOR_GREY);


	for(int i=0; i<(int)lifes.size(); i++) {
			//strWidthLife = GetDrawFormatStringWidth("%04d", lifes[i]);
			//strWidthScore = GetDrawFormatStringWidth("%08d", scores[i]);
			res.drawstring<string>(textPositions[i].lifePosX0, textPositions[i].lifePosY0, "Life:", color);
			res.drawstring<int>(textPositions[i].lifePosX1, textPositions[i].lifePosY1, lifes[i], color);
			res.drawstring<string>(textPositions[i].scorePosX0, textPositions[i].scorePosY0, "Score:", color);
			res.drawstring<int>(textPositions[i].scorePosX1, textPositions[i].scorePosY1, scores[i],color);
	}
}
string SystemData::encode(){
	string str_re;
	string str;
	for(size_t i=0;i<lifes.size();i++)str+=lifes[i]+" ";
	str_re+=tag::make_tag("lifes",str);
	str="";
	for(size_t i=0;i<lifes.size();i++)str+=scores[i]+" ";
	str_re+=tag::make_tag("scores",str);
	return(str_re);
}

SystemData& SystemData::decode(stringstream&ss){
	string str=tag::pop_tag("lifes",ss);

	str=tag::pop_tag("scores",ss);
	return(*new SystemData());
}