/*!
 * \file CollisionEvent.cpp
 * \brief Event send to signal a lateral collision
 * \author Jijidici
 * \date 06/03/2014
 */
#include "CollisionEvent.h"

namespace events {

const char* CollisionEvent::EVENT_NAME = "CollisionEvent";

CollisionEvent::CollisionEvent(Node* pSource)
	: SynthEvent(pSource, EVENT_NAME) {

}
    
CollisionEvent::CollisionEvent(Node* pSource, physics::ECollisionType eCollisionType)
	: SynthEvent(pSource, EVENT_NAME),  _eCollisionType(eCollisionType){
        
}

CollisionEvent::~CollisionEvent() {

}

}  // namespace events
