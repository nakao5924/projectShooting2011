#include "main.h"
#include "shooting.h"
#include "graphicResource.h"

#define SOLOPLAY_MODE
// #define SERVER_MODE
// #define CLIENT_MODE

void soloplay_main(){
  Shooting shooting;
  // 移動ルーチン
	int fpsTimer = GetNowCount();
  while( 1 ){
    shooting.action();
	  int term;
	  term = GetNowCount()-fpsTimer;
	  if(16-term>0){
			// 空関数。呼ぶ必要はない。
			//res.initdraw();
			res.draw();
		}
	  term = GetNowCount()-fpsTimer;
	  if(16-term>0){
			Sleep(16-term);
		}
	  fpsTimer = GetNowCount();
    // Windows 特有の面倒な処理をＤＸライブラリにやらせる
    // -1 が返ってきたらループを抜ける
    if( ProcessMessage() < 0 ) break ;

    // もしＥＳＣキーが押されていたらループから抜ける
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;
  }
}

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

#ifdef SOLOPLAY_MODE
	soloplay_main();
#endif // SOLOPLAY_MODE
#ifdef SERVER_MODE
	todo
#endif // SERVER_MODE
#ifdef CLIENT_MODE
	todo
#endif // CLIENT_MODE

  DxLib_End();				// ＤＸライブラリ使用の終了処理
  return 0;					// ソフトの終了
}
