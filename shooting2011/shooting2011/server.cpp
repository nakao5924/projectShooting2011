#include "main.h"

#include <fstream>
#include <vector>
#include "main.h"

#include "server.h"

#include "connection.h"
#include "msgdump.h"

ServerConnection::ServerConnection(int port):port_(port){}
bool ServerConnection::startListen(){
  return PreparationListenNetWork(port_) == -1;
}
bool ServerConnection::endListen(){
  return StopListenNetWork() == -1;
}
void ServerConnection::action(){
  int netHandle = GetNewAcceptNetWork();
  if(netHandle != -1){
    clients_.push_back(new Connection(netHandle));
  }
}
int ServerConnection::send(const string &str){
  int result = 0;
  for(int i = 0; i < size(); ++i){
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
int ServerConnection::size()const{
  return static_cast<int>(clients_.size());
}

ServerConnection *ScreateServerConnection(int port, int clientNum){
  static const int BLACK = GetColor(0, 0, 0);
  static const int WHITE = GetColor(0, 0, 0);
  ServerConnection *result = new ServerConnection(port);
  result->startListen();
  while(result->size() < clientNum){
    result->action();
    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
    DrawFormatString(60, 60, WHITE, "access: %d", result->size());
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
