/*!
 * \file EnterLightEvent.h
 * \brief Event to signal the source change color lighting
 * \author Jijidici
 * \date 11/03/2014
 */
#ifndef EVENTS_ENTER_LIGHT_EVENT_H
#define EVENTS_ENTER_LIGHT_EVENT_H

#include "cocos2d.h"
#include "events/SynthEvent.h"

USING_NS_CC;

namespace events {
/*! \class EnterLightEvent
 * \brief Event to signal the source change color lighting
 */
class EnterLightEvent : public SynthEvent {
public:
	/*! \brief Constructor */
	EnterLightEvent(Node* pSource, Color4B lightingColor);
	/*! \brief Destructor */
	~EnterLightEvent();

	inline Color4B getLightingColor() { return _lightingColor; }

	static const char* EVENT_NAME;

private:
	Color4B _lightingColor;

};

}  // namespace events
#endif
