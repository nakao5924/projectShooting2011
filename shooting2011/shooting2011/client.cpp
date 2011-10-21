#include "main.h"

#include "client.h"

#include <iostream>
#include <fstream>
#include "connection.h"

ClientConnection::ClientConnection(int port, IPDATA ip):port_(port), ip_(ip), connected_(false){}
void ClientConnection::assign(int port, IPDATA ip){
	assert(!connected_);
	port_ = port;
	ip_ = ip;
}
bool ClientConnection::connect(){
	int netHandle = ConnectNetWork(ip_, port_);
	if(netHandle == -1){
		return false;
	}
	server_.setNetHandle(netHandle);
	connected_ = true;
	return true;
}
int ClientConnection::send(const string &message){
	assert(connected_);
	return server_.send(message);
}
int ClientConnection::receive(string &ret){
	assert(connected_);
	return server_.receive(ret);
}

int ClientConnection::send(vector<int> &message){
	assert(connected_);
	return server_.send(message);
}

int ClientConnection::receive(vector<int> &ret){
	assert(connected_);
	return server_.receive(ret);
}
