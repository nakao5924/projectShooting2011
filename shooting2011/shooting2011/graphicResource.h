/**
 * graphicResource.h
 * @author neon
 */

#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__

#include <string>
#include <map>

using namespace std;

/**
 * GraphicResource
 * ゲーム中の画像のリソース管理
 */
class GraphicResource {
  // ファイル名をキーにして、mapで画像を呼び出すのに必要なidを持っておく
  map<string, int> graphics; 
public:
  GraphicResource();
  int get(const string &path);
  int get(const string &path, bool forceFlg);
  int load(const string &path);
};

#endif