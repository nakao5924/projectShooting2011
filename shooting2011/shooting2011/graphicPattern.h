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
  int graphic; // �g�p����摜
  int frame;   // �p������t���[��
};

/**
 * GraphicPattern
 * �A�j���[�V�������Ǘ����邽�߂̃N���X
 */
class GraphicPattern {
  static GraphicResource res;  // ���\�[�X
  vector<AnimePart> animation; // �A�j���[�V�������
  int current; // ���ݕ\������摜�̃C���f�b�N�X(����vector��)
  int frameCount; // ���݂̃p�[�g�ɂ�����o�߃t���[����
  bool repeatFlg; // �A�j���[�V�������I������ۂɍŏ�����J��Ԃ��\�����邩
                  // (false�̏ꍇ��Animation�̍Ō�̉摜��\����������΂悢�H)
public:
  GraphicPattern();
  GraphicPattern(const string &path);
  int loadAnimation(const string& path);
  void push_back(const string &imagePath, const int frame);
  void push_back(const int imageId, const int frame);
  void setRepeat(bool flg);
  void init();
  int getDrawImage();
  // test�p�̃A�j���[�V�����쐬�֐�
  void testFunc();
};
#endif