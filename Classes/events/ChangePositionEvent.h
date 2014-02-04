/* *****************************************************
 * ChangePositionEvent.h - @ Flora Jullien - 4/02/14
 ***************************************************** */

#ifndef __CHANGE_POSITION_EVENT_H__
#define __CHANGE_POSITION_EVENT_H__

#include "cocos2d.h"
#include "events/SynthEvent.h"

USING_NS_CC;

class ChangePositionEvent : public SynthEvent {

public:
	ChangePositionEvent(Node* source);
	~ChangePositionEvent();
	inline Point getCurrentPosition() { return _currentPosition; }
	inline void setCurrentPosition( Point position ) { _currentPosition = position; }

	static const char* EVENT_NAME;

private:
	Point _currentPosition;
};

#endif //__CHANGE_POSITION_EVENT_H__