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
			return(new EnemyData(start_time,x,y,mp,fp));
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
	static const deque<EnemyData*> readEnemyData(const string filename);
	
};



const deque<EnemyData*> Reader::readEnemyData(const string filename){
	srand((int)time(0));
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
		if(format=="<comment>"){
			while(ss>>str_sub){
				if(str_sub=="</comment>"){break;}
			}
		}else{
			str+=format+" ";
		}
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
		if(format=="<func>"){
			map<string,string>func_list;
			deque<string> str_list;
			while(ss>>format){
				if(format=="<_func>"){
					break;
				}
				str_list.push_back(format);
			}
			for(size_t i=0;i<str_list.size();i++){
				string value;
				ss>>value;
				func_list[str_list[i]]=value;
			}
			while(ss>>format){
				if(format=="</func>"){
					break;
				}
				map<string,string>::iterator it=func_list.find(format);
				if(it!=func_list.end()){
					str+=it->second+" ";
				}else{
					str+=format+" ";
				}
			}
		}else{
			str+=format+" ";
		}
	}
	ss=stringstream(str);
	str="";
	while(ss>>format){
		if(format=="rand"){
			double min_val,max_val;
			ss>>min_val>>max_val;
			stringstream ss_sub;
			ss_sub<<(max_val-min_val)*(rand()%1000)/1000;
			ss_sub>>format;
			str+=format+" ";
		}else{
			str+=format+" ";
		}
	}

	ss=stringstream(str);
	str="";
	while(ss>>format){
		if(format=="<add>"){
			int sum=0;
			while(ss>>format){
				if(format=="</add>")break;
				sum+=atoi(format.c_str());
			}
			stringstream ss_sub;
			ss_sub<<sum;
			ss_sub>>format;
			str+=format+" ";
		}else{
			str+=format+" ";
		}
	}
	ss=stringstream(str);
	str="";
	while(ss>>format){
		if(format=="<if>"){
			double in1,in2;
			ss>>in1>>in2;
			if(in1>in2){
				while(ss>>format){
					if(format=="</if>")break;
					str+=format+" ";
				}
			}else{
				while(ss>>format){
					if(format=="</if>")break;
					str+=format+" ";
				}
			}
		}else{
			str+=format+" ";
		}
	}



	ss=stringstream(str);
	deque<EnemyData*> enemylist;
#ifndef _DEBUG_
	if(format!="<endfile>")return(enemylist);
#endif 
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
	if(format=="straight"){
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