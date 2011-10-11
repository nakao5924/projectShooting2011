#include "shooting.h"

Shooting::Shooting(){
  gameClock = 0;
  fpsTimer = GetNowCount();
  addHero();
  addHero();
  addHero();
  addHero();
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
  // ��ʂ�������(�^�����ɂ���)
  ClearDrawScreen() ;

  for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i].draw();
  for (int i=0; i<(int)heros.size(); i++) heros[i].draw();
  for (int i=0; i<(int)enemys.size(); i++) enemys[i].draw();
  systemData.draw();

  // ����ʂ̓��e��\��ʂɃR�s�[����
  ScreenFlip();
}

void Shooting::action(){
  popUp();
  gameClock++;
  // �{�[���N
	{
    for (int i=0; i<(int)heros.size(); i++){
      heros[i].move();
      if( heros[i].fire()) heroBullets.push_back( HeroBullet( heros[i].getPosx(), heros[i].getPosy()));
      heros[i].transitionState();
    }
  }
  // �l�p�N
  {
    for (int i=0; i<(int)enemys.size(); i++) enemys[i].action();
    for (int i=0; i<(int)enemys.size(); i++){
      if( !enemys[i].isValid()) {
        enemys.erase( enemys.begin()+i);
        i--;
      }
    }

  }
  // �e
  {
    for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i].move();
    for (int i=0; i<(int)heroBullets.size(); i++){
      if( !heroBullets[i].isValid()) {
        heroBullets.erase( heroBullets.begin()+i);
        i--;
      }
    }
  }

  draw();
  calibrateFps();
}

void Shooting::addHero()
{
	heros.push_back( Hero());
	systemData.addHero();
}


