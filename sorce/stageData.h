#ifndef __STAGEDATA_H__
#define __STAGEDATA_H__

const int ENEMY_NUM = 10;
struct EnemyData{
  int popUpTime;
  int posx, posy;
  int moveType;
  int fireType;
};

const EnemyData enemyDatas[] = {
  {0, 10, 0, 1, 0},
  {10, 20, 0, 1, 0},
  {20, 30, 0, 1, 0},
  {60, 60, 0, 1, 0},
  {70, 70, 0, 1, 0},
  {80, 80, 0, 1, 0},
  {150, 40, 0, 1, 0},
  {150, 600, 0, 1, 0},
  {210, 70, 0, 1, 0},
  {210, 570, 0, 1, 0},
};

#endif