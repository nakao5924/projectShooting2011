#include "graphicResource.h"

// �R���X�g���N�^
GraphicResource::GraphicResource() {
};

// map����摜��id������Ă��� forceFlg��true�Ȃ瑶�݂��Ȃ���΃��[�h���s��
int GraphicResource::get(const string &path) {
  return this->get(path, false);
};

int GraphicResource::get(const string &path, bool forceFlg) {
  int id = this->graphics[path];
  return !!id ? (forceFlg ? -1 : this->load(path)) : id;
};

int GraphicResource::load(const string &path) {
  int id = LoadGraph(path.c_str());
  pair<string, int> val;
  val.first = path;
  val.second = id;
  this->graphics.insert(val);
  return id;
};