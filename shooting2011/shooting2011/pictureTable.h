#ifndef __PICTURE_READER_H__
#define __PICTURE_READER_H__
#include"Dxlib.h"
#include <map>
#include <string>
#include <deque>
#include "main.h"
using namespace std;
class PictureTable{
  //すべての画像を読み込んでそのidを管理する。

  map<int,deque<int>> decode_table;
  map<string,int> graphic_encode_table;
  map<int,pair<int, int>>half_size_table;//sizeの半分の大きさが格納されている。
  void load_all_graphics(string str);
public:
  ~PictureTable(){InitGraph();}
  PictureTable(){}
  int getID(string str);
  void initialize(){load_all_graphics("../graphic/");}
  int getanimation(int tableIdx,int animIdx);
  int gethalfsize_x(int graphicID){return half_size_table[graphicID].first;}
  int gethalfsize_y(int graphicID){return half_size_table[graphicID].second;}
  int decode(int in){return decode_table[in][0];}
  int encode(string str){return graphic_encode_table[str];}
};


#endif







