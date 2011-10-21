#include"decode.h"
#include"main.h"
void Decode::drawbox(stringstream&ss){
	int x1,y1,x2,y2,color;
	bool fillflag;
	string format;
	ss>>x1>>y1>>x2>>y2>>color>>fillflag;
	DrawBox(x1,y1,x2,y2,color,fillflag);
}
void Decode::drawline(stringstream&ss){
	int x1, y1, x2, y2, color;
	ss>>x1>>y1>>x2>>y2>>color;
	DrawLine(x1,y1,x2,y2,color);
}
void Decode::drawstring(stringstream&ss){
	int x,y,color;
	string str;
	ss>>x>>y>>str>>color;
	DrawString(x,y,str.c_str(),color);
}
void Decode::initdraw(){
	ClearDrawScreen();
}
void Decode::draw(const string &str){
	stringstream ss(str);
	draw(ss);
}
void Decode::drawgraph(stringstream &ss){
	int x,y,graphic;
	bool transflag;
	ss>>x>>y>>graphic>>transflag;
	DrawGraph(x,y,pt.decode(graphic),transflag);
}
void Decode::draw(stringstream&ss){
	initdraw();
	int format;
	while(ss>>format){
		if(format==DRAWBOX){drawbox(ss);ss>>format;}
		else if(format==DRAWGRAPH){drawgraph(ss);ss>>format;}
		else if(format==DRAWLINE){drawline(ss);ss>>format;}
		else if(format==DRAWSTRING){drawstring(ss);ss>>format;}
		else if(format==END)break;
	}

  ScreenFlip();
}
void Decode::initialize(){
	pt=PictureTable();
	pt.initialize();
}
Decode decoder;