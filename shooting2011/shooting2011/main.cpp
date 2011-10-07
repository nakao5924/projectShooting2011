#include "main.h"
#include "shooting.h"

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

  Shooting shooting;
  // 移動ルーチン
  while( 1 ){
    shooting.action();
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }

  DxLib_End();				// ＤＸライブラリ使用の終了処理
  return 0;					// ソフトの終了
}

