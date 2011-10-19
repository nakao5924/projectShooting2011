#ifndef __STAGE_H__
#define __STAGE_H__
#include"background.h"
#include "enemy.h"
class Scene{
public:
	virtual bool isValid(){return false;};
	BackGround bg;
	int frame,maxframe;
	deque<Enemy *> enemylist;
};
class SceneNormal : public Scene{
public:
	bool isValid();
};
class Stage{
public:
	deque<Scene *> scenes;
	int curScene;
};
#endif 