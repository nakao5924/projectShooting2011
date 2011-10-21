#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>

#include "connection.h"

class ServerConnection : private NonCopyable{
private:
	static const int MAX_CLIENT_NUM;
	enum CONNECTION_STATUS {WAIT_CONNECTION_MODE, REJECT_CONNECTION_MODE} status;
	int port_;
	vector<Connection *> clients_;
	vector<IPDATA> ips_;
	vector<char> connected_;
	int getFirstBrankIndex_();
	int findClientFromNetHandle_(int netHandle)const;
public:
	ServerConnection(int port = -1);
	bool startListen();
	bool endListen();
	void acceptNewConnection();
	void checkLostConnection();
	void setRejectConnectionMode();
	void setWaitConnectionMode();
	int send(const string &str);
	int send(int connection_id, const string &str);
	int receive(int connection_id, string &ret);

	int send(vector<int> &str);
	int send(int connection_id, vector<int> &str);
	int receive(int connection_id, vector<int> &ret);

	int getClientNum()const;
};

ServerConnection createServerConnection(int port, int clientNum);

#endif // __SERVER_H__