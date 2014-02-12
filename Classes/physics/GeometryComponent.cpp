/*!
 * \file GeometryComponent.h
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "GeometryComponent.h"

namespace physics {

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
    : SynthComponent() {
}

GeometryComponent::~GeometryComponent() {
}

bool GeometryComponent::init() {
	SynthComponent::init(GeometryComponent::COMPONENT_TYPE);
	return true;
}

GeometryComponent* GeometryComponent::create(Point position, Size size, float fRotationAngle, Point anchorPoint) {
	GeometryComponent* pRet = new GeometryComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_position =			position;
		pRet->_size =				size;
		pRet->_fRotationAngle =		fRotationAngle;
		pRet->_anchorPoint =		anchorPoint;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void GeometryComponent::initListeners() {
	//_pChangePositionListener = cocos2d::EventListenerCustom::create(ChangePositionEvent::eventName, CC_CALLBACK_1(GeometryComponent::onChangePosition, this));
}

void GeometryComponent::onChangePosition(EventCustom* pEvent) {
}


}  // namespace physics
