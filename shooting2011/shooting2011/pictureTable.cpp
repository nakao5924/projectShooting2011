#include"main.h"
#include"pictureTable.h"
#include<map>


void PictureTable::load_all_graphics(string dir){
	HANDLE hFind;
	WIN32_FIND_DATA fd;
  hFind=FindFirstFile((dir+"*.*").c_str(),&fd);
	
	map<string,int> graphic_list;
	for(int i=0;;i++){
    int loadedgraph = LoadGraph((dir+fd.cFileName).c_str());
		if(loadedgraph!=-1)graphic_list[fd.cFileName]=loadedgraph;
		if(FindNextFile(hFind,&fd))continue;
		else break;
	}
	FindClose(hFind);
	int i=0;
	for(map<string, int>::iterator it = graphic_list.begin();it!=graphic_list.end();it++){
    bool animflg = false;
		string str(it->first);
		for(size_t j=0;j<str.size();j++){
			if(str[j]=='.'){
				str=str.substr(0,j);
        break;
			}else if(str[j]=='_'){
				//animationpart
        animflg = true;
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
        int *tempbuf = (int*)malloc(sum * sizeof(int));
        int xsize, ysize;
        GetGraphSize(it->second, &xsize, &ysize);
        string filname = dir + it->first;
        LoadDivGraph((dir + it->first).c_str(), sum, x, y, xsize/x, ysize/y, tempbuf);
        for (int k = 0; k < sum; k++) {
          decode_table[i].push_back(tempbuf[k]);
        }
        free(tempbuf);
        DeleteGraph(it->second);
        break;
			}
		}
		graphic_encode_table[str]=i;
    if (!animflg) {
      decode_table[i].push_back(it->second);
    }
		int x,y;
    int graphic_id = animflg? decode_table[i][0] : it->second;
    GetGraphSize(graphic_id,&x,&y);
		half_size_table[i]=make_pair(x/2,y/2);
		i++;
	}
}


int PictureTable::getID(string str){
	return graphic_encode_table[str];
}

int PictureTable::getanimation(int tableIdx,int animIdx){
  if (decode_table[tableIdx].size() == 1) {
    return decode_table[tableIdx][decode_table[tableIdx].size()-1];
  } else {
    return decode_table[tableIdx][animIdx];
  }
}

int PictureTable::decode(int tableIdx, int animationIdx){
  int animsize;
  if ((animsize = decode_table[tableIdx].size()) == 1) {
    return decode_table[tableIdx][0];
  }
  return decode_table[tableIdx][animationIdx % animsize];
}
	
int PictureTable::encode(string str){
  return graphic_encode_table[str];
}