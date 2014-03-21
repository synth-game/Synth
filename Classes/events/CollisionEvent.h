/*!
 * \file CollisionEvent.h
 * \brief Event send to signal a lateral collision
 * \author Jijidici
 * \date 06/03/2014
 */
#ifndef EVENTS_COLLISION_EVENT_H
#define EVENTS_COLLISION_EVENT_H

#include "cocos2d.h"
#include "events/SynthEvent.h"
#include "physics/CollisionType.h"

USING_NS_CC;

namespace events {
/*! \class CollisionEvent
 * \brief Event send to signal a lateral collision
 */
class CollisionEvent : public SynthEvent {

protected:
    physics::ECollisionType _eCollisionType;
    
public:
	/*! \brief Constructor */
	CollisionEvent(Node* pSource);
    
    CollisionEvent(Node* pSource, physics::ECollisionType eCollisionType);
    
	/*! \brief Destructor */
	~CollisionEvent();
    
    inline physics::ECollisionType getCollisionType() { return _eCollisionType; };

	static const char* EVENT_NAME;

};

}  // namespace events
#endif //EVENTS_COLLISION_EVENT_H
