#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>

#include "connection.h"

class ServerConnection{
private:
	int _port;
	int _clientNum;
	vector<Connection> _clients;
public:
	ServerConnection(int port, int clientNum);
	bool startListen();
	bool endListen();
	void action();
	int send(int connection_id, const string &str);
	int receive(int connection_id, string &ret);
	int size()const;
};


#endif // __SERVER_H__