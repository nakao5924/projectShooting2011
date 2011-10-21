/**
 * graphicResource.h
 * @author upa
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include <string>
#include <map>
#include "pictureTable.h"
#include "main.h"
using namespace std;

class GraphicResource {
	stringstream ss;
	PictureTable pt;
public:
	~GraphicResource();
  GraphicResource();
  void initialize();

	/////////////////////////bigin/encode////////////////////////////////
	int getID(string objectname){return pt.getID(objectname);}
	void drawgraph(const int x,const int y,int graphic,bool transflag);
	void drawanimation(const int x,const int y,const int framecount,const int&graphicID);
	void drawbox(int x1, int y1, int x2, int y2,int color,bool fillflag);
	void drawline(int x1, int y1, int x2, int y2,int color);
	template<class _Ty>void drawstring(int x,int y, _Ty str, int color){
		ss<<" "<<DRAWSTRING<<" "<<x<<" "<<y<<" "<<str<<" "<<color<<" "<<DRAWSTRING<<" ";
	}

	string getMessages();
	void clear();
//////////////////////////end/encode////////////////////////////////////
};


extern GraphicResource graresource;  // ƒŠƒ\[ƒX
#endif