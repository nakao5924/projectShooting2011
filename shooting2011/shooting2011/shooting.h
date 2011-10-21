#ifndef __SHOOTING_H_
#define __SHOOTING_H_
#include "stageData.h"
#include "systemData.h"
#include "hero.h"
#include "enemy.h"
#include "heroBullet.h"
#include "enemyBullet.h"
#include "input.h"
#include "stage.h"

class Shooting : private NonCopyable{
private:
  friend class ShootingAccessor;
  int gameClock;
  //int fpsTimer;
	int curStageNum; //0-index 0ÇÕdummy

  Stage *stage;
  deque<Hero *> heros;
  deque<Enemy *> enemys;
  deque<HeroBullet *> heroBullets;
  deque<EnemyBullet *> enemyBullets;
  deque<Input *> inputs;
  SystemData systemData;
  void eraseMovingObject();
  void hitMovingObject();

	bool isBeginStage();
  void draw();
  void popUp();

  // èÛë‘ëJà⁄
  enum{
    NOMAL,
    GAME_OVER,
    GAME_CLEAR,
    FIN
  };

  int gameStatus;
  void nomalAction();
  void gameOverAction();
  void gameClearAction();

public:
  Shooting();
  Shooting(int HeroNum);
  ~Shooting();
  void action();
	void setInput(const vector<string> &messages);
  void setInput(int clientId, string message);
  void clearInput(int clientId);
  bool isValid();
  //string encode();
  //Shooting* decode(string);
};

#endif