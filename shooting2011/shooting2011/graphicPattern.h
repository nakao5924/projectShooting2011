#ifndef __GRAPHICPATTERN_H__
#define __GRAPHICPATTERN_H__

#include "main.h"
#include "graphicResource.h"
#include <string>
#include <vector>

using namespace std;

/* アニメーション管理
 * @author neon
 * アニメーションを管理するためのクラス
 * アニメーションの情報を実際にクラスのインスタンスに入れるのが
 * 意外と面倒くさいので、その内外部ファイルから読み込めるようにするといいかも
 */
struct AnimePart {
  int graphic; // 使用する画像
  int frame;   // 継続するフレーム
};

class GraphicPattern {
  static GraphicResource res;  // リソース
  vector<AnimePart> animation; // アニメーション情報
  int framecount; // 現在のパートにおける経過フレーム数
public:
  GraphicPattern();
  int loadAnimation(const string& path);
  void draw();
};

#endif