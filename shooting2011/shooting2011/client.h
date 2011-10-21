#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "connection.h"

class ClientConnection : private NonCopyable{
private:
	int port_;
	IPDATA ip_;
	Connection server_;
	bool connected_;
public:
	ClientConnection(int port, IPDATA ip);
	void assign(int port, IPDATA ip);
	bool connect();
	int send(const string &message);
	int receive(string &ret);
	int send(vector<int> &message);
	int receive(vector<int> &ret);
};

#endif // __CLIENT_H__
