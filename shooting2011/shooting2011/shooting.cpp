#include "main.h"
#include "shooting.h"
#include "shootingAccessor.h"
#include "stage.h"
#include "tag.h"
#include "msgdump.h"
Shooting::Shooting(){
  gameClock = 0;
  fpsTimer = GetNowCount();
  ShootingAccessor::setShooting(this);
  ShootingAccessor::addHero(new Hero(0,2));
  //ShootingAccessor::addHero(new Hero(1,1));
  //ShootingAccessor::addHero(new Hero(2,2));
  //ShootingAccessor::addHero(new Hero(3,3)); 
}

Shooting::~Shooting(){
  for(deque<Hero *>::iterator i = heros.begin(); i != heros.end(); ++i){
    delete *i;
  }
  for(deque<Enemy *>::iterator i = enemys.begin(); i != enemys.end(); ++i){
    delete *i;
  }
  for(deque<HeroBullet *>::iterator i = heroBullets.begin(); i != heroBullets.end(); ++i){
    delete *i;
  }
  for(deque<Input *>::iterator i = inputs.begin(); i != inputs.end(); ++i){
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
    if( enemyDatas[i]->popUpTime == gameClock){
      ShootingAccessor::addEnemy( new Enemy( *enemyDatas[i]));
    }
  }
}


void Shooting::action(){
  popUp();
  gameClock++;

  //begin getKeyInput test////////li
  inputs[0]->getKeyInput();
  //end getKeyInput test////////

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
    	/*
      if (enemys[i]->getStatus() != VALID) continue;
      //*/
      for (int j=0; j<(int)heroBullets.size(); j++){
        if (enemys[i]->getStatus() != VALID) break;
        if (heroBullets[j]->getStatus() != VALID) continue;
        if (isHit( enemys[i]->getHitRect(), heroBullets[j]->getHitRect())){
          enemys[i]->absorbDamage( heroBullets[j]->getAttackPower());
          heroBullets[j]->absorbDamage( enemys[i]->getAttackPower());
          systemData.addScore( heroBullets[j]->getHeroId(), 10);
        }
      }
    }

    // hero & enemyBullet
    for (int i=0; i<(int)heros.size(); i++){
    	/*
      if (heros[i]->getStatus() != VALID) continue;
      //*/
      for (int j=0; j<(int)enemyBullets.size(); j++){
        if (heros[i]->getStatus() != VALID) break;
        if (enemyBullets[j]->getStatus() != VALID) continue;
        if (isHit( heros[i]->getHitRect(), enemyBullets[j]->getHitRect())){
          heros[i]->absorbDamage( enemyBullets[j]->getAttackPower());
          enemyBullets[j]->absorbDamage( heros[i]->getAttackPower());
          systemData.addLife( i, -1);  // hero life -1        
        }
      }
    }

    //hero & enemy
    for (int i=0; i<(int)heros.size(); i++){
    	/*
      if (heros[i]->getStatus() != VALID) continue;
      //*/
      for (int j=0; j<(int)enemys.size(); j++){
        if (heros[i]->getStatus() != VALID) break;
        if (enemys[j]->getStatus() != VALID) continue;
        if (isHit( heros[i]->getHitRect(), enemys[j]->getHitRect())){
          heros[i]->absorbDamage( enemys[j]->getAttackPower());
          enemys[j]->absorbDamage( heros[i]->getAttackPower());
          systemData.addLife( i, -1);  // hero life -1  
        }
      }
    }
  }
  
  // status shift
  {
    for (int i=0; i<(int)heros.size(); i++) heros[i]->statusShift();
    for (int i=0; i<(int)enemys.size(); i++) enemys[i]->statusShift();
    for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->statusShift();
    for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->statusShift();
  }
  //erase
  {

/*
  // inStage? & enemy death
  {
    //enemy
		//
    for (int i=0; i<(int)enemys.size(); i++){
      if( !isInStage( enemys[i]->getGraphicRect())) enemys[i]->setStatus( INVALID);
      else if( enemys[i]->getHp() < 0) enemys[i]->setStatus( EXPLOSION);
    }//
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
    //*/
    //enemy
    for (int i=0; i<(int)enemys.size(); i++){
      if( enemys[i]->getStatus() == INVALID){
        delete enemys[i];
        enemys.erase( enemys.begin()+i);
        i--;
      }
    }
    //heroBullet
    for (int i=0; i<(int)heroBullets.size(); i++){
      if( heroBullets[i]->getStatus() == INVALID){
        delete heroBullets[i];
        heroBullets.erase( heroBullets.begin()+i);
        i--;
      }
    }
    //enemyBullet
    for (int i=0; i<(int)enemyBullets.size(); i++){
      if( enemyBullets[i]->getStatus() == INVALID){
        delete enemyBullets[i];
        enemyBullets.erase( enemyBullets.begin()+i);
        i--;
      }
    }
  }

  calibrateFps();
  draw();
}


void Shooting::draw(){
  // 画面を初期化(真っ黒にする)
  res.initdraw();

  for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->draw();
  for (int i=0; i<(int)heros.size(); i++) heros[i]->draw();
  for (int i=0; i<(int)enemys.size(); i++) enemys[i]->draw();
	for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->draw();
  systemData.draw();

  dxout << dxclr;
  dxout << enemys.size() << dxendl;
  dxout << heroBullets.size() << dxendl;

  // 裏画面の内容を表画面にコピーする
	res.draw();
}


string Shooting::encode(){
	string str_re;
	string str;
	str="";
	for (int i=0; i<(int)heroBullets.size(); i++) str+=heroBullets[i]->encode();
	str_re+=tag::make_tag("HeroBullets",str);
	str="";
	for (int i=0; i<(int)heros.size(); i++) str+=heros[i]->encode();
	str_re+=tag::make_tag("Hero",str);
	str="";
	for (int i=0; i<(int)enemys.size(); i++) str+=enemys[i]->encode();
	str_re+=tag::make_tag("Enemy",str);
	str="";
	for (int i=0; i<(int)enemyBullets.size(); i++) str+=enemyBullets[i]->encode();
	str_re+=tag::make_tag("EnemyBullets",str);
	str="";
	str+=systemData.encode();
	str_re+=tag::make_tag("SystemData",str);
	return str_re;
}



Shooting* Shooting::decode(string str){
	Shooting* self=new Shooting(0);
	stringstream ss(str);
	string get;
	get=tag::pop_tag("HeroBullets",ss);
	stringstream ss_sub(get);
	while(HeroBullet*obj=HeroBullet::decode<HeroBullet>(ss_sub))heroBullets.push_back(new HeroBullet());
	get=tag::pop_tag("Hero",ss);
	ss_sub.str(get);
	while(1)heros.push_back(new Hero());
	get=tag::pop_tag("Enemy",ss);
	ss_sub.str(get);
	while(1)enemys.push_back(new Enemy());
	get=tag::pop_tag("EnemyBullets",ss);
	ss_sub.str(get);
	while(1)enemyBullets.push_back(new EnemyBullet());
	get=tag::pop_tag("SystemData",ss);
	ss_sub.str(get);
	systemData.decode(ss);
	return self;
}
//*/