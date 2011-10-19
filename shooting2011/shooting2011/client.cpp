#include "main.h"

#include "client.h"

#include <iostream>
#include <fstream>
#include "connection.h"

ClientConnection::ClientConnection(const string &configFile){
	ifstream ifs(configFile);
	ifs >> _port;
	ifs >> _ip.d1 >> _ip.d2 >> _ip.d3 >> _ip.d4;
}
ClientConnection::ClientConnection(int port, IPDATA ip):_port(port), _ip(ip){
}
void ClientConnection::assign(int port, IPDATA ip){
	_port = port;
	_ip = ip;
}
bool ClientConnection::connect(){
	int netHandle = ConnectNetWork(_ip, _port);
	if(netHandle == -1){
		return false;
	}
	_server.setNetHandle(netHandle);
	return true;
}
int ClientConnection::send(const string &message){
	return _server.send(message);
}
int ClientConnection::receive(string &ret){
	return _server.receive(ret);
}
