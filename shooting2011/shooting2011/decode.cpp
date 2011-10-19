#include"decode.h"
#include"main.h"
void Decode::drawbox(stringstream&ss){
	int x1,y1,x2,y2,color;
	bool fillflag;
	string format;
	if(ss>>x1>>y1>>x2>>y2>>color>>fillflag);
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
void Decode::draw(stringstream&ss){
	initdraw();
	string format;
	while(ss>>format){
		if(format=="<drawbox>"){drawbox(ss);ss>>format;}
		else if(format=="<drawgraph>"){drawgraph(ss);ss>>format;}
		else if(format=="<drawline>"){drawline(ss);ss>>format;}
		else if(format=="<drawstring>"){drawstring(ss);ss>>format;}
		else if(format=="<end>")break;
	}

  ScreenFlip();
}

void Decode::drawgraph(stringstream &ss){
	//ss<<" <drawgraph> "<<x<<" "<<y<<" "<<graphic<<" "<<transflag<<" <drawgraph> ";
	int x,y,graphic;
	bool transflag;
	ss>>x>>y>>graphic>>transflag;
	DrawGraph(x,y,graphic,transflag);
}