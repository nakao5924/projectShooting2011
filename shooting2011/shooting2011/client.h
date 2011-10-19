#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "connection.h"

class ClientConnection{
private:
	int _port;
	IPDATA _ip;
	Connection _server;
public:
	ClientConnection(const string &configFile);
	ClientConnection(int port, IPDATA ip);
	void assign(int port, IPDATA ip);
	bool connect();
	int send(const string &message);
	int receive(string &ret);
};

#endif // __CLIENT_H__
