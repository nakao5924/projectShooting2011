#include "main.h"
#include "graphicResource.h"


GraphicResource graresource=GraphicResource();  // リソース

// コンストラクタ
GraphicResource::GraphicResource() {
}
void GraphicResource::initialize(){
	pt.initialize();
}
GraphicResource::~GraphicResource(){}







//////////////////begin/encode//////////////////////////////////////
void GraphicResource::drawgraph(const int x,const int y,int graphic,bool transflag){
	ss<<" "<<DRAWGRAPH<<" "<<x<<" "<<y<<" "<<graphic<<" "<<transflag<<" "<<DRAWGRAPH<<" ";
	//DrawGraph(x,y,graphic,transflag);
}
void GraphicResource::drawbox(int x1, int y1, int x2, int y2, int color, bool fillflag){
	ss<<" "<<DRAWBOX<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<color<<" "<<fillflag<<" "<<DRAWBOX<<" ";
	//DrawBox(x1,y1,x2,y2,color,fillflag);
	
}
void GraphicResource::drawline(int x1, int y1, int x2, int y2, int color){
	ss<<" "<<DRAWLINE<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<color<<" "<<DRAWLINE<<" ";
	//DrawLine(x1,y1,x2,y2,color);
}

string GraphicResource::getMessages(){
	ss << " "<<END<<" ";
	return ss.str();
}

void GraphicResource::clear(){
	static const string emptystring;
	ss.clear(stringstream::goodbit);
	ss.str(emptystring);
}

void GraphicResource::drawanimation(const int x,const int y,const int framecount,const int&graphicID){
	this->drawgraph(x-pt.gethalfsize_x(graphicID),y-pt.gethalfsize_y(graphicID),pt.getanimation(graphicID,framecount),true);
}
















////////////////////end/encode///////////////////////////////////