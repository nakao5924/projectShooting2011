//*
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

class Reader{
	Reader();
public:
	static const deque<EnemyData*> readEnemyData(const string filename);
	
};

static string format;

static stringstream ss; 
template <class _Ty>
static _Ty* making_basic_object();
template <class _Ty>
static PatternComposer<_Ty>* making_object(PatternComposer<_Ty>*);




const deque<EnemyData*> Reader::readEnemyData(const string filename){
	ifstream ifs(filename);
	map<string,string> list; 
	while(ifs>>format){
		if(format=="<make>"){
			string name;
			ifs>>name;
			string contents;
			string str;
			while(ifs>>str){
				if(str=="</make>"){break;}
				contents+=str+" ";
			}
			list[name]=contents;
		}
	}
	ifs.close();
	ss=stringstream("");
	ifs=ifstream(filename);
	while(ifs>>format){
		map<string,string>::iterator it=list.find(format);
		if(it != list.end()){
			ss<<it->second<<" ";
		}else{
			ss<<format<<" ";
		}
	}
	ifs.close();
	deque<EnemyData*> enemylist;
	string str;

	while(ss>>str){
		if(str=="<enemy>"){
			int limit_time;
			double x,y;
			ss>>limit_time>>x>>y>>str;

		}
	
	
	
	}
	return(enemylist);
 }
template<class _Ty>
const PatternComposer<_Ty>* making_object(PatternComposer<_Ty> *pc){
}

/*
template<_Ty>
const _Ty* making_basic_object();


template<>
const MovePattern* making_basic_object<MovePattern>(){
	if(format=="straight"){
		double x,y;
		ss>>x>>y;
		return new  MovePatternUniformlyAcceleratedLinearMotion(x,y);
	}
}


/*

const deque<EnemyData*> Reader::readEnemyData(string filename){
	default_ifs=ifstream(filename);
	deque<EnemyData*> enemylist;
	ifs=&default_ifs;
	while(*ifs>>format){
		if(format=="<enemy>"){
			int time;
			double x,y;
			
			*ifs>>time>>x>>y;
			MovePattern* mp=making_object<MovePattern>(new PatternComposer<MovePattern>());
			FirePattern* fp=making_object<FirePattern>(new PatternComposer<FirePattern>());
			*ifs>>format;
		}else if(format=="<make>"){
			string name;
			*ifs>>name;
			stringstream*contents=new stringstream("");
			string str;
			while(*ifs>>str){
				if(str=="</make>"){break;}
				*contents<<str<<" ";
			}
			streamlist.push_back(make_pair(name,contents));
		}
	}
	return(enemylist);
 }

template<class _Ty>
static PatternComposer<_Ty>* making_object(PatternComposer<_Ty>*mp){
	*ifs>>format;
	if(_Ty* mp_sub = making_basic_object<_Ty>()){
		int limit_time;
		*ifs>>limit_time;
		mp->add(limit_time,mp_sub);
	}else{
		istream *sub=ifs;
		for(size_t i = 0; i < streamlist.size(); i++){
			if(streamlist[i].first==format){
				ifs=streamlist[i].second;
			}
		
		}
		while(*ifs>>format){
			making_object(mp);
		}

		ifs=sub;
		//基本パターンではない。
	}
	return(mp);
}

template<>
static MovePattern *making_basic_object<MovePattern>(){
	if(format=="straight"){
		double a1,a2;
		*ifs>>a1>>a2;
		return new  MovePatternUniformlyAcceleratedLinearMotion(a1,a2);

	}        
	return(NULL);
}
template<>
static FirePattern *making_basic_object<FirePattern>(){
	if(format=="none"){
		double a1,a2;
		*ifs>>a1>>a2;
		return new FirePatternNone(a1,a2);

	}        
	return(NULL);
}

//*/