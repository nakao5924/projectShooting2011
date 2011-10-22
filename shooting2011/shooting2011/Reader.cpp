#include "main.h"
#include "reader.h"
#include "graphicPattern.h"

SceneNormal* Reader::readEnemyData(const string filename){
	srand((int)time(0));
	list.clear();
	ifstream ifs(filename);

	string str;
	ifs>>str;
	ifs>>str;
	deque<EnemyData*> enemyData;
//	if(str!="<file>")return new SceneNormal(enemyData,0);
	int stagetime;
	if(str=="<stagetime>"){
		ifs>>stagetime>>str;
	}
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
			string name;//label
			ss>>name;
			list[name]=" <__make__> ";
			while(ss>>format){
				if(format=="</make>"){
					list[name]+=" </__make__> ";
					break;
				}
				list[name]+=format+" ";
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
	stringstream ss_sub=stringstream(str);
	str="";
	list.clear();
	while(ss_sub>>format){
		if(format=="<__make__>"){
			ss_sub>>format;
			deque<string> argument_list;
			string body_list;
			if(format=="<arg>"){
				while(ss_sub>>format){
					if(format=="</arg>"){
						ss_sub>>format;
						break;
					}
					argument_list.push_back(format);
				}
			}
			if(format=="<body>"){
				while(ss_sub>>format){
					if(format=="</body>"){
						ss_sub>>format;
						break;
					}
					body_list+=format+" ";
				}
			}else{
				body_list+=format+" ";
				while(ss_sub>>format){
					if(format=="</__make__>"){
						break;
					}
					body_list+=format+" ";
				}
			}
			if(format=="</__make__>"){
				for(size_t i=0;i<argument_list.size();i++){
					ss_sub>>format;
					list[argument_list[i]]=format;
				}
			}
			ss=stringstream(body_list);
			while(ss>>format){

				str+=addnext(format);
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
	while(ss>>format){
		if(format=="<enemy>"){
			string picture;
			ss>>format>>picture>>format>>format;
			enemylist.push_back(get_enemy_data(picture));
			while(format!="</enemy>")
				return(new SceneNormal(enemylist,stagetime));
		}
	
	
	}

	return(new SceneNormal(enemylist,stagetime));
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
		return new FirePatternAllRangeTimeRag(dtheta,startTheta,v,interval,graresource.getID("bulletbluenone16"));
	}
	else if(format=="bomb"){
		double d_theta,vv;
		ss>>d_theta>>vv;
		return new FirePatternBomb(d_theta,vv,graresource.getID("bulletwhitenone16"));
	}
	else if(format=="aimedRandom"){
		int interval,n;
		double v;
		ss>>interval>>v>>n;
		return new FirePatternAimedRandom(interval,n,v,graresource.getID("bulletgreennone16"));
	}
	else if(format=="nway"){
		int interval,n;
		double v,dir,dtheta;
		ss>>interval>>n>>v>>dir>>dtheta;
		return new FirePatternNway(interval,n,v,dir,dtheta,graresource.getID("bulletbluenone16"));
	}
	else if(format=="createself"){
		int interval,hp;
		double v;
		ss>>interval>>v>>hp;
		return new FirePatternCreateSelf(interval,v,hp,graresource.getID("araiup32"));
	}
	return(NULL);
}



