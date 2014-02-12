/*!
 * \file GeometryComponent.h
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "GeometryComponent.h"

namespace physics
{

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
    : SynthComponent() {

}

GeometryComponent::~GeometryComponent() {
}

bool GeometryComponent::init() {
	return false;
}

GeometryComponent* GeometryComponent::create(Point position, Size size, float fRotationAngle, Point anchorPoint) {
	return nullptr;
}

Point GeometryComponent::getPosition() {
	return Point::ZERO;
}

Size GeometryComponent::getSize() {
	return Size::ZERO;
}

float GeometryComponent::getRotationAngle() {
	return 0.f;
}

Point GeometryComponent::getAnchorPoint() {
	return Point::ZERO;
}

void GeometryComponent::setPosition(Point position) {
}

void GeometryComponent::setSize(Size size) {
}

void GeometryComponent::setRotationAngle(float fRotationAngle) {

}

void GeometryComponent::setAnchorPoint(Point anchorPoint) {
}

void GeometryComponent::initListeners() {
}

void GeometryComponent::onChangePosition(EventCustom* pEvent) {
}


}  // namespace physics
