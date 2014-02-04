/* *****************************************************
 * SynthEvent.h - @ Flora Jullien - 4/02/14
 ***************************************************** */

#ifndef __SYNTH_EVENT_H__
#define __SYNTH_EVENT_H__

#include "cocos2d.h"

USING_NS_CC;

class SynthEvent : public EventCustom {
	
public: 
	SynthEvent(Node* source, const char* eventName);
	~SynthEvent();
	inline Node* getSource() { return _source; }
	
protected:
	Node* _source;

};

#endif //__SYNTH_EVENT_H__