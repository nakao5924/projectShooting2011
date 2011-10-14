/**
 * graphicPattern.h
 * @author neon
 */

#ifndef __GRAPHICPATTERN_H__
#define __GRAPHICPATTERN_H__

#include "graphicResource.h"
#include <string>
#include <vector>

using namespace std;

struct AnimePart {
  int graphic; // 使用する画像
  int frame;   // 継続するフレーム
};

/**
 * GraphicPattern
 * アニメーションを管理するためのクラス
 */
class GraphicPattern {
  static GraphicResource res;  // リソース
  vector<AnimePart> animation; // アニメーション情報
  int current; // 現在表示する画像のインデックス(↑のvectorの)
  int frameCount; // 現在のパートにおける経過フレーム数
  bool repeatFlg; // アニメーションが終わった際に最初から繰り返し表示するか
                  // (falseの場合はAnimationの最後の画像を表示し続ければよい？)
public:
  GraphicPattern();
  GraphicPattern(const string &path);
  int loadAnimation(const string& path);
  void push_back(const string &imagePath, const int frame);
  void push_back(const int imageId, const int frame);
  void setRepeat(bool flg);
  void init();
  int getDrawImage();
  // test用のアニメーション作成関数
  void testFunc();
};
#endif