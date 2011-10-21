#ifndef __DECODE_H__
#define __DECODE_H__

#include <sstream>
#include "pictureTable.h"
using namespace std;
class Decode{
	PictureTable pt;
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
};
extern Decode decoder;
#endif

