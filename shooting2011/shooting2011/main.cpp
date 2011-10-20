#include "main.h"
#include "shooting.h"
#include "graphicResource.h"
#include "server.h"
#include "client.h"
#include "msgdump.h"

#define SOLOPLAY_MODE
// #define SERVER_MODE
// #define CLIENT_MODE

const int PORT = 12345;
// SAKURA
// const IPDATA SERVER_IP = {192, 168, 0, 100};
// LOCALHOST
const IPDATA SERVER_IP = {127, 0, 0, 1};

const int CLIENT_NUM = 1;

void soloplay_main();
void server_main();
void client_main();

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

#ifdef SOLOPLAY_MODE
	soloplay_main();
#endif // SOLOPLAY_MODE
#ifdef SERVER_MODE
	server_main();
#endif // SERVER_MODE
#ifdef CLIENT_MODE
	client_main();
#endif // CLIENT_MODE

  DxLib_End();				// �c�w���C�u�����g�p�̏I������
  return 0;					// �\�t�g�̏I��
}

void soloplay_main(){
	static const int BLACK = GetColor(0, 0, 0);
  static const int WHITE = GetColor(255, 255, 255);
	ServerConnection server(PORT);
	ClientConnection client(PORT, SERVER_IP);
	server.startListen();
	client.connect();
	while(server.size() < CLIENT_NUM){
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
		DrawFormatString(60, 60, WHITE, "access: %d", server.size());
		ScreenFlip();
		Sleep(10);
		server.action();
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) exit(1) ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) exit(1);
	}
	server.endListen();
  Shooting shooting(CLIENT_NUM);
  // �ړ����[�`��
	int fpsTimer = GetNowCount();
	Input input;
  while( 1 ){
		input.getKeyInput();
		client.send(input.encode());
		string serverMessage;
    /* // todo treat dead client
    while(true){
      int lostNetWork = GetLostNetWork();
    }
    */
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

		string clientMessage = res.getMessages();

		server.send(clientMessage);

		res.clear();
	  int term;
	  term = GetNowCount()-fpsTimer;

		if(16 - term > 0){
			string clientMessage;
			if(client.receive(clientMessage) >= 0){
				while(client.receive(clientMessage) >= 0);
				Decode::draw(clientMessage);
			}

			term = GetNowCount()-fpsTimer;

			// ��֐��B�ĂԕK�v�͂Ȃ��B
			//res.initdraw();
			if(16-term>0){
				Sleep(16-term);
			}
		}

	  fpsTimer = GetNowCount();
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) break ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}

void server_main(){
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
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) exit(1) ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) exit(1);
	}
	server.endListen();
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
	DrawFormatString(60, 60, WHITE, "access: %d", server.size());
	DrawFormatString(60, 80, WHITE, "game start", server.size());
	ScreenFlip();
  Shooting shooting(CLIENT_NUM);
  // �ړ����[�`��
	int fpsTimer = GetNowCount();
  while( 1 ){
		string serverMessage;
    /* // todo treat dead client
    while(true){
      int lostNetWork = GetLostNetWork();
    }
    */
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

		string clientMessage = res.getMessages();

		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
		DrawFormatString(60, 60, WHITE, "access: %d", server.size());
		DrawFormatString(60, 80, WHITE, "game start", server.size());
		//DrawFormatString(60, 100, WHITE, clientMessage.c_str());
		ScreenFlip();

		server.send(clientMessage);
	  res.clear();
	  int term;
	  term = GetNowCount()-fpsTimer;
		// ��֐��B�ĂԕK�v�͂Ȃ��B
		//res.initdraw();
	  if(16-term>0){
			Sleep(16-term);
		}
	  fpsTimer = GetNowCount();
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) break ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}

void client_main(){
	ClientConnection client(PORT, SERVER_IP);
	client.connect();

  // �ړ����[�`��
	int fpsTimer = GetNowCount();
	Input input;
  while( 1 ){
		input.getKeyInput();
		client.send(input.encode());
		string clientMessage;
		if(client.receive(clientMessage) >= 0){
			while(client.receive(clientMessage) >= 0);
			Decode::draw(clientMessage);
		}
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(8-term>0){
			Sleep(8-term);
		}
	  fpsTimer = GetNowCount();
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) break ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}
