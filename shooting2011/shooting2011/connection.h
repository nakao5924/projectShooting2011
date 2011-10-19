#ifndef __CONNECTION_H__
#define __CONNECTION_H__

class Connection{
private:
	static char _getDelimiter();
	static int _getBase();

	int _netHandle;

	char *_buf;
	int _bufsize;
	string _receivebuf;

	void _expandbuf(int newSize);
public:
	Connection();
	Connection(int netHandle);
	void setNetHandle(int netHandle);
	~Connection();

	// return value is:
	//   error is occured in DxLib	: -1
	//   else												: send data length
	int send(const string &str);

	// return value is:
	//   fail to receive perfect data	: -1
	//   error is occured in DxLib		: -2
	//   else													: data length
	int receive(string &ret);
};

#endif // __CONNECTION_H__