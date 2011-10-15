
#ifndef __INPUT_H__
#define __INPUT_H__

class Input {
	int hoge;
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	bool isButtonA;
	bool isButtonB;
	bool isButtonC;

public:
	Input();
	void getKeyInput();
	bool up();
	bool down();
	bool left();
	bool right();
	bool buttonA();
	bool buttonB();
	bool buttonC();
};

#endif
