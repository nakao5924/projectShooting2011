#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include "main.h"
#include <string>
#include <map>

using namespace std;

class GraphicResource {
  map<string, int> graphics;
public:
  GraphicResource();
  int get(const string &path);
  int get(const string &path, bool forceFlg);
  int load(const string &path);
};

#endif