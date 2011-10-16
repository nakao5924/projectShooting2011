#ifndef __STAGE_H__
#define __STAGE_H__
#include"background.h"
#include"main.h"
class Scene{
public:
	virtual bool isValid(){return false;};
	BackGround bg;
	int frame,maxframe;
};
class SceneNormal : public Scene{
public:
	bool isValid();
};
class Stage{
public:
	deque<Scene> scenes;
};
#endif 