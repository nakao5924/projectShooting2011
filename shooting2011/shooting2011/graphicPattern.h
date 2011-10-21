/**
 * graphicPattern.h
 * @author upa
 */

#ifndef __GRAPHICPATTERN_H__
#define __GRAPHICPATTERN_H__

#include "movingObject.h"
#include "graphicResource.h"
#include <string>
#include <deque>
#include "main.h"
class MovingObject;

using namespace std;

class GraphicPattern:public MovingObject{
  int graphicID;
public:
  void action(MovingObject*);
  GraphicPattern();
  GraphicPattern(int ID);
  GraphicPattern(string str);
  ~GraphicPattern(){}
};

#endif