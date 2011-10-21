#include "main.h"

#include <fstream>
#include <vector>
#include "main.h"

#include "server.h"

#include "connection.h"
#include "msgdump.h"

const int ServerConnection::MAX_CLIENT_NUM = 4;

static bool isSameIP(const IPDATA &a, const IPDATA &b){
	return a.d1 == b.d1 &&
		     a.d2 == b.d2 &&
		     a.d3 == b.d3 &&
		     a.d4 == b.d4;
}

int ServerConnection::getFirstBrankIndex_(){
	for(int i = 0; i < getClientNum(); ++i){
		if(!connected_[i]){
			return i;
		}
	}
	if(getClientNum() < MAX_CLIENT_NUM){
		clients_.push_back(static_cast<Connection *>(NULL));
		ips_.push_back(IPDATA());
		connected_.push_back(static_cast<char>(false));
		return getClientNum() - 1;
	}
	return -1;
}
int ServerConnection::findClientFromNetHandle_(int netHandle)const{
	for(int i = 0; i < getClientNum(); ++i){
		if(connected_[i] && clients_[i]->getNetHandle() == netHandle){
				return i;
		}
	}
	return -1;
}

ServerConnection::ServerConnection(int port):port_(port), status(WAIT_CONNECTION_MODE){}
bool ServerConnection::startListen(){
  return PreparationListenNetWork(port_) == -1;
}
bool ServerConnection::endListen(){
  return StopListenNetWork() == -1;
}
void ServerConnection::acceptNewConnection(){
  int netHandle = GetNewAcceptNetWork();
  if(netHandle != -1){
		Connection *newConnection = new Connection(netHandle);
		int tmp;
		IPDATA ip;
		switch(status){
		case WAIT_CONNECTION_MODE:
			tmp = getFirstBrankIndex_();
			if(tmp == -1){
				newConnection->send("ERROR 01: TOO MANY CLIENTS");
				delete newConnection;
				CloseNetWork(netHandle);
				return;
			}
			clients_[tmp] = newConnection;
			GetNetWorkIP(netHandle, &ips_[tmp]);
			connected_[tmp] = true;
			break;
		case REJECT_CONNECTION_MODE:
			GetNetWorkIP(netHandle, &ip);
			for(int i = 0; i < getClientNum(); ++i){
				if(!connected_[i] && isSameIP(ip, ips_[i])){
					clients_[i] = newConnection;
					connected_[i] = true;
				}
			}
			newConnection->send("ERROR 02: CONNECTION IS REJECTED");
			delete newConnection;
			CloseNetWork(netHandle);
			break;
		}
  }
}
void ServerConnection::checkLostConnection(){
	int lostHandle;
	while((lostHandle = GetLostNetWork()) != -1){
		int tmp = findClientFromNetHandle_(lostHandle);
		delete clients_[tmp];
		connected_[tmp] = false;
	}
}

void ServerConnection::setRejectConnectionMode(){
	status = REJECT_CONNECTION_MODE;
}
void ServerConnection::setWaitConnectionMode(){
	status = WAIT_CONNECTION_MODE;
}

int ServerConnection::send(const string &str){
  int result = 0;
  for(int i = 0; i < getClientNum(); ++i){
    int tmp = send(i, str);
    if(tmp < 0){
      result = tmp;
    }
  }
  return result;
}
int ServerConnection::send(int connection_id, const string &str){
  return clients_.at(connection_id)->send(str);
}
int ServerConnection::receive(int connection_id, string &ret){
  return clients_.at(connection_id)->receive(ret);
}
int ServerConnection::getClientNum()const{
	return static_cast<int>(clients_.size());
}

int ServerConnection::send(vector<int> &message){
	int result = 0;
	for(int i = 0; i < getClientNum(); ++i){
		int tmp = send(i, message);
		if(tmp < 0){
			result = tmp;
		}
	}
	return result;
}
int ServerConnection::send(int connection_id, vector<int> &message){
	return clients_.at(connection_id)->send(message);
}
int ServerConnection::receive(int connection_id, vector<int> &ret){
	return clients_.at(connection_id)->receive(ret);
}

ServerConnection *ScreateServerConnection(int port, int clientNum){
  static const int BLACK = GetColor(0, 0, 0);
  static const int WHITE = GetColor(0, 0, 0);
  ServerConnection *result = new ServerConnection(port);
  result->startListen();
  while(result->getClientNum() < clientNum){
    result->getClientNum();
    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
    DrawFormatString(60, 60, WHITE, "access: %d", result->getClientNum());
    ScreenFlip();
    Sleep(10);
    if( ProcessMessage() < 0 ) break ;
    if( CheckHitKey( KEY_INPUT_ESCAPE ) ){
      return NULL;
    }
  }
  result->endListen();
  return result;
}
