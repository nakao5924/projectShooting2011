//*
#ifndef __READRE_H__
#define __READRE_H__
#include<fstream>
#include<sstream>
#include <deque>
#include <string>
#include <map>
using namespace std;
#include"stageData.h"
#include"movePattern.h"
#include"firePattern.h"
#include"patternComposer.h"

static string format;
static stringstream ss; 
static map<string,string> list; 


class Reader{
private:
	Reader();
	static EnemyData* get_enemy_data(){

		int start_time;
		double x,y;
		ss>>start_time>>x>>y>>format;
		
		MovePattern *mp=making_object<MovePattern>(new PatternComposer<MovePattern>());
		FirePattern *fp=making_object<FirePattern>(new PatternComposer<FirePattern>());
		return(new EnemyData(start_time,x,y,mp,fp));
	}

	template<class _Ty>
	static PatternComposer<_Ty>* making_object(PatternComposer<_Ty> *pc){
		_Ty *p=making_basic_object<_Ty>();
		if(p==NULL)
			return(pc);
		int limit_time;
		ss>>limit_time;
		ss>>format;
		return(making_object<_Ty>(pc->add(limit_time,p)));
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
	static const deque<EnemyData*> readEnemyData(const string filename);
	
};



const deque<EnemyData*> Reader::readEnemyData(const string filename){
	ifstream ifs(filename);
	string str="";
	string str_sub;
	while(ifs>>str){
		str_sub+=str+" ";
	}
	ifs.close();
	str="";
	for(size_t i=0;i<str_sub.size();i++){
		if(str_sub[i]==','||str_sub[i]=='('||str_sub[i]==')')str+=" ";
		else if(str_sub[i]=='<')str+=" <";
		else if(str_sub[i]=='>')str+="> ";
		else str+=str_sub[i];
	}
	ss=stringstream(str);
	str="";
	while(ss>>format){
		if(format=="<make>"){
			string name;
			ss>>name;
			list[name]="";
			str_sub="";
			while(ss>>str_sub){
				if(str_sub=="</make>"){break;}
				list[name]+=str_sub+" ";
			}
		}else{
			str+=format+" ";
		}
	}
	ss=stringstream(str);
	str="";
	while(ss>>format){

		str+=addnext(format);
	}
	ss=stringstream(str);
	str="";
	while(ss>>format){
		if(format=="rand"){
			int min,max;
			ss>>min>>max;
			str+=min+GetRand(max-min);
		}else{
			str+=format+" ";
		}
	}
	ss=stringstream(str);
	deque<EnemyData*> enemylist;

	while(ss>>format){
		if(format=="<enemy>"){
			enemylist.push_back(get_enemy_data());
			while(format!="</enemy>")ss>>format;
		}
	
	
	}
	return(enemylist);
 }




template<>
MovePattern *Reader::making_basic_object<MovePattern>(){
	if(format=="streight"){
		double x,y;
		ss>>x>>y;
		return new  MovePatternUniformlyAcceleratedLinearMotion(x,y);
	}else if(format=="lissajous" ){
		double x,y;
		double ampx,freqx,deltax;
		double ampy,freqy,deltay;
		ss>>x>>y>>ampx>>freqx>>deltax>>ampy>>freqy>>deltay;
		return new MovePatternLissajous(x,y,ampx,freqx,deltax,ampy,freqy,deltay);
	}
	return(NULL);
}
template<>
FirePattern *Reader::making_basic_object<FirePattern>(){
	if(format=="none"){

		return new FirePatternNone();
	}else if(format=="allrange"){
		double dtheta,startTheta,v;int interval;
		ss>>dtheta>>startTheta>>v>>interval;
		return new FirePatternAllRangeTimeRag(dtheta,startTheta,v,interval);
	}
	return(NULL);
}




#endif

//*/