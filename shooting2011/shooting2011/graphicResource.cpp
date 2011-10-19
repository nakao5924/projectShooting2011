#include "main.h"
#include "graphicResource.h"


GraphicResource res=GraphicResource();  // リソース

// コンストラクタ
GraphicResource::GraphicResource() {
};

// mapから画像のidを取ってくる forceFlgがtrueなら存在しなければロードも行う
int GraphicResource::get(const string &path) {
  return this->get(path, false);
};

int GraphicResource::get(const string &path, bool forceFlg) {
  int id = this->graphics[path];
  return !id ? (forceFlg ? this->load(path) : -1) : id;
};

int GraphicResource::load(const string &path) {
  int id = LoadGraph(path.c_str());
  pair<string, int> val;
  val.first = path;
  val.second = id;
  this->graphics.insert(val);
  return id;
};





//////////////////begin/encode//////////////////////////////////////

void GraphicResource::drawbox(int x1, int y1, int x2, int y2, int color, bool fillflag){
	ss<<" <drawbox> "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<color<<" "<<fillflag<<" </drawbox> ";
//	DrawBox(x1,y1,x2,y2,color,fillflag);
	
}
void GraphicResource::drawline(int x1, int y1, int x2, int y2, int color){
	ss<<" <drawline> "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<color<<" </drawline> ";
//	DrawLine(x1,y1,x2,y2,color);
}
void GraphicResource::initdraw(){
	//ClearDrawScreen();

	ss.str("");
}
void GraphicResource::draw(){
	ss<<" <end> ";
	Decode::draw(ss);
//  ScreenFlip();

}
























////////////////////end/encode///////////////////////////////////