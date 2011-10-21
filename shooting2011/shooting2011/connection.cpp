#include "main.h"

#include "connection.h"

#include <cstdio>
#include <string>
#include <cassert>
#include <map>

#include "msgdump.h"
/*
map<int, string> dummyPipe;

void dumpDummyPipe(){
	msgDump("dummyPipe:");
	for(map<int, string>::iterator i = dummyPipe.begin(); i != dummyPipe.end(); ++i){
		msgDump(i->first);
		msgDump(i->second);
	}
}

int dummySend(int netHandle, void *data, int length){
	dummyPipe[netHandle] += string(static_cast<char *>(data), length);
	return 0;
}
int dummyRecv(int netHandle, void *data, int length){
	memcpy(data, static_cast<const void *>(dummyPipe[netHandle].substr(0, length).c_str()), length);
	dummyPipe[netHandle] = dummyPipe[netHandle].substr(length);
	return 0;
}
int dummyGetDataLength(int netHandle){
	return static_cast<int>(dummyPipe[netHandle].length());
}

#define NetWorkSend dummySend
#define NetWorkRecv dummyRecv
#define GetNetWorkDataLength dummyGetDataLength
*/
int Connection::getBase_(){
	static int ret = 1 << (CHAR_BIT - 1);
	return ret;
}
char Connection::getDelimiter_(){
	static char ret = 0;
	if(ret == 0){
		++ret;
		for(int i = 1; i < CHAR_BIT; ++i){
			ret <<= 1;
			if(i % 2 == 0){
				++ret;
			}
		}
	}
	assert(static_cast<unsigned char>(ret) >= getBase_());
	return ret;
}

int Connection::sendHeader_(int length){
	sendbuf_.resize(0);
	sendbuf_.push_back(getDelimiter_());
	while(length > 0){
		sendbuf_.push_back(static_cast<char>(length % getBase_()));
		length /= getBase_();
	}
	sendbuf_.push_back(getDelimiter_());
	assert(sendbuf_.size() <= INT_MAX);
	int header_length = static_cast<int>(sendbuf_.size());
	if(NetWorkSend(netHandle_, static_cast<void *>(&sendbuf_[0]), header_length) == -1){
		return -1;
}
	sendbuf_.resize(0);
	return header_length;
}

Connection::Connection():netHandle_(-1){}
Connection::Connection(int netHandle):netHandle_(netHandle){}

void Connection::setNetHandle(int netHandle){
	netHandle_ = netHandle;
}
int Connection::getNetHandle()const{
	return netHandle_;
}

int Connection::send(int length, void *data){
	if(netHandle_ == -1)return -2;
	int header_length = sendHeader_(length);
	if(header_length < 0){
		return header_length;
	}
	if(NetWorkSend(netHandle_, data, length) == -1){
		return -1;
	}
	return header_length + length;
}

int Connection::receive(void *&ret){
	if(netHandle_ == -1){
		return -2;
	}
	int length = GetNetWorkDataLength(netHandle_);
	if(length < 0){
		return -2;
	}else if(length > 0){
		assert(receivebuf_.size() <= INT_MAX);
		int used_length = static_cast<int>(receivebuf_.size());
		receivebuf_.resize(used_length + length);
		if(NetWorkRecv(netHandle_, static_cast<void *>(&receivebuf_[used_length]), length) == -1){
			return -2;
		}
	}
	if(receivebuf_.empty()){
		return -1;
	}
	if(receivebuf_[0] != getDelimiter_()){
		size_t i = 1;
		while(i < receivebuf_.size() && receivebuf_[i] != getDelimiter_()){
			++i;
		}
		receivebuf_.erase(receivebuf_.begin(), receivebuf_.begin() + i);
	}
	size_t i = 1;
	size_t data_length = 0;
	size_t base = 1;
	while(true){
		if(i >= receivebuf_.size()){
			return -1;
		}
		if(receivebuf_[i] == getDelimiter_()){
			break;
		}
		assert(receivebuf_[i] < getBase_());
		data_length += receivebuf_[i] * base;
		base *= getBase_();
		++i;
	}
	
	size_t header_length = i + 1;
	if(receivebuf_.size() < header_length + data_length){
		return -1;
	}
	receive_returnbuf_.assign(receivebuf_.begin() + header_length, receivebuf_.begin() + header_length + data_length);
	receivebuf_.erase(receivebuf_.begin(), receivebuf_.begin() + header_length + data_length);
	ret = static_cast<void *>(&receive_returnbuf_[0]);
	return data_length;
}

int Connection::send(const string &message){
	assert(message.length() <= INT_MAX);
	vector<char> buf(message.begin(), message.end());
	return send(static_cast<int>(message.length()), static_cast<void *>(&buf[0]));
}

int Connection::receive(string &ret){
	void *buf = NULL;
	int tmp = receive(buf);
	if(tmp < 0){
		return tmp;
	}
	ret = string(static_cast<const char *>(buf), tmp);
	return tmp;
}

int Connection::send(vector<int> &message){
	assert(message.size() <= INT_MAX / sizeof(int));
	return send(static_cast<int>(message.size() * sizeof(int)), static_cast<void *>(&message[0]));
}

int Connection::receive(vector<int> &ret){
	void *buf = NULL;
	int tmp = receive(buf);
	if(tmp < 0){
		return tmp;
	}
	assert(tmp % sizeof(int) == 0);
	ret.assign(static_cast<int *>(buf), static_cast<int *>(buf) + tmp / sizeof(int));
	return tmp;
}
