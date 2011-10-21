

#ifndef __STAGEDATA_H__
#define __STAGEDATA_H__
#include"movePattern.h"
#include"firePattern.h"
#include"graphicPattern.h"
#include "patternComposer.h"
//extern const int ENEMY_NUM;
struct EnemyData{
  int popUpTime;
  double posx, posy;
  MovePattern *moveType;
  FirePattern *fireType;
  GraphicPattern*graType;
  EnemyData(int pt,double px,double py,MovePattern *mp,FirePattern *fp,GraphicPattern*gp){
    popUpTime = pt;
    posx = px;
    posy = py;
    moveType = mp;
    fireType = fp;
    graType = gp;
  }
};
extern const deque<EnemyData*> enemyDatas;
#endif