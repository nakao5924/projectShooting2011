#ifndef __TAG_H__
#define __TAG_H__

#include<string>
#include<deque>
#include<sstream>
using namespace std;
class tag{
public:
  static const string make_tag(string tagname,string &str){
    return" <"+tagname+"> "+str+" </"+tagname+"> ";
  }
  static const deque<string> pop_all_tag(string tagname,string &str){
    deque<string> re;
    stringstream ss(str);
    string tag;
    string str_re;
    while(ss>>tag){
      if(tag=="<"+tagname+">"){
        string str_sub;
        string getter;
        while(ss>>getter){
          if(getter=="</"+tagname+">"){
            break;
          }
          str_sub+=getter+" ";
        }
        re.push_back(str_sub);
      }else{
        str_re+=tag+" ";
      }
    }
    str=str_re;
  }

  static const string pop_tag(string tagname,stringstream &ss){
    string tag;
    string str_re;
    while(ss>>tag){
      if(tag=="<"+tagname+">"){
        string str_sub;
        string getter;
        while(ss>>getter){
          if(getter=="</"+tagname+">"){
            break;
          }
          str_sub+=getter+" ";
        }
        return str_sub;
      }
    }
    return "";
  }
  static const string test_func(){
    string s="data";
  
    s=make_tag("hoge",s);
    s=make_tag("foo",s);
    s=s+s+s;
    s=make_tag("piyo",s);
    stringstream ss(s);
    string str2=pop_tag("hoge",ss);
    str2=pop_tag("hoge",ss);
    str2=pop_tag("hoge",ss);
    str2=pop_tag("hoge",ss);
  ss>>str2;
    return s;
  }
};


#endif