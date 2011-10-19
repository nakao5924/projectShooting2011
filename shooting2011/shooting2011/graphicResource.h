/**
 * graphicResource.h
 * @author neon
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include <string>
#include <map>
#include "decode.h"
using namespace std;

/**
 * GraphicResource
 * ゲーム中の画像のリソース管理
 */
class GraphicResource {
  // ファイル名をキーにして、mapで画像を呼び出すのに必要なidを持っておく
  map<string, int> graphics;
	stringstream ss;
public:
  GraphicResource();
  int get(const string &path);
  int get(const string &path, bool forceFlg);
  int load(const string &path);

	/////////////////////////bigin/encode////////////////////////////////
	void drawgraph(const int x,const int y,int graphic,bool transflag);
	void drawbox(int x1, int y1, int x2, int y2,int color,bool fillflag);
	void drawline(int x1, int y1, int x2, int y2,int color);
	template<class _Ty>void drawstring(int x,int y, _Ty str, int color){
		ss<<" <drawstring> "<<x<<" "<<y<<" "<<str<<" "<<color<<" </drawstring> ";
		/*
		stringstream ss_sub;
		ss_sub<<str;
		string s;
		ss_sub>>s;
		DrawString(x,y,s.c_str(),color);
		//*/
	}
	void initdraw();

	void draw();
//////////////////////////end/encode////////////////////////////////////
};


extern GraphicResource res;  // リソース
#endif