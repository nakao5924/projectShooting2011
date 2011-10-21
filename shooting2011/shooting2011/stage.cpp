#include "main.h"
#include "stage.h"
#include "shootingAccessor.h"
#include "reader.h"

Stage::Stage(int stageNum){
  stringstream ss;
  ss<<stageNum;
  string snum;
  ss>>snum;
  int sceneNum=1;
  string fileNameBase="StageData\\stage"+snum+"\\scene";
  while(1){
    stringstream ss;
    ss<<sceneNum;
    string snum;
    ss>>snum;
    string filename = fileNameBase+snum+".in";
    if(GetFileAttributes(filename.c_str()) == -1)break;
    scenes.push_back(Reader::readEnemyData(filename));
    sceneNum++;
  }
  curScene=0;
}
void Stage::popUp(){
  if(scenes.size() == curScene) return;
  scenes[curScene]->popUp();
  if(!scenes[curScene]->isValid()) {
    curScene++;
  }
}
bool Stage::isValid(){
  return curScene < (int)scenes.size();
}
Stage::~Stage(){
  for(int i=0;i<(int)scenes.size();i++){
    delete scenes[i];
  }
}
bool SceneNormal::cmpEnemyData(const EnemyData *const a,const EnemyData *const b){
  return a->popUpTime < b->popUpTime;
}
SceneNormal::SceneNormal(deque<EnemyData*>ed,int _maxFrame){
  enemyList = ed;
  maxFrame = _maxFrame;
  curFrame = 0;
  index = 0;
  sort(enemyList.begin(),enemyList.end(),cmpEnemyData);
}
bool SceneNormal::isValid(){
  return curFrame<maxFrame;
}
void SceneNormal::popUp(){
  while(index<(int)enemyList.size() && curFrame == enemyList[index]->popUpTime){
    ShootingAccessor::addEnemy(new Enemy( *enemyList[index]));
    enemyList[index++]=NULL;
  }
  curFrame++;
}
SceneNormal::~SceneNormal(){
  for(int i=0;i<(int)enemyList.size();i++){
    delete enemyList[i];
  }
}