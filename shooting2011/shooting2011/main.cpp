#include "main.h"
#include "shooting.h"
#include "graphicResource.h"
#include "server.h"
#include "client.h"

#define SOLOPLAY_MODE
// #define SERVER_MODE
// #define CLIENT_MODE

const int PORT = 12345;
const IPDATA SERVER_IP = {192, 168, 0, 100};

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
	ServerConnection server(PORT);
	ClientConnection client(PORT, SERVER_IP);
	server.startListen();
	client.connect();
	while(server.size() < 1){
		Sleep(10);
		server.action();
	}
	server.endListen();
  Shooting shooting;
  // �ړ����[�`��
	int fpsTimer = GetNowCount();
	Input input;
  while( 1 ){
    shooting.action();
		server.send(res.getMessages());
		res.clear();
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(16-term>0){
			// ��֐��B�ĂԕK�v�͂Ȃ��B
			//res.initdraw();
			input.getKeyInput();
			client.send(input.encode());
			vector<string> serverMessages;
			string serverMessage;
			for(int i = 0; i < server.size(); ++i){
				server.receive(0, serverMessage);
				serverMessages.push_back(serverMessage);
			}
			shooting.setInput(serverMessages);
			string clientMessage;
			if(client.receive(clientMessage) >= 0){
				while(client.receive(clientMessage) >= 0);
				Decode::draw(clientMessage);
			}
		}
	  term = GetNowCount()-fpsTimer;
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

void server_main(){
	// todo
}
void client_main(){
	// todo
}
