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
private:
  vector<int> data;
  PictureTable pt;
public:
  ~GraphicResource();
  GraphicResource();
  void initialize();

  int getID(string objectname){return pt.getID(objectname);}
  /////////////////////////bigin/encode////////////////////////////////
  void drawgraph(const int x,const int y,int tableIdx,int animationIdx,bool transflag);
  void drawanimation(const int x,const int y, const int &graphicID, const int &animationIdx);
  void drawbox(int x1, int y1, int x2, int y2,int color,bool fillflag);
  void drawline(int x1, int y1, int x2, int y2,int color);
  void drawstring(int x,int y, string str, int color);
  void drawint(int x, int y, int num, int color);

  vector<int> getMessages();
  void clear();
//////////////////////////end/encode////////////////////////////////////
};


extern GraphicResource graresource;  // ÉäÉ\Å[ÉX
#endif