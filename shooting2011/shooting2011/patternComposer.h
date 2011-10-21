#ifndef __COMPOSE_H__
#define __COMPOSE_H__

template<class PatternType>
class PatternComposer : public PatternType, private NonCopyable{
	// PatternTypeが持つべきインターフェースは
	//   void PatternType::action(MovionObject *);

private:
	deque<pair<int, PatternType *> > patterns;
	typename deque<pair<int, PatternType *> >::iterator currentPattern;
	int frameCounter;
	bool isInitialized;
	void init();
	PatternType *getCurrentPattern();
	void countUp();
	bool isFire(){return false;} // atode kesu
public:
	PatternComposer();
	~PatternComposer();
	PatternComposer<PatternType> *add(int frame, PatternType *pattern);
	void action(MovingObject *);
};

template<class PatternType>
class ParallelPatternComposer : public PatternType, private NonCopyable{
private:
	deque<PatternType *> patterns_;
public:
	~ParallelPatternComposer();
	ParallelPatternComposer<PatternType> *add(PatternType *pattern);
	void action(MovingObject *owner);
};

#include "__patternComposer.h"

#endif // __COMPOSE_H__