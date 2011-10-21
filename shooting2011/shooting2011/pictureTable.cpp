#include"main.h"
#include"pictureTable.h"
#include<map>


void PictureTable::load_all_graphics(string str){
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	hFind=FindFirstFile((str+"*.*").c_str(),&fd);
	
	map<string,int> graphic_list;
	for(int i=0;;i++){
		int loadedgraph=LoadGraph((str+fd.cFileName).c_str());
		if(loadedgraph!=-1)graphic_list[fd.cFileName]=loadedgraph;
		if(FindNextFile(hFind,&fd))continue;
		else break;
	}
	FindClose(hFind);
	int i=0;
	for(map<string, int>::iterator it = graphic_list.begin();it!=graphic_list.end();it++){
		string str(it->first);
		for(size_t j=0;j<str.size();j++){
			if(str[j]=='.'){
				str=str.substr(0,j);
			}else if(str[j]=='_'){
				//animationpart

				string str_sub=str.substr(j+1,str.size()-j+1);
				str=str.substr(0,j);
				for(size_t k=0;k<str_sub.size();k++){
					if(str_sub[k]=='_'){
						str_sub[k]=' ';
					}
				}
				stringstream ss(str_sub);
				int sum,x,y;
				ss>>sum>>x>>y;
			}
		}
		decode_table[i]=it->second;
		graphic_encode_table[str]=i;
		int x,y;
		GetGraphSize(it->second,&x,&y);
		half_size_table[i]=make_pair(x/2,y/2);
		i++;
	}
}


int PictureTable::getID(string str){
	return graphic_encode_table[str];
}

int PictureTable::getanimation(int graphicID,int framecount){
	
	return graphicID;
}