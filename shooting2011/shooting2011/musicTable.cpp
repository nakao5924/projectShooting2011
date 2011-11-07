#include"main.h"
#include"MusicTable.h"
#include<map>


void MusicTable::load_all_musics(string dir){
	HANDLE hFind;
	WIN32_FIND_DATA fd;
  hFind=FindFirstFile((dir+"*.*").c_str(),&fd);
	
	map<string,int> music_list;
	for(int i=0;;i++){
    int loaded_music = LoadSoundMem((dir+fd.cFileName).c_str());
		if(loaded_music!=-1)music_list[fd.cFileName]=loaded_music;
		if(FindNextFile(hFind,&fd))continue;
		else break;
	}
	FindClose(hFind);
	int i=0;
	for(map<string, int>::iterator it = music_list.begin(); it != music_list.end(); it++){
		string str(it->first);
		encode_table[str]=i;
		for(size_t j = str.size()-1; j >= 0; j--){
			if(str[j]=='.'){
				str=str.substr(0,j);
				break;
			}
		}
		encode_table[str]=i;
		decode_table[i]=it->second;
		i++;
	}
}


int MusicTable::get_sound_id(string str){
	return encode_table[str];
}


int MusicTable::decode(int tableIdx){
	return decode_table[tableIdx];
}

int MusicTable::encode(string str){
  return encode_table[str];
}
