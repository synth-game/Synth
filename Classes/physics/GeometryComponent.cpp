#include "GeometryComponent.h"

namespace Physics
{
char* GeometryComponent::COMPONENT_TYPE;

GeometryComponent::GeometryComponent()
{
}

GeometryComponent::~GeometryComponent()
{
}

GeometryComponent* GeometryComponent::create(Point position, Size size, float fRotationAngle, Point anchorPoint)
{
	return 0;
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
