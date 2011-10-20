

#ifndef __STAGEDATA_H__
#define __STAGEDATA_H__
#include"movePattern.h"
#include"firePattern.h"
#include "patternComposer.h"
//extern const int ENEMY_NUM;
struct EnemyData{
  int popUpTime;
  double posx, posy;
	MovePattern *moveType;
  FirePattern *fireType;
	EnemyData(int pt,double px,double py,MovePattern *mp,FirePattern *fp){
		popUpTime = pt;
		posx = px;
		posy = py;
		moveType = mp;
		fireType = fp;
	}
};
extern const deque<EnemyData*> enemyDatas;
#endif