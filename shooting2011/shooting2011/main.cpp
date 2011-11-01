#include "main.h"
#include "shooting.h"
#include "graphicResource.h"
#include "decode.h"
#include "server.h"
#include "client.h"
#include "msgdump.h"
#include <iostream>
//#define SOLOPLAY_MODE
#define NETWORK_SOLOPLAY_MODE
//#define SERVER_MODE
//#define CLIENT_MODE

int PORT = 12345;
#ifdef CLIENT_MODE
// SAKURA
IPDATA SERVER_IP = {192, 168, 0, 100};
#else
// LOCALHOST
IPDATA SERVER_IP = {127, 0, 0, 1};
#endif

int CLIENT_NUM = 1;

void soloplay_main();
void network_soloplay_main();
void server_main();
void client_main();

// WinMain関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, int nCmdShow )
{
	ifstream ifs("../config/default.conf");

	int tmp;
	ifs >> PORT;
	ifs >> tmp;
	SERVER_IP.d1 = tmp;
	ifs >> tmp;
	SERVER_IP.d2 = tmp;
	ifs >> tmp;
	SERVER_IP.d3 = tmp;
	ifs >> tmp;
	SERVER_IP.d4 = tmp;
	ifs >> CLIENT_NUM;

  // 画面モードの設定
  ChangeWindowMode(true);
  SetGraphMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16 ) ;

  // ＤＸライブラリ初期化処理
  if( DxLib_Init() == -1 ) return -1;

  // グラフィックの描画先を裏画面にセット
  SetDrawScreen( DX_SCREEN_BACK );
  SetMainWindowText( "Bullet of the Chaos");

#ifdef SOLOPLAY_MODE
	soloplay_main();
#endif // SOLOPLAY_MODE
#ifdef NETWORK_SOLOPLAY_MODE
	network_soloplay_main();
#endif // NETWORK_SOLOPLAY_MODE
#ifdef SERVER_MODE
	server_main();
#endif // SERVER_MODE
#ifdef CLIENT_MODE
	client_main();
#endif // CLIENT_MODE

  DxLib_End();				// ＤＸライブラリ使用の終了処理
  return 0;					// ソフトの終了
}

