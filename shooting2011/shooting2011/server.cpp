#include "main.h"

#include <fstream>
#include <vector>
#include "main.h"

#include "server.h"

#include "connection.h"

ServerConnection::ServerConnection(int port, int clientNum):_port(port), _clientNum(clientNum){}
bool ServerConnection::startListen(){
	return PreparationListenNetWork(_port) == -1;
}
bool ServerConnection::endListen(){
	return StopListenNetWork() == -1;
}
void ServerConnection::action(){
	int netHandle = GetNewAcceptNetWork();
	if(netHandle != -1){
		_clients.push_back(netHandle);
	}
}
int ServerConnection::send(int connection_id, const string &str){
	return _clients.at(connection_id).send(str);
}
int ServerConnection::receive(int connection_id, string &ret){
	return _clients.at(connection_id).receive(ret);
}
int ServerConnection::size()const{
	return static_cast<int>(_clients.size());
}
