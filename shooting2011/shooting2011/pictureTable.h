#ifndef __PICTURE_TABLE_H__
#define __PICTURE_TABLE_H__
#include"Dxlib.h"
#include <map>
#include <string>
#include <deque>
#include "main.h"
using namespace std;
class PictureTable{
	//���ׂẲ摜��ǂݍ���ł���id���Ǘ�����B

  map<int,deque<int>> decode_table;
	map<string,int> graphic_encode_table;
	map<int,pair<int,int>>half_size_table;//size�̔����̑傫�����i�[����Ă���B
	void load_all_graphics(string str);
public:
  ~PictureTable(){InitGraph();};
  PictureTable(){};
	int get_graphic_id(string str);
	void initialize(){load_all_graphics("../graphic/");}
  int getanimation(int tableIdx,int animIdx);
  int gethalfsize_x(int graphicID){return half_size_table[graphicID].first;};
  int gethalfsize_y(int graphicID){return half_size_table[graphicID].second;};
  int decode(int tableIdx, int animationIdx);
  int encode(string str);
};


#endif







