/**
 * graphicResource.h
 * @author upa
 * @replace nakao
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include "pictureTable.h"
#include "musicTable.h"
#include "main.h"

class GraphicResource {
private:
  vector<int> data;
	PictureTable pt;
	MusicTable mt;
public:
	~GraphicResource();
  GraphicResource();
  void initialize();

	const int get_graphic_id(const string objectname){return pt.get_graphic_id(objectname);}
  const int get_sound_id(const string objectname){return mt.get_sound_id(objectname);}
	/////////////////////////bigin/encode////////////////////////////////
	void playsound(const int id);
	void playloopsound(const int id);
	void playloopsound(const string filename){playloopsound(get_sound_id(filename));}
	void stopallsound();
	void stopsound(const int id);

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