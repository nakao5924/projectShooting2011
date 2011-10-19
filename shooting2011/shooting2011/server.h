#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>

#include "connection.h"

class ServerConnection{
private:
	int _port;
	vector<Connection> _clients;
public:
	ServerConnection(int port = -1);
	bool startListen();
	bool endListen();
	void action();
	int send(const string &str);
	int send(int connection_id, const string &str);
	int receive(int connection_id, string &ret);
	int size()const;
};

ServerConnection createServerConnection(int port, int clientNum);

#endif // __SERVER_H__