#ifndef __MUSIC_TABLE_H__
#define __MUSIC_TABLE_H__
#include"Dxlib.h"
#include <map>
#include <string>
#include <deque>
#include "main.h"
using namespace std;
class MusicTable{
	//‚·‚×‚Ä‚Ì‰æ‘œ‚ğ“Ç‚İ‚ñ‚Å‚»‚Ìid‚ğŠÇ—‚·‚éB

  map<int,int> decode_table;
	map<string,int> encode_table;
	void load_all_musics(string str);
public:
  ~MusicTable(){InitGraph();};
  MusicTable(){};
	int get_sound_id(string str);
	void initialize(){load_all_musics("../music/");}
  int decode(int music_index);
  int encode(string str);
};


#endif







