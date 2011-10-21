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
  static const int explosionID=graresource.getID("Explosion");
  switch(mo->getStatus()){
  case INVALID:
    return;
  case VALID:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,mo->getframeCount(),graphicID);
    return;
  case EXPLOSION:
    graresource.drawanimation((int)mo->getHitRect().x,(int)mo->getHitRect().y,mo->getframeCount(),explosionID);
    return;
  case REBIRTH:

    return;
  default:
    return;
  }



}
