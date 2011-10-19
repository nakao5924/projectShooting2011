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
int Connection::_getBase(){
	static int ret = 1 << (CHAR_BIT - 1);
	return ret;
}
char Connection::_getDelimiter(){
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
	assert(static_cast<unsigned char>(ret) >= _getBase());
	return ret;
}

void Connection::_expandbuf(int newSize){
	if(newSize <= _bufsize) return;
	newSize = max(_bufsize * 2, newSize);
	_bufsize = newSize;
	delete[] _buf;
	_buf = new char[_bufsize];
}
Connection::Connection():_netHandle(-1), _buf(NULL), _bufsize(0){}
Connection::Connection(int netHandle):_netHandle(netHandle), _buf(NULL), _bufsize(0){}
Connection::~Connection(){
	delete[] _buf;
}
void Connection::setNetHandle(int netHandle){
	_netHandle = netHandle;
}

int Connection::send(const string &str){
	if(_netHandle == -1)return -1;
	assert(str.length() <= INT_MAX);
	int length = static_cast<int>(str.length());
	_expandbuf(length + 2);
	int pos = 0;
	_buf[pos++] = _getDelimiter();
	while(length > 0){
		_buf[pos++] = static_cast<char>(length % _getBase());
		length /= _getBase();
	}
	_buf[pos++] = _getDelimiter();
	int header_length = pos;
	if(NetWorkSend(_netHandle, static_cast<void *>(_buf), header_length) == -1){
		return -1;
	}
	sprintf(_buf, "%s", str.c_str());
	if(NetWorkSend(_netHandle, static_cast<void *>(_buf), static_cast<int>(str.length())) == -1){
		return -1;
	}
	return header_length + static_cast<int>(str.length());
}

int Connection::receive(string &ret){
	if(_netHandle == -1){
		return -2;
	}
	int length = GetNetWorkDataLength(_netHandle);
	_expandbuf(length);
	if(NetWorkRecv(_netHandle, static_cast<void *>(_buf), length) == -1){
		return -2;
	}
	_receivebuf += string(_buf, length);
	if(_receivebuf.empty()){
		return -1;
	}
	if(_receivebuf[0] != _getDelimiter()){
		size_t i = 1;
		while(i < _receivebuf.length() && _receivebuf[i] != _getDelimiter()){
			++i;
		}
		_receivebuf = _receivebuf.substr(i);
	}
	size_t i = 1;
	size_t data_length = 0;
	size_t base = 1;
	while(true){
		if(i >= _receivebuf.length()){
			return -1;
		}
		if(_receivebuf[i] == _getDelimiter()){
			break;
		}
		data_length += _receivebuf[i] * base;
		base *= _getBase();
		++i;
	}
	
	size_t header_length = i + 1;
	if(_receivebuf.length() < header_length + data_length){
		return -1;
	}
	ret = _receivebuf.substr(header_length, data_length);
	_receivebuf = _receivebuf.substr(header_length + data_length);
	return data_length;
}
