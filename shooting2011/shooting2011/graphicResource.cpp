#include "main.h"
#include "graphicResource.h"

GraphicResource graresource=GraphicResource();  // リソース

// コンストラクタ
GraphicResource::GraphicResource() {}
  
void GraphicResource::initialize(){
  data.resize(0);
  pt.initialize();
}

GraphicResource::~GraphicResource(){}

//encode start
void GraphicResource::drawgraph(const int x,const int y,int graphic,bool transflag){
  data.push_back( DRAWGRAPH);
  data.push_back( x);
  data.push_back( y);
  data.push_back( graphic);
  data.push_back( (int)transflag);
  //DrawGraph(x,y,graphic,transflag);
}
void GraphicResource::drawbox(int x1, int y1, int x2, int y2, int color, bool fillflag){
  data.push_back( DRAWBOX);
  data.push_back( x1);
  data.push_back( y1);
  data.push_back( x2);
  data.push_back( y2);
  data.push_back( color);
  data.push_back( (int)fillflag);
  //DrawBox(x1,y1,x2,y2,color,fillflag);
  
}
void GraphicResource::drawline(int x1, int y1, int x2, int y2, int color){
  data.push_back( DRAWLINE);
  data.push_back( x1);
  data.push_back( y1);
  data.push_back( x2);
  data.push_back( y2);
  data.push_back( color);
  //DrawLine(x1,y1,x2,y2,color);
}

void GraphicResource::drawstring(int x,int y, string str, int color){
  data.push_back( DRAWSTRING);
  data.push_back( x);
  data.push_back( y);
  data.push_back( (int)str.size());
  for (int i=0; i<str.size(); i++){
    data.push_back( (int)str[i]);
  }
  data.push_back( color);
}

void GraphicResource::drawint(int x,int y, int num, int color){
  data.push_back( DRAWINT);
  data.push_back( x);
  data.push_back( y);
  data.push_back( num);
  data.push_back( color);
}

vector<int> GraphicResource::getMessages(){
  data.push_back( END);
  return data;
  data.pop_back();
}

void GraphicResource::clear(){
  data.resize(0);
}

void GraphicResource::drawanimation(const int x,const int y,const int framecount,const int&graphicID){
  this->drawgraph(x-pt.gethalfsize_x(graphicID),y-pt.gethalfsize_y(graphicID),pt.getanimation(graphicID,framecount),true);
}

/*
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
*/