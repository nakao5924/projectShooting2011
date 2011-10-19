#include "main.h"
#include "graphicPattern.h"

//GraphicResource GraphicPattern::res;

GraphicPattern::GraphicPattern() {
  current = 0;
  frameCount = 0;
  repeatFlg = false;
};

// Animation記述ファイルを読み込むとデータに直したいけど未実装
GraphicPattern::GraphicPattern(const string &path) {
  current = 0;
  frameCount = 0;
  repeatFlg = false;
};

// 描画する座標を持っているのがMovingObjectなのでとりあえず描画すべき画像を返す
int GraphicPattern::getDrawImage() {
  frameCount++;
  if (!repeatFlg && current == animation.size()-1) {
    return animation[current].graphic;
  }
  if (animation[current].frame < frameCount) {
    frameCount = 0;
    current = (current+1) % animation.size();
  }
  return animation[current].graphic;
};

// Animationの末尾に画像を足す　削除関数なんてものはない
void GraphicPattern::push_back(const string &imagePath, const int frame) {
  AnimePart part;
  part.graphic = res.get(imagePath, true);
  part.frame = frame;
  animation.push_back(part);
};

void GraphicPattern::push_back(const int imageId, const int frame) {
  AnimePart part;
  part.graphic = imageId;
  part.frame = frame;
  animation.push_back(part);
};

// Animationをリピートさせるフラグの設定
void GraphicPattern::setRepeat(bool flg) {
  repeatFlg = flg;
};

void GraphicPattern::init() {
  current = 0;
  frameCount = 0;
};

// For Debug
void GraphicPattern::testFunc() {
  setRepeat(true);
  push_back("../graphic/Ball.png", 20);
  push_back("../graphic/Sikaku.png", 20);
};


