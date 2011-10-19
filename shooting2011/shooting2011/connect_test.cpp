/*
#include "main.h"
#include <cassert>
#include "shooting.h"
#include "server.h"
#include "client.h"
#include "msgdump.h"
using namespace std;
//void dumpDummyPipe();

// WinMain関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, int nCmdShow )
{
  // 画面モードの設定
  ChangeWindowMode(true);
  SetGraphMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16 ) ;

  // ＤＸライブラリ初期化処理
  if( DxLib_Init() == -1 ) return -1;

  // グラフィックの描画先を裏画面にセット
  SetDrawScreen( DX_SCREEN_BACK );

	string buf;

	IPDATA ip = {192, 168, 0, 100};
	ServerConnection server(12345);
	ClientConnection client(12345, ip);

	server.startListen();

	bool connect = client.connect();
	assert(connect);

	server.action();

	server.endListen();
	assert(server.size() == 1);

	dxout << server.send(0, "server: hello, client!!") << dxendl;

	dxout << client.receive(buf) << dxendl;
	dxout << buf << dxendl;

	dxout << client.send("client: hello, server!!") << dxendl;

	dxout << server.receive(0, buf) << dxendl;
	dxout << buf << dxendl;

	dxout << client.receive(buf) << dxendl;
	dxout << buf << dxendl;
	dxout << server.receive(0, buf) << dxendl;
	dxout << buf << dxendl;

	dxout << server.send(0, "server: test message1") << dxendl;
	dxout << server.send(0, "server: test message2") << dxendl;

	dxout << client.receive(buf) << dxendl;
	dxout << buf << dxendl;
	dxout << client.receive(buf) << dxendl;
	dxout << buf << dxendl;

	dxout << client.send("client: test message1") << dxendl;
	dxout << client.send("client: test message2") << dxendl;
	dxout << server.receive(0, buf) << dxendl;
	dxout << buf << dxendl;
	dxout << server.receive(0, buf) << dxendl;
	dxout << buf << dxendl;

	ScreenFlip();
	WaitKey();

	DxLib_End();				// ＤＸライブラリ使用の終了処理
  return 0;					// ソフトの終了
}

*/