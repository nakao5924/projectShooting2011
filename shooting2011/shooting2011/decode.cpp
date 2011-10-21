#include"decode.h"
#include"main.h"

void Decode::drawbox( const vector<int>& data, int& pos){
//  DrawBox(x1,y1,x2,y2,color,fillflag);
  int temp[6];
  for (int i=0; i<6; i++) temp[i] = data[pos++];
  DrawBox( temp[0], temp[1], temp[2], temp[3], temp[4], (bool)temp[5]);
}

void Decode::drawline( const vector<int>& data, int& pos){
//  DrawLine(x1,y1,x2,y2,color);
  int temp[5];
  for (int i=0; i<5; i++) temp[i] = data[pos++];
  DrawLine( temp[0], temp[1], temp[2], temp[3], temp[4]);
}

void Decode::drawstring( const vector<int>& data, int& pos){
//  DrawString(x,y,str.c_str(),color);
  int x, y, strNum;
  string str;
  int color;
  x = data[pos++];
  y = data[pos++];
  strNum = data[pos++];
  for (int i=0; i<strNum; i++){
    str.push_back(static_cast<char>(data[pos++]));
  }
  color = data[pos++];
  DrawString( x, y, str.c_str(), color);
}

void Decode::drawgraph( const vector<int>& data, int& pos){
//  DrawGraph(x,y,pt.decode(graphic),transflag);
  int temp[4];
  for (int i=0; i<4; i++) temp[i] = data[pos++];
  DrawGraph( temp[0], temp[1], pt.decode(temp[2]), (bool)temp[3]);
}

void Decode::drawint( const vector<int>& data, int& pos){
  int x, y, color, num;
  x = data.at(pos++);
  y = data[pos++];
  num = data[pos++];
  color = data[pos++];

  ostringstream ss;
  ss << num;

  DrawString( x, y, ss.str().c_str(), color);  
}
void Decode::draw( const vector<int>& data){
  ClearDrawScreen();

  static int pos = 0;
  TagCode tag;
  pos = 0;
  while( (tag = (TagCode)data[pos++]) != END){
    if (tag == DRAWBOX){ drawbox( data, pos);}
    else if (tag == DRAWLINE){ drawline( data, pos);}
    else if (tag == DRAWSTRING){ drawstring( data, pos);}
    else if (tag == DRAWINT){ drawint( data, pos);}
    else if (tag == DRAWGRAPH){ drawgraph( data, pos);}
    else assert(false && "decode: unknown tag");
  }

  ScreenFlip();
}
/*
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
*/
void Decode::initialize(){
  pt=PictureTable();
  pt.initialize();
}

Decode decoder;