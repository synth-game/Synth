/*!
 * \file SynthEvent.h
 * \brief Base classe of our events
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef EVENTS_SYNTH_EVENT_H
#define EVENTS_SYNTH_EVENT_H

#include "cocos2d.h"

USING_NS_CC;

/*! \namespace events
 *
 * namespace regrouping our events
 */
namespace events {

/*! \class SynthEvent
 * \brief Base class of our events
 *
 * It inherits of Cocos2d EventCustom object which have a name to distinguish events.
 * It also save the Node which sent the event
 */
class SynthEvent : public EventCustom {
public:
	/*! \brief Deprecated default constructor
	 * \deprecated Constructor 
	 */
	SynthEvent();

	/*! \brief Constructor
	 * \param pSource pointer on Node which sent the event
	 * \param type name of the event
	 */
	SynthEvent(Node* pSource, const char* sEventName);

	/*! \brief Destructor */
	~SynthEvent();

	inline Node* getSource() { return _pSource; }

protected:
	Node* _pSource; /*! \brief pointer on Node which sent the event  */
};

}  // namespace Events
#endif
