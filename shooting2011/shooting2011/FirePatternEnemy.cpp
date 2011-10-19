#include "main.h"
#include "movePattern.h"
#include "firePattern.h"
#include "enemyBullet.h"
#include "enemy.h"
#include "shootingAccessor.h"

FirePatternEnemy::FirePatternEnemy(const vector<int> &fs,const vector<vector<MovePattern *> > &_vvmp,int _maxFrame,bool _loop){
	frames = fs;
	vvmp = _vvmp;
	maxFrame = _maxFrame;
	loop = _loop;
	curFrame = 0;
	index = 0;
}
bool FirePatternEnemy::isFire(){
	curFrame++;
	if(index == frames.size()) {
		if(curFrame==maxFrame){
			curFrame=0;
			index = 0;
		}
		return false;
	}
	else if(frames[index]==curFrame){
		index++;
		return true;
	}
	return false;
}
void FirePatternEnemy::action(MovingObject *){
	/*if(isFire()){
		vector<MovingObject *> ret;
		for(int i=0;i<vvmp[index].size();i++){
			ShootingAccessor::addEnemyBullet(new EnemyBullet());
		}
	}*/
}
FirePatternEnemy::~FirePatternEnemy(){
	for(int i=0;i<vvmp.size();i++){
		for(vector<MovePattern *>::iterator j = vvmp[i].begin();j!=vvmp[i].end();j++){
			delete *j;
		}
	}
}