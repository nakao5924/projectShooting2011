#include "shooting.h"

Shooting::Shooting(){
  gameClock = 0;
  fpsTimer = GetNowCount();
  heros.push_back( Hero());
}

void Shooting::calibrateFps(){
  int term;
  term = GetNowCount()-fpsTimer;
  if(16-term>0) Sleep(16-term);
  fpsTimer = GetNowCount();
  return;
}

void Shooting::popUp(){
  for (int i=0; i<ENEMY_NUM; i++){
    if( enemyDatas[i].popUpTime == gameClock){
      enemys.push_back( Enemy( enemyDatas[i]));
    }
  }
}

void Shooting::draw(){
  // 画面を初期化(真っ黒にする)
  ClearDrawScreen() ;

  for (int i=0; i<(int)HeroheroBullets.size(); i++) HeroheroBullets[i].draw();
  for (int i=0; i<(int)heros.size(); i++) heros[i].draw();
  for (int i=0; i<(int)enemys.size(); i++) enemys[i].draw();

  // 裏画面の内容を表画面にコピーする
  ScreenFlip();
}

void Shooting::action(){
  popUp();
  gameClock++;
  // ボール君
	{
    for (int i=0; i<(int)heros.size(); i++){
      heros[i].move();
      if( heros[i].fire()) HeroheroBullets.push_back( HeroBullet( heros[i].getPosx(), heros[i].getPosy()));
      heros[i].transitionState();
    }
  }
  // 四角君
  {
    for (int i=0; i<(int)enemys.size(); i++) enemys[i].action();
    for (int i=0; i<(int)enemys.size(); i++){
      if( !enemys[i].isValid()) {
        enemys.erase( enemys.begin()+i);
        i--;
      }
    }

  }
  // 弾
  {
    for (int i=0; i<(int)HeroheroBullets.size(); i++) HeroheroBullets[i].move();
    for (int i=0; i<(int)HeroheroBullets.size(); i++){
      if( !HeroheroBullets[i].isValid()) {
        HeroheroBullets.erase( HeroheroBullets.begin()+i);
        i--;
      }
    }
  }

  draw();
  calibrateFps();
}

