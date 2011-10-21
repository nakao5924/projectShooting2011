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
	void draw(stringstream&ss);
	void initdraw();
	void drawbox(stringstream&ss);
	void drawline(stringstream&ss);
	void drawstring(stringstream&ss);
	void drawgraph(stringstream&ss);
	void draw(const string&str);


};
extern Decode decoder;
#endif

