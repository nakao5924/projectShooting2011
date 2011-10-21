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
  static const int explosionID=graresource.getID("explosion");
  switch(mo->getStatus()){
  case INVALID:
    return;
  case VALID:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,graphicID, mo->getframeCount());
    return;
  case EXPLOSION:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,explosionID, mo->getframeCount());
    return;
  case REBIRTH:

    return;
  default:
    return;
  }



}
