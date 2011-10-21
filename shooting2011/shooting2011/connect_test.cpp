/*
#include "main.h"
#include <cassert>
#include "shooting.h"
#include "server.h"
#include "client.h"
#include "msgdump.h"
using namespace std;
//void dumpDummyPipe();

// WinMain�֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, int nCmdShow )
{
  // ��ʃ��[�h�̐ݒ�
  ChangeWindowMode(true);
  SetGraphMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16 ) ;

  // �c�w���C�u��������������
  if( DxLib_Init() == -1 ) return -1;

  // �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
  SetDrawScreen( DX_SCREEN_BACK );

	string buf;

	IPDATA ip = {127, 0, 0, 1};
	/ *
	Connection c1(0), c2(0);

	c1.send("c1: hello, c2.");
	c2.receive(buf);

	c2.send("c2: hello, c1!!");
	c1.receive(buf);

	c1.send("c1: test message1");
	c1.send("c1: test message2");
	c2.send("c2: test message1");
	c2.send("c2: test message2");

	c1.receive(buf);
	c1.receive(buf);

	c2.receive(buf);
	c2.receive(buf);
	* /
	
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������
  return 0;					// �\�t�g�̏I��
}

*/