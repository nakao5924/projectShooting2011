#include "main.h"
#include "reader.h"
#include "graphicPattern.h"
SceneNormal* Reader::readEnemyData(const string filename){
	srand((int)time(0));
	list.clear();
	ifstream ifs(filename);
	string str="";
	int maxframe;
	ifs>>str>>maxframe>>str;
	str="";
	string str_sub;
	while(ifs>>str){
		str_sub+=str+" ";
	}
	ifs.close();
	str="";
	for(size_t i=0;i<str_sub.size();i++){
		if(str_sub[i]==','||str_sub[i]=='('||str_sub[i]==')'){str+=" ";}
		else if(str_sub[i]=='<'){str+=" <";}
		else if(str_sub[i]=='>'){str+="> ";}
		else if(str_sub[i]=='P'&&str_sub[i+1]=='I'){
			i++;
			str+=" 3.14 ";
		}else str+=str_sub[i];
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
		if(format=="<mul>"){
			double sum=1;
			while(ss>>format){
				if(format=="</mul>")break;
				sum*=atof(format.c_str());
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
//#ifndef _DEBUG_
//	if(format!="<endfile>")return(enemylist);
//#endif 
	while(ss>>format){
		if(format=="<enemy>"){
			ss>>format;
			string pictureId;
			if(format=="<picture>"){
				ss>>pictureId>>format;
				ss>>format;
			}else{pictureId="";}
			enemylist.push_back(get_enemy_data(pictureId));
			if(format!="</enemy>")
				return new SceneNormal(enemylist,maxframe);
		}
	
	
	}

	return(new SceneNormal(enemylist,maxframe));
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
	else if(format=="circle"){
		string str;
		double delay,r,omega;
		ss>>str;
		delay=atof(str.c_str());
		ss>>str;
		r=atof(str.c_str());
		ss>>str;
		omega=atof(str.c_str());
		return new MovePatternCircle(delay,r,omega);
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
		return new FirePatternAllRangeTimeRag(dtheta,startTheta,v,interval,graresource.get_graphic_id("bulletbluenone16"));
	}
	else if(format=="bomb"){
		double d_theta,vv;
		ss>>d_theta>>vv;
		return new FirePatternBomb(d_theta,vv,graresource.get_graphic_id("bulletwhitenone16"));
	}
	else if(format=="aimedRandom"){
		int interval,n;
		double v;
		ss>>interval>>v>>n;
		return new FirePatternAimedRandom(interval,n,v,graresource.get_graphic_id("bulletgreennone16"));
	}
	else if(format=="nway"){
		int interval,n;
		double v,dir,dtheta;
		ss>>interval>>n>>v>>dir>>dtheta;
		return new FirePatternNway(interval,n,v,dir,dtheta,graresource.get_graphic_id("bulletbluenone16"));
	}
	else if(format=="createself"){
		int interval,hp;
		double v;
		ss>>interval>>v>>hp;
		return new FirePatternCreateSelf(interval,v,hp,graresource.get_graphic_id("araiup32"));
	}
	return(NULL);
}



