#ifndef __STAGEDATA_H__
#define __STAGEDATA_H__
#include"movePattern.h"
#include"firePattern.h"
const int ENEMY_NUM = 2;
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

const EnemyData enemyDatas[] = {
	EnemyData(0,60,60,new MovePatternLissajous(160,160,100,0.06,0,50,0.1,0),new FirePatternAllRangeTimeRag(0.05,0,10,1)),
	EnemyData(0,100,60,new MovePatternStraight(0,1),new FirePatternAllRangeTimeRag(0.05,0,10,1))
};
#endif