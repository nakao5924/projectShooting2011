#ifndef __CONNECTION_H__
#define __CONNECTION_H__

class Connection : private NonCopyable{
private:
  static char getDelimiter_();
  static int getBase_();

  int netHandle_;

	vector<char> sendbuf_;
	vector<char> receivebuf_;
	vector<char> receive_returnbuf_;

	int sendHeader_(int length);
public:
	Connection();
	Connection(int netHandle);
	int getNetHandle()const;
	void setNetHandle(int netHandle);

	// return value is:
	//   error is occured in DxLib	: -1
	//   else												: send data length
	int send(int length, void *data);

	// return value is:
	//   fail to receive perfect data	: -1
	//   error is occured in DxLib		: -2
	//   else													: data length
	int receive(void *&ret);

	int send(const string &message);
	int receive(string &ret);

	int send(vector<int> &message);
	int receive(vector<int> &ret);
};

#endif // __CONNECTION_H__