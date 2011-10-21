/*
#include "main.h"
#include "shooting.h"
#include "server.h"
#include "client.h"
#include "msgdump.h"
#include "decode.h"
#include "graphicResource.h"

const int PORT = 12345;

const IPDATA LOCALHOST = {127, 0, 0, 1};
const IPDATA SAKURA = {192, 168, 0, 100};

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

	ServerConnection server(PORT);
	ClientConnection c1(PORT, LOCALHOST);
	ClientConnection c2(PORT, LOCALHOST);
	ClientConnection c3(PORT, LOCALHOST);
	ClientConnection c4(PORT, LOCALHOST);
	ClientConnection c5(PORT, LOCALHOST);

	string buf;

	server.startListen();

	c1.connect();
	Sleep(100);
	server.acceptNewConnection();
	dxout << c1.receive(buf) << dxendl;
	dxout << buf << dxendl;

	c2.connect();
	Sleep(100);
	server.acceptNewConnection();
	dxout << c2.receive(buf) << dxendl;
	dxout << buf << dxendl;

	c3.connect();
	Sleep(100);
	server.acceptNewConnection();
	dxout << c3.receive(buf) << dxendl;
	dxout << buf << dxendl;

	c4.connect();
	Sleep(100);
	server.acceptNewConnection();
	dxout << c4.receive(buf) << dxendl;
	dxout << buf << dxendl;

	c5.connect();
	Sleep(100);
	server.acceptNewConnection();
	server.endListen();
	dxout << c5.receive(buf) << dxendl;
	dxout << buf << dxendl;

	decoder.draw(graresource.getMessages());
	ScreenFlip();
	WaitKey();

  DxLib_End();				// �c�w���C�u�����g�p�̏I������
  return 0;					// �\�t�g�̏I��
}
*/