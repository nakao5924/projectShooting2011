
#ifndef __INPUT_H__
#define __INPUT_H__

class Input {
	//int data_;
	static const int WATCH_KEYS_NUM = 7;
	static const int WATCH_KEYS[WATCH_KEYS_NUM];
	string data_;
	/*
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	bool isButtonA;
	bool isButtonB;
	bool isButtonC;
	*/
	bool getKeyStatus_(int keyId)const;
public:
	Input();
	~Input();
	void getKeyInput();
	bool up()const;
	bool down()const;
	bool left()const;
	bool right()const;
	bool buttonA()const;
	bool buttonB()const;
	bool buttonC()const;

	string encode()const;
	void decode(const string &message);
  static string getEmptyMessage();
  void clear();
};

#endif
