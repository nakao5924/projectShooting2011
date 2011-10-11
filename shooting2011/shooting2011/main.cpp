#include "main.h"
#include "shooting.h"

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

  Shooting shooting;
  // �ړ����[�`��
  while( 1 ){
    shooting.action();
    // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
    // -1 ���Ԃ��Ă����烋�[�v�𔲂���
    if( ProcessMessage() < 0 ) break ;

    // �����d�r�b�L�[��������Ă����烋�[�v���甲����
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }

  DxLib_End();				// �c�w���C�u�����g�p�̏I������
  return 0;					// �\�t�g�̏I��
}

