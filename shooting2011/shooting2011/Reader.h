//*
#ifndef __READRE_H__
#define __READRE_H__
#include<fstream>
#include<sstream>
#include <deque>
#include <string>
#include <map>
#include <time.h>
using namespace std;
#include"stageData.h"
#include"movePattern.h"
#include"firePattern.h"
#include"patternComposer.h"
#include"stage.h"
class Scene;
static string format;
static stringstream ss; 
static map<string,string> list; 


class Reader{
private:
  Reader();
  static EnemyData* get_enemy_data(){

    int start_time;
    double x,y;
    if(ss>>start_time>>x>>y>>format){
      MovePattern *mp=making_object<MovePattern>(new PatternComposer<MovePattern>());
      FirePattern *fp=making_object<FirePattern>(new PatternComposer<FirePattern>());
      GraphicPattern *gp=new GraphicPattern("enemy1up64");
      return(new EnemyData(start_time,x,y,mp,fp,gp));
    }
    return NULL;
  }

  template<class _Ty>
  static PatternComposer<_Ty>* making_object(PatternComposer<_Ty> *pc){
    _Ty *p=making_basic_object<_Ty>();
    if(p==NULL)
      return(pc);
    int limit_time;
    if(ss>>limit_time>>format)return(making_object<_Ty>(pc->add(limit_time,p)));
    return NULL;
  }
  template<class _Ty>
  static _Ty* making_basic_object();
  
  
  static string addnext(string&str){
    map<string,string>::iterator it=list.find(str);
    if(it != list.end()){
      stringstream ss(it->second);
      string str_sub;
      string str_ans;
      while(ss>>str_sub){
        str_ans+=addnext(str_sub);
      }
      return(str_ans);
    }else{
      return(str+" ");
    }
  }
  

public:
  static SceneNormal* readEnemyData(const string filename);
    
};


#endif


//*/