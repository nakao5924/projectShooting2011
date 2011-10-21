#include<vector>
#include<deque>
#include"main.h"

class Connection{
private:
	static const int BUFSIZE = 1024;
	IPDATA _ip;
	int _port;
	int _netHandle;
	char _buf[BUFSIZE];
	deque<char> _data;
public:
	Connection(int port, int netHandle):_port(port), _netHandle(netHandle){
		GetNetWorkIP(_netHandle, &_ip);
	}
	IPDATA getIP()const{
		return _ip;
	}
	int getPort()const{
		return _port;
	}
	int getNetHandle()const{
		return _netHandle;
	}
	void recieve(){
		int length = GetNetWorkDataLength(_netHandle);	// データの量を取得
		NetWorkRecv(_netHandle, _buf, length);	// データをバッファに取得
		for(int i = 0; i < length; ++i){
		  _data.push_back(_buf[i]);
		}
	}
	void read(char *buf, int length = (int)_data.size()){
	  for(int i = 0; i < length; ++i){
			buf[i] = _data.front();
			_data.pop_front();
		}
	}
	void action(){
		ProcessMessage();
		recieve();
	}
};

class ConnectionManager{
private:
	int _port;
	vector<Connection> _connections;
public:
	ConnectionManager(int port):_port(port){
		PreparationListenNetWork(_port);
	}
	int getPort()const{
		return _port;
	}
	void getConnection(){
	}
	bool removeConnection(int netHandle){
		bool res = false;
		for(vector<Connection>::iterator i = _connections.begin(); i != _connections.end(); ){
			if(netHandle == i->getNetHandle()){
				i = _connections.erase(i);
				res = true;
				continue;
			}
			++i;
		}
		return res;
	}
	void action(){
		int netHandle = GetNewAcceptNetWork();
		if(netHandle != -1){
			_connections.push_back(Connection(_port, netHandle));
			// 接続してきたマシンのＩＰアドレスを得る

			ProcessMessage();

			// データ受信
			for(vector<Connection>::iterator i = _connections.begin(); i != _connections.end(); ++i){
				i->recieve();
			}

			// 新たに切断されたネットワークハンドルを得る
			int lost;
			do{
				lost = GetLostNetWork() ;
			}while(removeConnection(lost));

			// 切断された接続が今まで通信してた相手だった場合ループを抜ける
			if( LostHandle == NetHandle ) break ;
		}
	}
};
