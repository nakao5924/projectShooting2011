#ifndef __GRAPHICPATTERN_H__
#define __GRAPHICPATTERN_H__

#include "main.h"
#include "graphicResource.h"
#include <string>
#include <vector>

using namespace std;

/* �A�j���[�V�����Ǘ�
 * @author neon
 * �A�j���[�V�������Ǘ����邽�߂̃N���X
 * �A�j���[�V�����̏������ۂɃN���X�̃C���X�^���X�ɓ����̂�
 * �ӊO�Ɩʓ|�������̂ŁA���̓��O���t�@�C������ǂݍ��߂�悤�ɂ���Ƃ�������
 */
struct AnimePart {
  int graphic; // �g�p����摜
  int frame;   // �p������t���[��
};

class GraphicPattern {
  static GraphicResource res;  // ���\�[�X
  vector<AnimePart> animation; // �A�j���[�V�������
  int framecount; // ���݂̃p�[�g�ɂ�����o�߃t���[����
public:
  GraphicPattern();
  int loadAnimation(const string& path);
  void draw();
};

#endif