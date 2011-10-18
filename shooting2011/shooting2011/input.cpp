
#include "main.h"
#include "input.h"

Input::Input() {
	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = false;
	isButtonA = false;
	isButtonB = false;
	isButtonC = false;
}

Input::~Input() {}

void Input::getKeyInput() {
	isUp = (CheckHitKey( KEY_INPUT_UP ) == 1);
	isDown = (CheckHitKey( KEY_INPUT_DOWN ) == 1);
	isLeft = (CheckHitKey( KEY_INPUT_LEFT ) == 1);
	isRight = (CheckHitKey( KEY_INPUT_RIGHT ) == 1);
	isButtonA = (CheckHitKey( KEY_INPUT_Z ) == 1);
	isButtonB = (CheckHitKey( KEY_INPUT_X ) == 1);
	isButtonC = (CheckHitKey( KEY_INPUT_C ) == 1);
}

bool Input::up() {return isUp;}

bool Input::down() {return isDown;}

bool Input::left() {return isLeft;}

bool Input::right() {return isRight;}

bool Input::buttonA() {return isButtonA;}

bool Input::buttonB() {return isButtonB;}

bool Input::buttonC() {return isButtonC;}

