#include "graphicPattern.h"
#include "graphicResource.h"


GraphicPattern::GraphicPattern(string str){
	graphicID=graresource.getID(str);
}
GraphicPattern::GraphicPattern(int _graphicID){
	graphicID=_graphicID;
}
GraphicPattern::GraphicPattern(){
}
void GraphicPattern::action(MovingObject* mo){
	static const int interval=20;
  static const int explosionID=graresource.getID("explosion");
	switch(mo->getStatus()){
	case INVALID:
		return;
	case VALID:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,graphicID, mo->getframeCount());
		return;
	case EXPLOSION:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,explosionID, (int)mo->getframeCount()/3);
		return;
	case REBIRTH:
    if( mo->getframeCount()%interval>interval/2)graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,graphicID, mo->getframeCount());

		return;
	default:
		return;
	}



}
