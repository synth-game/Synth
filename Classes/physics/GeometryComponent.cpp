/* *****************************************************
 *		GeometryComponent.cpp - @ Flora Jullien - 30/01/14
 ***************************************************** */

#include "GeometryComponent.h"

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
	: SynthComponent() {

}

GeometryComponent::~GeometryComponent() {

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

void GeometryComponent::initListeners() {

}