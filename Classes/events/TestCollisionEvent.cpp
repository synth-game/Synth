/*!
 * \file TestCollisionEvent.cpp
 * 
 * \author Flora Jullien
 * \date 12/02/2014
 */
#include "TestCollisionEvent.h"

namespace events {

const char* TestCollisionEvent::EVENT_NAME = "test_collision_event";

TestCollisionEvent::TestCollisionEvent(Node* pSource, Point position, Point targetPosition, Size size) 
	: SynthEvent(pSource, EVENT_NAME), _currentPosition(position), _targetPosition(targetPosition), _size(size) {

}

TestCollisionEvent::~TestCollisionEvent() {

}

}  // namespace events
