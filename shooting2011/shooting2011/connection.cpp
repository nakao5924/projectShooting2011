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

void Connection::expandbuf_(int newSize){
  if(newSize <= bufsize_) return;
  newSize = max(bufsize_ * 2, newSize);
  bufsize_ = newSize;
  delete[] buf_;
  buf_ = new char[bufsize_];
}
Connection::Connection():netHandle_(-1), buf_(NULL), bufsize_(0){}
Connection::Connection(int netHandle):netHandle_(netHandle), buf_(NULL), bufsize_(0){}
Connection::~Connection(){
  delete[] buf_;
}
void Connection::setNetHandle(int netHandle){
  netHandle_ = netHandle;
}

int Connection::send(const string &str){
  if(netHandle_ == -1)return -1;
  assert(str.length() <= INT_MAX);
  int length = static_cast<int>(str.length());
  expandbuf_(length + 2);
  int pos = 0;
  buf_[pos++] = getDelimiter_();
  while(length > 0){
    buf_[pos++] = static_cast<char>(length % getBase_());
    length /= getBase_();
  }
  buf_[pos++] = getDelimiter_();
  int header_length = pos;
  if(NetWorkSend(netHandle_, static_cast<void *>(buf_), header_length) == -1){
    return -1;
  }
  sprintf(buf_, "%s", str.c_str());
  if(NetWorkSend(netHandle_, static_cast<void *>(buf_), static_cast<int>(str.length())) == -1){
    return -1;
  }
  return header_length + static_cast<int>(str.length());
}

int Connection::receive(string &ret){
  if(netHandle_ == -1){
    return -2;
  }
  int length = GetNetWorkDataLength(netHandle_);
  expandbuf_(length);
  if(NetWorkRecv(netHandle_, static_cast<void *>(buf_), length) == -1){
    return -2;
  }
  receivebuf_ += string(buf_, length);
  if(receivebuf_.empty()){
    return -1;
  }
  if(receivebuf_[0] != getDelimiter_()){
    size_t i = 1;
    while(i < receivebuf_.length() && receivebuf_[i] != getDelimiter_()){
      ++i;
    }
    receivebuf_ = receivebuf_.substr(i);
  }
  size_t i = 1;
  size_t data_length = 0;
  size_t base = 1;
  while(true){
    if(i >= receivebuf_.length()){
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
  if(receivebuf_.length() < header_length + data_length){
    return -1;
  }
  ret = receivebuf_.substr(header_length, data_length);
  receivebuf_ = receivebuf_.substr(header_length + data_length);
  return data_length;
}
