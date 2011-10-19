#include "main.h"
#include "graphicPattern.h"

//GraphicResource GraphicPattern::res;

GraphicPattern::GraphicPattern() {
  current = 0;
  frameCount = 0;
  repeatFlg = false;
};

// Animation�L�q�t�@�C����ǂݍ��ނƃf�[�^�ɒ����������ǖ�����
GraphicPattern::GraphicPattern(const string &path) {
  current = 0;
  frameCount = 0;
  repeatFlg = false;
};

// �`�悷����W�������Ă���̂�MovingObject�Ȃ̂łƂ肠�����`�悷�ׂ��摜��Ԃ�
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

// Animation�̖����ɉ摜�𑫂��@�폜�֐��Ȃ�Ă��̂͂Ȃ�
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

// Animation�����s�[�g������t���O�̐ݒ�
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


