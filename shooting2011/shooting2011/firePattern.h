#ifndef __FIREPATTERN_H__
#define __FIREPATTERN_H__

class MovingObject;

class FirePattern{
private:
	virtual bool isFire() = 0;
public:
	virtual void action(MovingObject *owner) = 0;
	virtual ~FirePattern(){}
};

class FirePatternAllRangeTimeRag : public FirePattern{
	double dtheta,curTheta;
	double v;
	int interval;
	int curFrame;
	bool isFire();
public:
	FirePatternAllRangeTimeRag(double _dtheta,double _startTheta,double _v,int _interval);
	void action(MovingObject *owner);
	~FirePatternAllRangeTimeRag();
};

class FirePatternHero : public FirePattern{
private:
	bool isFire();
public:
	FirePatternHero(int _interval,int _heroId,int _shotType);
	void action(MovingObject *owner);
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
	
	void action(MovingObject *owner);
	~FirePatternNone();
};
#endif