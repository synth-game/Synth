/* *****************************************************
 *      GeometryComponent.cpp - @ Flora Jullien - 30/01/14
 ***************************************************** */

#include "GeometryComponent.h"

namespace Physics
{

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
    : SynthComponent() {

}

GeometryComponent::~GeometryComponent()
{
}

bool GeometryComponent::init() {
    return SynthComponent::init(GeometryComponent::COMPONENT_TYPE);
}

GeometryComponent* GeometryComponent::create(Point position) {
    GeometryComponent* pRet = new GeometryComponent();
    if (pRet != nullptr && pRet->init()) {
        pRet->autorelease();
        pRet->_position = position;
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

Point GeometryComponent::getPosition()
{
	return 0;
}

Size GeometryComponent::getSize()
{
	return 0;
}

float GeometryComponent::getRotationAngle()
{
	return 0;
}

Point GeometryComponent::getAnchorPoint()
{
	return 0;
}

void GeometryComponent::setPosition(Point position)
{
}

void GeometryComponent::setSize(Size size)
{
}

void GeometryComponent::setRotationAngle(float fRotationAngle)
{
}

void GeometryComponent::setAnchorPoint(Point anchorPoint)
{
}

void GeometryComponent::initListeners()
{
}

void GeometryComponent::onChangePosition(EventCustom* pEvent)
{
}
}  // namespace Physics
