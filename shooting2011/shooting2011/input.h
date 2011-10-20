
#ifndef __INPUT_H__
#define __INPUT_H__

class Input {
	//int data_;
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	bool isButtonA;
	bool isButtonB;
	bool isButtonC;
public:
	Input();
	~Input();
	void getKeyInput();
	bool up();
	bool down();
	bool left();
	bool right();
	bool buttonA();
	bool buttonB();
	bool buttonC();

	string encode();
	void decode(const string &str);
  // 古い仕様。今度消す。
  static string getEmptyMessage();
  void clear();
};

#endif
