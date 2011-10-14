/**
 * graphicResource.h
 * @author neon
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include <string>
#include <map>

using namespace std;

/**
 * GraphicResource
 * �Q�[�����̉摜�̃��\�[�X�Ǘ�
 */
class GraphicResource {
  // �t�@�C�������L�[�ɂ��āAmap�ŉ摜���Ăяo���̂ɕK�v��id�������Ă���
  map<string, int> graphics; 
public:
  GraphicResource();
  int get(const string &path);
  int get(const string &path, bool forceFlg);
  int load(const string &path);
};

#endif