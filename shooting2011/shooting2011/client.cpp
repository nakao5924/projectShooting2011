#include "main.h"

#include "client.h"

#include <iostream>
#include <fstream>
#include "connection.h"

ClientConnection::ClientConnection(int port, IPDATA ip):port_(port), ip_(ip){}
void ClientConnection::assign(int port, IPDATA ip){
  port_ = port;
  ip_ = ip;
}
bool ClientConnection::connect(){
  int netHandle = ConnectNetWork(ip_, port_);
  if(netHandle == -1){
    return false;
  }
  server_.setNetHandle(netHandle);
  return true;
}
int ClientConnection::send(const string &message){
  return server_.send(message);
}
int ClientConnection::receive(string &ret){
  return server_.receive(ret);
}
