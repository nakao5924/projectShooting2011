#ifndef __STAGE_H__
#define __STAGE_H__
#include "enemy.h"
#include "background.h"
class Scene :private NonCopyable{
public:
	virtual void popUp()=0;
	virtual bool isValid()=0;
	virtual ~Scene(){};
};
class SceneNormal : public Scene{
	BackGround bg;
	int curFrame,maxFrame,index;
	deque<EnemyData *> enemyList;
	static bool cmpEnemyData(const EnemyData *const a,const EnemyData *const b);
public:
	SceneNormal(deque<EnemyData*>ed,int _maxFlame);
	void popUp();
	bool isValid();
	~SceneNormal();
};
class Stage :private NonCopyable{
	deque<Scene *> scenes;
	int curScene;
public:
	Stage(int stageNum);
	void popUp();
	bool isValid();
	~Stage();
};
#endif 