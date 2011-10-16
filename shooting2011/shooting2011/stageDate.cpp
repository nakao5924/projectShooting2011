#include "main.h"
#include "stageData.h"
#include "reader.h"
const int ENEMY_NUM=3;
const deque<EnemyData*> temp=Reader::readEnemyData("stage.in");
const EnemyData enemyDatas[] = {
	EnemyData(0,60,60,new MovePatternLissajous(160,160,100,0.06,0,50,0.1,0),new FirePatternAllRangeTimeRag(0.05,0,1,5)),
	EnemyData(0,100,60,new MovePatternStraight(0,1),new FirePatternAllRangeTimeRag(0.05,0,1,5)),
	EnemyData(0,60,100,((new PatternComposer<MovePattern>())->add(60, new MovePatternStraight(0, 1))
	                                                        ->add(60, new MovePatternStraight(1, 0))),new FirePatternAllRangeTimeRag(0.05,0,1,5))
};

/*

const int ENEMY_NUM=3;
const EnemyData enemyDatas[] = {
	EnemyData(0,60,60,new MovePatternLissajous(160,160,100,0.06,0,50,0.1,0),new FirePatternAllRangeTimeRag(0.05,0,1,5)),
	EnemyData(0,100,60,new MovePatternStraight(0,1),new FirePatternAllRangeTimeRag(0.05,0,1,5)),
	EnemyData(0,60,100,((new PatternComposer<MovePattern>())->add(60, new MovePatternStraight(0, 1))
	                                                        ->add(60, new MovePatternStraight(1, 0))),new FirePatternAllRangeTimeRag(0.05,0,1,5))
};

//*/