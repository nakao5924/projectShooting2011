#ifndef __FIREPATTERN_H__
#define __FIREPATTERN_H__

class MovingObject;

class FirePattern{
public:
	virtual bool isFire()=0;
	virtual void action(MovingObject *self)=0;
	virtual ~FirePattern(){};
};

class FirePatternEnemy : public FirePattern{
	vector<int> frames;
	vector<vector<MovePattern *> > vvmp;
	int maxFrame;
	bool loop;
	int curFrame;
	int index;
public:
	FirePatternEnemy(const vector<int> &fs,const vector<vector<MovePattern *> > &_vvmp,int _maxFrame,bool _loop);
	bool isFire();
	void action(MovingObject *self);
	~FirePatternEnemy();
};

class FirePatternHero : public FirePattern{
public:
	FirePatternHero(const vector<MovePattern *> &_vm,int _interval);
	bool isFire();
	vector<MovePattern *> vm;
	void action(MovingObject *self);
	~FirePatternHero();

	int interval;
	int curFrame;
	int heroId;
	bool keyPushFlag;
};

class FirePatternNone : public FirePattern{
public:
	FirePatternNone();
	bool isFire();
	
	void action(MovingObject *self);
	~FirePatternNone();
};
#endif