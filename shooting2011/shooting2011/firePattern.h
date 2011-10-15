#ifndef __FIREPATTERN_H__
#define __FIREPATTERN_H__

class MovingObject;

class FirePattern{
private:
	virtual bool isFire()=0;
public:
	virtual void action(MovingObject *self)=0;
	virtual ~FirePattern(){}
};

class FirePatternEnemy : public FirePattern{
	vector<int> frames;
	vector<vector<MovePattern *> > vvmp;
	int maxFrame;
	bool loop;
	int curFrame;
	int index;
	bool isFire();
public:
	FirePatternEnemy(const vector<int> &fs,const vector<vector<MovePattern *> > &_vvmp,int _maxFrame,bool _loop);
	void action(MovingObject *self);
	~FirePatternEnemy();
};

class FirePatternHero : public FirePattern{
private:
	bool isFire();
public:
	FirePatternHero(int _interval,int _heroId,int _shotType);
	void action(MovingObject *self);
	~FirePatternHero();

	int shotType;
	int interval;
	int curFrame;
	int heroId;
	bool keyPushFlag;
};

class FirePatternNone : public FirePattern{
private:
	bool isFire();
public:
	FirePatternNone();
	
	void action(MovingObject *self);
	~FirePatternNone();
};
#endif