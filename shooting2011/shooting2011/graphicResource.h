/**
 * graphicResource.h
 * @author upa
 * @replace nakao
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include "pictureTable.h"
#include "main.h"

class GraphicResource {
//private:
//  int *data;
	stringstream ss;
	PictureTable pt;
public:
	~GraphicResource();
  GraphicResource();
  void initialize();

	int getID(string objectname){return pt.getID(objectname);}
	/////////////////////////bigin/encode////////////////////////////////
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