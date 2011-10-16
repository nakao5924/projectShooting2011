
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
	for(typename vector<pair<int, PatternType *> >::iterator i = patterns.begin(); i != patterns.end(); ++i){
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
pair<double, double> PatternComposer<PatternType>::action(double x, double y){
	if(patterns.empty()){

		
		return make_pair(x, y);
	}
	if(!isInitialized){
		init();
		isInitialized = true;
	}
	pair<double, double> ret = currentPattern->second->action(x, y);
	countUp();
	return ret;
}

template<class PatternType>
void PatternComposer<PatternType>::action(MovingObject *self){
	if(patterns.empty()){
		return;
	}
	if(!isInitialized){
		init();
	}
	currentPattern->second->action(self);
	countUp();
}
