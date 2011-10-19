#ifndef __COMPOSE_H__
#define __COMPOSE_H__

template<class PatternType>
class PatternComposer : public PatternType{
	// PatternType ‚É‚Í MovePattern ‚© FirePattern ‚Ì‚Ý‚ª“ü‚é
	// GraphicPattern ‚à“ü‚ê‚ç‚ê‚é‚æ‚¤‚É‚µ‚½‚¢‚È (ƒ`ƒ‰

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
	pair<double, double> action(double x, double y); // for MovePattern
	void vanishAction(MovingObject*);//for FirePattern
	void action(MovingObject *); // for FirePattern
};

#include "__patternComposer.h"

#endif // __COMPOSE_H__