#include "main.h"
#include "shooting.h"
#include "shootingAccessor.h"
#include "stage.h"
#include "tag.h"
#include "msgdump.h"
Shooting::Shooting(){
	gameClock = 0;
	ShootingAccessor::setShooting(this);
	ShootingAccessor::addHero(new Hero(0, 2));
	curStageNum = 0;
	stage = NULL;
  gameStatus = GAME_SELECT;
  isSelected.resize( 4, 0);
  heroDirections.resize( 4, 0);
}
Shooting::Shooting(int heroNum){
  gameClock = 0;
  //fpsTimer = GetNowCount();
  ShootingAccessor::setShooting(this);
	for(int i = 0; i < heroNum; ++i){
	  ShootingAccessor::addHero(new Hero(i, (i + 2) % 4));
    systemData.addLife( i, 10);
	}
  //ShootingAccessor::addHero(new Hero(1,1));
  //ShootingAccessor::addHero(new Hero(2,2));
  //ShootingAccessor::addHero(new Hero(3,3));
	curStageNum = 0;
	stage = NULL;
  gameStatus = GAME_SELECT;
  isSelected.resize( 4, 0);
  heroDirections.resize( 4, 0);
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
/*
void Shooting::calibrateFps(){
  int term;
  term = GetNowCount()-fpsTimer;
  if(16-term>0) Sleep(16-term);
  fpsTimer = GetNowCount();
  return;
}
*/
void Shooting::popUp(){
  /*for (int i=0; i<ENEMY_NUM; i++){
    if( enemyDatas[i]->popUpTime == gameClock){
      ShootingAccessor::addEnemy( new Enemy( *enemyDatas[i]));
    }
  }*/
	stage->popUp();
}

bool Shooting::isBeginStage(){
	return curStageNum == 0 || !stage->isValid();
}

void Shooting::nomalAction(){	
	if(isBeginStage()){
		delete stage;
		stage = new Stage(++curStageNum);
	}
  popUp();
	
  gameClock++;


  // action
	{
    for (int i=0; i<(int)heros.size(); i++) heros[i]->action();
    for (int i=0; i<(int)enemys.size(); i++) enemys[i]->action();
    for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->action();
    for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->action();
  }

  // hit
  // 同時にあたった場合の処理はどうする？
  hitMovingObject();
  
  // status shift
  {
    for (int i=0; i<(int)heros.size(); i++) heros[i]->statusShift();
    for (int i=0; i<(int)enemys.size(); i++) enemys[i]->statusShift();
    for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->statusShift();
    for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->statusShift();
  }

  // hero death
  {
    for (int i=0; i<(int)heros.size(); i++){
      if (heros[i]->getStatus() == REBIRTH && 
        systemData.getLife( heros[i]->getHeroId()) <= 0){
        heros[i]->changeStatus( INVALID);
      }
    }
  }
  //erase
  eraseMovingObject();

	static const int gameBackGraphId = graresource.getID("background");
  graresource.drawgraph(0,0,gameBackGraphId,0,false);

  //calibrateFps();
  //draw();
}

void Shooting::gameOverAction(){
  //いつか差し替える nakao
//  static const int gameOverGraphId = graresource.getID( "gameOver");
//  graresource.drawgraph( 0, 0, gameOverGraphId, false);
	SetFontSize(70);
  graresource.drawstring( 100, 100, "game over", WHITE);
}

void Shooting::gameClearAction(){
  //いつか差し替える nakao
//  static const int gameClearGraphId = graresource.getID( "gameClear");
//  graresource.drawgraph( 0, 0, gameClearGraphId, false);
	SetFontSize(70);
  graresource.drawstring( 100, 100, "game clear", WHITE);
}

void Shooting::gameSelectAction(){
  static bool first = true;
  static const int selectGraphId = graresource.getID( "selectImg");
  static vector<string> DIR(4);// = {"up", "right", "down", "left"};
  static vector<vector<int> > selectHeroGraphId(4, vector<int>(4));
  static vector<int> selectedGraphId( 4);

  static const int zenpoId = graresource.getID( "zenpoFront");
  static const int uhoId = graresource.getID( "uhoRight");
  static const int kohoId = graresource.getID( "kohoRear");
  static const int sahoId = graresource.getID( "sahoLeft");
  if (first){
    selectedGraphId[0] = graresource.getID( "ready0");
    selectedGraphId[1] = graresource.getID( "ready1");
    selectedGraphId[2] = graresource.getID( "ready2");
    selectedGraphId[3] = graresource.getID( "ready3");
    first = false;
    // 0:up, 1:right, 2:down, 3:left
    DIR[0] = "up";
    DIR[1] = "right";
    DIR[2] = "down";
    DIR[3] = "left";

    for (int i=0; i<4; i++){
      for (int j=0; j<4; j++){
        string graphicFileName = string("selectHero") + string(1,(i+'0')) + DIR[j];
        selectHeroGraphId[i][j] = graresource.getID( graphicFileName);
      }
    }
  }

  //vector<Input*>
  // 0:up, 1:right, 2:down, 3:left
  for (int hId = 0; hId < (int)heros.size(); hId++){
    if (inputs[hId]->up()){
      heroDirections[hId] = 0;
    } else if (inputs[hId]->right()){
      heroDirections[hId] = 1;
    } else if (inputs[hId]->down()){
      heroDirections[hId] = 2;
    } else if (inputs[hId]->left()){
      heroDirections[hId] = 3;
    } else if (inputs[hId]->buttonA()){
      isSelected[hId] = true;
    } else if (inputs[hId]->buttonB()){
      isSelected[hId] = false;
    }
  }

  graresource.drawgraph( 0, 0, selectGraphId, 0, false);
  const static int shgPosX[4] = {50,450,50,450};
  const static int shgPosY[4] = {0,0,300,300};
  for (int i=0; i<(int)heros.size(); i++){
    graresource.drawgraph( shgPosX[i], shgPosY[i], 
      selectHeroGraphId[i][heroDirections[i]], 0, true);
  }


  const static int namePosX[4] = {200,600,200,600};
  const static int namePosY[4] = {150,150,450,450};
  for (int i=0; i<4; i++){
    if (heroDirections[i]==0) graresource.drawgraph( namePosX[i], namePosY[i], zenpoId, 0, true);
    if (heroDirections[i]==1) graresource.drawgraph( namePosX[i], namePosY[i], uhoId, 0, true);
    if (heroDirections[i]==2) graresource.drawgraph( namePosX[i], namePosY[i], kohoId, 0, true);
    if (heroDirections[i]==3) graresource.drawgraph( namePosX[i], namePosY[i], sahoId, 0, true);
  }

  const static int sgPosX[4] = {0,400,0,400};
  const static int sgPosY[4] = {0,0,300,300};
  for (int i=0; i<(int)heros.size(); i++){
    if (isSelected[i]){
      graresource.drawgraph( sgPosX[i], sgPosY[i], 
        selectedGraphId[i], 0, true);
    }
  }
}

void Shooting::action(){
  static int frameCount = 0;
  frameCount++;

  if (gameStatus == NOMAL) nomalAction();
  else if (gameStatus == GAME_OVER) gameOverAction();
  else if (gameStatus == GAME_CLEAR) gameClearAction();
  else if (gameStatus == GAME_SELECT) gameSelectAction();
  else if (gameStatus == FIN) assert( false && "shooting action. status is fin.");
  else assert( false && "shooting action");

  // status shift
  if (gameStatus == GAME_SELECT){
    bool flag = true;
    for (int i=0; i<heros.size(); i++) {
      if (!isSelected[i]) flag = false;
    }
    if (flag){
      gameStatus = NOMAL;
      frameCount = 0;

      for (int i=0; i<(int)heros.size(); i++){
        heros[i]->setDirection( heroDirections[i]);
      }
    }
  } else if (gameStatus == NOMAL){
    bool gameOverFlag = true;
    for (int i=0; i<heros.size(); i++){
      if (heros[i]->getStatus() != INVALID) {
        gameOverFlag = false;
        break;
      }
    }
    if (gameOverFlag){
      frameCount = 0;
      gameStatus = GAME_OVER;
    } else if (!stage->isValid()){
      frameCount = 0;
      gameStatus = GAME_CLEAR;
    }
		draw();
  } else if (GAME_OVER){
    if (frameCount >= 180) gameStatus = FIN;
  } else if (GAME_CLEAR){
    if (frameCount >= 180) gameStatus = FIN;
  }
}

void Shooting::hitMovingObject(){
  // nakao
  // enemy & heroBullet 分割統治による高速化version
  // rectSizeは64ぐらい、48から128あたりまで
  // 怪しいと思ったら下の安定versoinで
  //*
  static const int rectSize = 64; // more than (enemy size + hero bullet size)
  static const int W = (STAGE_WIDTH + rectSize-1) / rectSize;
  static const int H = (STAGE_HEIGHT + rectSize-1) / rectSize;
  vector<int> h[W][H];//e[W+1][H+1], h[W][H]; 

  for (int i=0; i<(int)heroBullets.size(); i++){
    int a = (int)heroBullets[i]->getHitRect().x / rectSize;
    int b = (int)heroBullets[i]->getHitRect().y / rectSize;
    h[a][b].push_back(i);
  }
  for (int eId=0; eId<(int)enemys.size(); eId++){
    int a = (int)(enemys[eId]->getHitRect().x + rectSize/2) / rectSize;
    int b = (int)(enemys[eId]->getHitRect().y + rectSize/2) / rectSize;

    for (int i=a-1; i<a+1; i++){
      for (int j=b-1; j<b+1; j++){
        if (i < 0 || j < 0 || i >= W || j >= H) continue;
        for (int k=0; k<(int)h[i][j].size(); k++){
          int hId = h[i][j][k];
          if (enemys[eId]->getStatus() != VALID) break;
          if (heroBullets[hId]->getStatus() != VALID) continue;
          if (isHit( enemys[eId]->getHitRect(), heroBullets[hId]->getHitRect())){
            enemys[eId]->absorbDamage( heroBullets[hId]->getAttackPower());
            heroBullets[hId]->absorbDamage( enemys[eId]->getAttackPower());
            if (enemys[eId]->getStatus() == EXPLOSION) 
              systemData.addScore( heroBullets[hId]->getHeroId(), 1000); //score
            systemData.addScore( heroBullets[hId]->getHeroId(), 1); //score
          }
        }
      }
    }
  }
  //*/
  // enemy & heroBullet 愚直に正確なほう
  /*
  for (int i=0; i<(int)enemys.size(); i++){
    for (int j=0; j<(int)heroBullets.size(); j++){
      if (enemys[i]->getStatus() != VALID) break;
      if (heroBullets[j]->getStatus() != VALID) continue;
      if (isHit( enemys[i]->getHitRect(), heroBullets[j]->getHitRect())){
        enemys[i]->absorbDamage( heroBullets[j]->getAttackPower());
        heroBullets[j]->absorbDamage( enemys[i]->getAttackPower());
        if (enemys[i]->getStatus() == EXPLOSION)
          systemData.addScore( heroBullets[j]->getHeroId(), 1000); //score
        systemData.addScore( heroBullets[j]->getHeroId(), 1); //score
      }
    }
  }
  //*/
  // hero & enemyBullet
  for (int i=0; i<(int)heros.size(); i++){
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

void Shooting::eraseMovingObject(){
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

void Shooting::draw(){

  for (int i=0; i<(int)heroBullets.size(); i++) heroBullets[i]->draw();
  for (int i=0; i<(int)heros.size(); i++) heros[i]->draw();
  for (int i=0; i<(int)enemys.size(); i++) enemys[i]->draw();
  for (int i=0; i<(int)enemyBullets.size(); i++) enemyBullets[i]->draw();
  systemData.draw();

#ifdef _DEBUG_
  // FPS checker @nakao
  static int preFPS = 60;
  static int FPS = 0;
  static int preTime = GetNowCount();
  if (GetNowCount() > preTime +1000){
    preTime = GetNowCount();
    preFPS = FPS;
    FPS = 0;
  }
  FPS++;
  dxout << dxclr;
  dxout << "FPS_=_" << preFPS << dxendl;
  // FPS checker end

  dxout << "hSize_=_" << heros.size() << dxendl;
  dxout << "eSize_=_" << enemys.size() << dxendl;
  dxout << "hbSize_=_" << heroBullets.size() << dxendl;
  dxout << "ebSize_=_"<< enemyBullets.size() << dxendl;

	dxout << "heros[0].x_=_"<< heros[0]->getHitRect().x << dxendl;
	dxout << "heros[0].y_=_"<< heros[0]->getHitRect().y << dxendl;
	dxout << "inputs[0]_=_" << inputs[0]->up() << inputs[0]->down() << inputs[0]->right() << inputs[0]->left() << inputs[0]->buttonA() << inputs[0]->buttonB() << inputs[0]->buttonC() << dxendl;
#endif
}

void Shooting::setInput(int clientId, string message){
  inputs[clientId]->decode(message);
}

void Shooting::clearInput(int clientId){
  inputs[clientId]->clear();
}

bool Shooting::isValid(){
  return gameStatus != FIN;
}