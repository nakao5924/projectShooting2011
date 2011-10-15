#include "main.h"
#include "shooting.h"
#include "shootingAccessor.h"

Shooting::Shooting(){
  gameClock = 0;
  fpsTimer = GetNowCount();
  ShootingAccessor::setShooting(this);
  ShootingAccessor::addHero(new Hero(0,0));
  ShootingAccessor::addHero(new Hero(1,1));
  ShootingAccessor::addHero(new Hero(2,2));
  ShootingAccessor::addHero(new Hero(3,3));
}

Shooting::~Shooting(){
  for(vector<Hero *>::iterator i = heros.begin(); i != heros.end(); ++i){
    delete *i;
  }
  for(vector<Enemy *>::iterator i = enemys.begin(); i != enemys.end(); ++i){
    delete *i;
  }
  for(vector<HeroBullet *>::iterator i = heroBullets.begin(); i != heroBullets.end(); ++i){
    delete *i;
  }
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
      ShootingAccessor::addEnemy( new Enemy( enemyDatas[i]));
    }
  }
}

void Shooting::draw(){
  // 画面を初期化(真っ黒にする)
  ClearDrawScreen() ;

  for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->draw();
  for (int i=0; i<(int)heros.size(); i++) heros[i]->draw();
  for (int i=0; i<(int)enemys.size(); i++) enemys[i]->draw();
	for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->draw();
  systemData.draw();

  // 裏画面の内容を表画面にコピーする
  ScreenFlip();
}

void Shooting::action(){
  popUp();
  gameClock++;

  // action
	{
    // hero
    for (int i=0; i<(int)heros.size(); i++) heros[i]->action();
    // enemy
    for (int i=0; i<(int)enemys.size(); i++) enemys[i]->action();
    // heroBullet
    for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->action();
    // enemyBullet
    for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->action();
  }

  // hit
  // 同時にあたった場合の処理はどうする？ てきとう
  {
    // enemy & heroBullet
    for (int i=0; i<(int)enemys.size(); i++){
      if (enemys[i]->getStatus() != VALID) continue;
      for (int j=0; j<(int)heroBullets.size(); j++){
        if (heroBullets[j]->getStatus() != VALID) continue;
        if (isHit( enemys[i]->getHitRect(), heroBullets[j]->getHitRect())){
          enemys[i]->addHp(-1);
          heroBullets[j]->setStatus( INVALID);
          systemData.addScore( heroBullets[j]->getHeroId(), 10);
        }
      }
    }

    // hero & enemyBullet
    for (int i=0; i<(int)heros.size(); i++){
      if (heros[i]->getStatus() != VALID) continue;
      for (int j=0; j<(int)enemyBullets.size(); j++){
        if (enemyBullets[j]->getStatus() != VALID) continue;
        if (isHit( heros[i]->getHitRect(), enemyBullets[j]->getHitRect())){
          heros[i]->setStatus( EXPLOSION);
          enemyBullets[j]->setStatus( INVALID);
        }
      }
    }

    //hero & enemy
    for (int i=0; i<(int)heros.size(); i++){
      if (heros[i]->getStatus() != VALID) continue;
      for (int j=0; j<(int)enemys.size(); j++){
        if (enemys[j]->getStatus() != VALID) continue;
        if (isHit( heros[i]->getHitRect(), enemys[j]->getHitRect())){
          heros[i]->setStatus( EXPLOSION);
          enemys[j]->addHp(-20);
        }
      }
    }
  }

  // inStage? & enemy death
  {
    //enemy
    for (int i=0; i<(int)enemys.size(); i++){
      if( !isInStage( enemys[i]->getGraphicRect())) enemys[i]->setStatus( INVALID);
      else if( enemys[i]->getHp() < 0) enemys[i]->setStatus( EXPLOSION);
    }
    //heroBullet
    for (int i=0; i<(int)heroBullets.size(); i++){
      if( !isInStage( heroBullets[i]->getGraphicRect())) heroBullets[i]->setStatus( INVALID);
    }
    //enemyBullet
    for (int i=0; i<(int)enemyBullets.size(); i++){
      if( !isInStage( enemyBullets[i]->getGraphicRect())) enemyBullets[i]->setStatus( INVALID);
    }
  }

  //status shift
  {
    //hero
    for (int i=0; i<(int)heros.size(); i++){
      if( heros[i]->getStatus() == EXPLOSION || heros[i]->getStatus() == INVALID){
        systemData.addLife( i, -1);
        heros[i]->setStatus( REBIRTH);
      } else if( heros[i]->getStatus() == REBIRTH){
        heros[i]->setStatus( VALID);
      }
    }
    //enemy
    for (int i=0; i<(int)enemys.size(); i++){
      if( enemys[i]->getStatus() == EXPLOSION || enemys[i]->getStatus() == INVALID){
        enemys.erase( enemys.begin()+i);
        i--;
      }
    }
    //heroBullet
    for (int i=0; i<(int)heroBullets.size(); i++){
      if( heroBullets[i]->getStatus() == EXPLOSION || heroBullets[i]->getStatus() == INVALID){
        heroBullets.erase( heroBullets.begin()+i);
        i--;
      }
    }
    //enemyBullet
    for (int i=0; i<(int)enemyBullets.size(); i++){
      if( enemyBullets[i]->getStatus() == EXPLOSION || enemyBullets[i]->getStatus() == INVALID){
        enemyBullets.erase( enemyBullets.begin()+i);
        i--;
      }
    }
  }

  calibrateFps();
  draw();
}

