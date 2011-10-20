
template<class PatternType>
void PatternComposer<PatternType>::init(){
	currentPattern = patterns.begin();
	frameCounter = 0;
}

template<class PatternType>
PatternType *PatternComposer<PatternType>::getCurrentPattern(){
	return currentPattern->second;
}

template<class PatternType>
void PatternComposer<PatternType>::countUp(){
	if(currentPattern->first >= 0 && ++frameCounter >= currentPattern->first){
		frameCounter = 0;
		if(++currentPattern == patterns.end()){
			currentPattern = patterns.begin();
		}
	}
}

template<class PatternType>
PatternComposer<PatternType>::PatternComposer():isInitialized(false){}

template<class PatternType>
PatternComposer<PatternType>::~PatternComposer(){
	for(typename deque<pair<int, PatternType *> >::iterator i = patterns.begin(); i != patterns.end(); ++i){
		delete i->second;
	}
}

template<class PatternType>
PatternComposer<PatternType> *PatternComposer<PatternType>::add(int frame, PatternType *pattern){
	if(frame != 0){
		patterns.push_back(make_pair(frame, pattern));
	}
	return this;
}

template<class PatternType>
void PatternComposer<PatternType>::action(MovingObject *owner){
	if(patterns.empty()){
		return;
	}
	if(!isInitialized){
		init();
		isInitialized = true; // bug fix arai tabunhituyou
	}
	currentPattern->second->action(owner);
	countUp();
}
/*
template<class PatternType>
void PatternComposer<PatternType>::vanishAction(MovingObject *owner){
	if(patterns.empty()){
		return;
	}
	if(!isInitialized){
		init();
		isInitialized = true; // bug fix arai tabunhituyou
	}
	currentPattern->second->vanishAction(owner);
	countUp();
}

//*/
/*
template<class PatternType>
ParallelPatternComposer<PatternType>::~ParallelPatternComposer(){
	for(typename deque<PatternType *>::iterator i = patterns_.begin(); i != patterns_.end(); ++i){
		delete *i;
	}
}
*/
template<class PatternType>
ParallelPatternComposer<PatternType> *ParallelPatternComposer<PatternType>::add(PatternType *pattern){
	patterns_.push_back(pattern);
}

template<class PatternType>
void ParallelPatternComposer<PatternType>::action(MovingObject *owner){
	for(size_t i = 0; i < patterns_.size(); ++i){
		patterns_[i]->action(owner);
	}
}
