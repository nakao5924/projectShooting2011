
#include "main.h"
#include "input.h"

const int Input::WATCH_KEYS[WATCH_KEYS_NUM] = {
  KEY_INPUT_UP,
  KEY_INPUT_DOWN,
  KEY_INPUT_LEFT,
  KEY_INPUT_RIGHT,
  KEY_INPUT_Z,
  KEY_INPUT_X,
  KEY_INPUT_C
};

Input::Input():data_(getEmptyMessage()){
  /*
  isUp = false;
  isDown = false;
  isLeft = false;
  isRight = false;
  isButtonA = false;
  isButtonB = false;
  isButtonC = false;
  */
}

Input::~Input() {}

void Input::getKeyInput() {
  /*
  isUp = (CheckHitKey( KEY_INPUT_UP ) == 1);
  isDown = (CheckHitKey( KEY_INPUT_DOWN ) == 1);
  isLeft = (CheckHitKey( KEY_INPUT_LEFT ) == 1);
  isRight = (CheckHitKey( KEY_INPUT_RIGHT ) == 1);
  isButtonA = (CheckHitKey( KEY_INPUT_Z ) == 1);
  isButtonB = (CheckHitKey( KEY_INPUT_X ) == 1);
  isButtonC = (CheckHitKey( KEY_INPUT_C ) == 1);
  */
  if(data_.length() != WATCH_KEYS_NUM){
    data_ = string(WATCH_KEYS_NUM, '0');
  }
  assert(data_.length() == WATCH_KEYS_NUM);
  for(int i = 0; i < WATCH_KEYS_NUM; ++i){
    data_[i] = CheckHitKey(WATCH_KEYS[i]) ? '1' : '0';
  }
  assert(data_.length() == WATCH_KEYS_NUM);
}

bool Input::getKeyStatus_(int keyId)const{
  assert(keyId >= 0 && keyId < WATCH_KEYS_NUM);
  return data_[keyId] == '1';
}

bool Input::up()const{ return getKeyStatus_(0); } // { return isUp; }

bool Input::down()const{ return getKeyStatus_(1); }// {return isDown;}

bool Input::left()const{ return getKeyStatus_(2); } // {return isLeft;}

bool Input::right()const{ return getKeyStatus_(3); } // {return isRight;}

bool Input::buttonA()const{ return getKeyStatus_(4); } // {return isButtonA;}

bool Input::buttonB()const{ return getKeyStatus_(5); } // {return isButtonB;}

bool Input::buttonC()const{ return getKeyStatus_(6); } // {return isButtonC;}

string Input::encode()const{
  return data_;
}

void Input::decode(const string &message){
  assert(data_.length() == message.length());
  data_ = message;
}

string Input::getEmptyMessage(){
  return string(WATCH_KEYS_NUM, '0');
}

void Input::clear(){
  data_ = getEmptyMessage();
}
