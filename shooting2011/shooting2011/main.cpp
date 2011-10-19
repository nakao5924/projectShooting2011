#include "main.h"
#include "shooting.h"
#include "graphicResource.h"

#define SOLOPLAY_MODE
// #define SERVER_MODE
// #define CLIENT_MODE

void soloplay_main(){
  Shooting shooting;
  // �ړ����[�`��
	int fpsTimer = GetNowCount();
  while( 1 ){
    shooting.action();
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(16-term>0){
			// ��֐��B�ĂԕK�v�͂Ȃ��B
			//res.initdraw();
			res.draw();
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
	todo
#endif // SERVER_MODE
#ifdef CLIENT_MODE
	todo
#endif // CLIENT_MODE

  DxLib_End();				// �c�w���C�u�����g�p�̏I������
  return 0;					// �\�t�g�̏I��
}
