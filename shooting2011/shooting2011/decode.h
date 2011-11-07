#ifndef __DECODE_H__
#define __DECODE_H__

#include <sstream>
#include "pictureTable.h"
#include "musicTable.h"
using namespace std;
class Decode{
	PictureTable pt;
	MusicTable mt;
public:
	Decode(){}
	~Decode(){}
	void initialize();
  void drawbox( const vector<int>& data, int& pos);
  void drawline( const vector<int>& data, int& pos);
  void drawstring( const vector<int>& data, int& pos);
  void drawgraph( const vector<int>& data, int& pos);
  void drawint( const vector<int>& data, int& pos);
  void draw( const vector<int>& data);
	void playmusic(const vector<int>& data, int& pos);
	void playloopmusic(const vector<int>& data, int& pos);
	void stopmusic(const vector<int>& data, int& pos);
	void stopallmusic(const vector<int>& data, int& pos);
};
extern Decode decoder;
#endif