#ifdef nakao_SOLOPLAY_MODE
void soloplay_main(){
  Input input;
  Mode status = TITLE;

  graresource.initialize();
  decoder.initialize();
  Shooting *shooting;
  int fpsTimer = GetNowCount();

  while (true){
    if (status == TITLE){
      input.getKeyInput();
      if (input.buttonA()){
        status = SELECT;
      }
  	  ClearDrawScreen();
      // 後で差し替える　nakao
      DrawString( 100, 100, "TITLE", WHITE, GREY);
      //DrawGraph( 0, 0, "TITLE.bmp", false);
      ScreenFlip();
    } else if (status == SELECT){
      input.getKeyInput();
      if (input.buttonA()){
        shooting = new Shooting(1);
        status = SHOOTING;
      } else if (input.buttonB()){
        status = TITLE;
      }
  	  ClearDrawScreen();
      // 後で差し替える　nakao
      DrawString( 100, 100, "SELECT", WHITE, GREY);
      DrawString( 100, 200, "If push button A, game start.", WHITE, GREY);
      DrawString( 100, 300, "If push button B, back to title.", WHITE, GREY);
      ScreenFlip();
    } else if (status == SHOOTING){
   		input.getKeyInput();
      // todo treat dead client
      //while(true){
      //  int lostNetWork = GetLostNetWork();
      //}
      shooting->setInput(0, input.encode());
      shooting->action();
      
      //if (SHOOTING) shooting.action();
      //else if (TITLE) {
      //  drawTitle;
      //} else if (){

      //}
      

#ifdef _DEBUG_

		  // debug messages
		  //dxout << serverMessage << dxendl;

#endif // _DEBUG_

		  //string clientMessage = graresource.getMessages();
		  //server.send(clientMessage);
      vector<int> mess___ = graresource.getMessages();
		  decoder.draw( mess___);
		  graresource.clear();
	    int term;
	    term = GetNowCount()-fpsTimer;

		  if(16-term>0){
  			Sleep(16-term);
		  }

	    fpsTimer = GetNowCount();
      if (!shooting->isValid()){
        delete shooting;
        status = SELECT;
      }

    } else {
      assert( false && "solo main");
    }
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
#endif // nakao_SOLOPLAY_MODE

#ifdef SOLOPLAY_MODE
void soloplay_main(){
  //画像読み込み
  graresource.initialize();
  decoder.initialize();
  static const int BLACK = GetColor(0, 0, 0);
  static const int WHITE = GetColor(255, 255, 255);
  static const int playerNum = 4;
  Shooting shooting(playerNum);
  // 移動ルーチン
  int fpsTimer = GetNowCount();
  Input input;

  ClearDrawScreen();
  const static int titleGraph = LoadGraph( "../graphic/ShootingTitle.jpg");
  DrawGraph( 0, 0, titleGraph, false);
  ScreenFlip();
  Sleep( 3000);
  while( 1 ){
    input.getKeyInput();
    // todo treat dead client
    //while(true){
    //  int lostNetWork = GetLostNetWork();
    //}
    for(int i = 0; i < playerNum; ++i){
      shooting.setInput(i, input.encode());
    }
    shooting.action();

#ifdef _DEBUG_

    // debug messages
    //dxout << serverMessage << dxendl;

#endif // _DEBUG_

		decoder.draw(graresource.getMessages());
    graresource.clear();
    int term;
    term = GetNowCount()-fpsTimer;

    if(16-term>0){
      Sleep(16-term);
    }

    fpsTimer = GetNowCount();

		if (!shooting.isValid()) break;		
		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
#endif // SOLOPLAY_MODE

#ifdef NETWORK_SOLOPLAY_MODE
void network_soloplay_main(){
	//画像読み込み
  graresource.initialize();
	decoder.initialize();
	ServerConnection server(PORT);
	ClientConnection client(PORT, SERVER_IP);
	server.startListen();
  ClearDrawScreen();
  const static int titleGraph = LoadGraph( "../graphic/ShootingTitle.jpg");
  DrawGraph( 0, 0, titleGraph, false);
  ScreenFlip();

	if(!client.connect()){
		exit(1);
	}
	while(server.getClientNum() < CLIENT_NUM){
    ClearDrawScreen();
    DrawGraph( 0, 0, titleGraph, false);
		DrawFormatString(300, 500, WHITE, "access: %d", server.getClientNum());
    ScreenFlip();
		Sleep(10);
		server.acceptNewConnection();
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) exit(1) ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) exit(1);
	}
  Shooting *shooting= new Shooting(CLIENT_NUM);
  // 移動ルーチン
	int fpsTimer = GetNowCount();
	Input input;
	int playerNum = server.getClientNum();
  while( 1 ){

		//server.acceptNewConnection();
		//server.checkLostConnection();

		input.getKeyInput();
		client.send(input.encode());
		string serverMessage;
    // todo treat dead client
    //while(true){
    //  int lostNetWork = GetLostNetWork();
    //}
		for(int i = 0; i < server.getClientNum(); ++i){
      if(server.receive(i, serverMessage) >= 0){
        while(server.receive(i, serverMessage) >= 0);
        // receive succssessed
        shooting->setInput(i, serverMessage);
      }else{
        // receive failed
        shooting->clearInput(i);
      }
	  }
    shooting->action();

#ifdef _DEBUG_

		// debug messages
		dxout << serverMessage << dxendl;

#endif // _DEBUG_

    //string clientMessage = graresource.getMessages();
    //server.send(clientMessage);
		vector<int> clientMessage = graresource.getMessages();
		server.send(clientMessage);

		graresource.clear();
	  int term;
	  term = GetNowCount()-fpsTimer;

		if(16 - term > 0){
			vector<int> clientMessage;
			if(client.receive(clientMessage) >= 0){
				while(client.receive(clientMessage) >= 0);
				decoder.draw(clientMessage);
			}

			term = GetNowCount()-fpsTimer;


			if(16-term>0){
				Sleep(16-term);
			}
		}

	  fpsTimer = GetNowCount();

		if (!shooting->isValid()){
			delete shooting;
			shooting = new Shooting(CLIENT_NUM);
		}
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
	server.endListen();
}
#endif // NETWORK_SOLOPLAY_MODE

#ifdef SERVER_MODE
void server_main(){
  graresource.initialize();
  static const int BLACK = GetColor(0, 0, 0);
  static const int WHITE = GetColor(255, 255, 255);
	ServerConnection server(PORT);
	server.startListen();
	while(server.size() < CLIENT_NUM){
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
		DrawFormatString(60, 60, WHITE, "access: %d", server.size());
		ScreenFlip();
		Sleep(10);
		server.action();
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) exit(1) ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) exit(1);
	}
	server.endListen();
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
	DrawFormatString(60, 60, WHITE, "access: %d", server.size());
	DrawFormatString(60, 80, WHITE, "game start", server.size());
	ScreenFlip();
  Shooting shooting(CLIENT_NUM);
  // 移動ルーチン
	int fpsTimer = GetNowCount();
  while( 1 ){
		string serverMessage;
    // todo treat dead client
    //while(true){
    //  int lostNetWork = GetLostNetWork();
    //}

		for(int i = 0; i < server.size(); ++i){
      if(server.receive(i, serverMessage) >= 0){
        while(server.receive(i, serverMessage) >= 0);
        // receive succssessed
        shooting.setInput(i, serverMessage);
      }else{
        // receive failed
        shooting.clearInput(i);
      }
	  }
    shooting.action();

		// debug messages
		dxout << serverMessage << dxendl;

		vector<int> clientMessage = graresource.getMessages();

		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
		DrawFormatString(60, 60, WHITE, "access: %d", server.size());
		DrawFormatString(60, 80, WHITE, "game start", server.size());
		//DrawFormatString(60, 100, WHITE, clientMessage.c_str());
		ScreenFlip();

		server.send(clientMessage);
	  graresource.clear();
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(16-term>0){
			Sleep(16-term);
		}
	  fpsTimer = GetNowCount();

		if (!shooting.isValid()) break;
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
#endif // SERVER_MODE

#ifdef CLIENT_MODE
void client_main(){
  static Mode status = UNCONNECTED;
	ClientConnection client(PORT, SERVER_IP);
	Input input;
	decoder.initialize();

	while(!client.connect()){
	  ClearDrawScreen();
	  const static int titleGraph = LoadGraph( "../graphic/ShootingTitle.jpg");
	  DrawGraph( 0, 0, titleGraph, false);
	  DrawString( 300, 500, "Now connecting", WHITE);
		ScreenFlip();
		int lastTry = GetNowCount();
		while(GetNowCount() - lastTry < 1000){
			Sleep(20);

			// Windows 特有の面倒な処理をＤＸライブラリにやらせる
	    // -1 が返ってきたらループを抜ける
	    if( ProcessMessage() < 0 ) exit(0);
  
	    // もしＥＳＣキーが押されていたらループから抜ける
	    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) exit(0);
		}
	}
  status = CONNECTED;

  // 移動ルーチン
	int fpsTimer = GetNowCount();
  while( 1 ){
    input.getKeyInput();
	  client.send(input.encode());
	  vector<int> clientMessage;
	  if(client.receive(clientMessage) >= 0){
  		while(client.receive(clientMessage) >= 0);
		  decoder.draw(clientMessage);
	  }
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(8-term>0){
  		Sleep(8-term);
	  }
	  fpsTimer = GetNowCount();
  
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;
  
    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
#endif // CLIENT_MODE

// client_main は未テストです。以下の client_main_backup は消さないように！
#ifdef CLIENT_MODE
void client_main_backup(){
  static Mode status = UNCONNECTED;
	decoder.initialize();

	ClientConnection client(PORT, SERVER_IP);
  ClearDrawScreen();
  const static int titleGraph = LoadGraph( "../graphic/ShootingTitle.jpg");
  DrawGraph( 0, 0, titleGraph, false);
  DrawString( 300, 500, "Now connecting", WHITE);
  ScreenFlip();
	if(!client.connect()){
    ClearDrawScreen();
    DrawString( 200, 500, "Connect failed. Please set up server first.", WHITE);
    DrawString( 200, 550, "Shutdown.", WHITE);
    ScreenFlip();
    Sleep( 7000);
		exit(1);
	}
  status = CONNECTED;

  // 移動ルーチン
	int fpsTimer = GetNowCount();
	Input input;
  while( 1 ){
    input.getKeyInput();
	  client.send(input.encode());
	  vector<int> clientMessage;
	  if(client.receive(clientMessage) >= 0){
  		while(client.receive(clientMessage) >= 0);
		  decoder.draw(clientMessage);
	  }
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(8-term>0){
  		Sleep(8-term);
	  }
	  fpsTimer = GetNowCount();
  
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;
  
    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
#endif // CLIENT_MODE
