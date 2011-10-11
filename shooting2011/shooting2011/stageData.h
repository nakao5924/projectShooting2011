#ifndef __STAGEDATA_H__
#define __STAGEDATA_H__
#include"movePattern.h"
const int ENEMY_NUM = 1;
struct EnemyData{
  int popUpTime;
  int posx, posy;
	MovePattern *moveType;
  int fireType;
	EnemyData(int pt,int px,int py,MovePattern *mp){
		popUpTime = pt;
		posx = px;
		posy = py;
		moveType = mp;
	}
};

const EnemyData enemyDatas[] = {
	EnemyData(0,60,60,new MovePatternLissajous(160,160,100,0.06,0,50,0.1,0))
};

#endif