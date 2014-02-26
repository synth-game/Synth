#include "NodeOwnerComponent.h"

namespace game
{
char* NodeOwnerComponent::COMPONENT_TYPE;

NodeOwnerComponent::NodeOwnerComponent()
{
}

NodeOwnerComponent::~NodeOwnerComponent()
{
}

bool NodeOwnerComponent::init()
{
	return 0;
}

NodeOwnerComponent* NodeOwnerComponent::create(Node* pOwnedNode)
{
	return 0;
}

Node* NodeOwnerComponent::getOwnedNode()
{
	return nullptr;
}

void NodeOwnerComponent::setOwnedNode(Node* pOwnedNode)
{
}

void NodeOwnerComponent::initListeners()
{
}

void NodeOwnerComponent::onToggleLightEvent(EventCustom* pEvent)
{
}

void NodeOwnerComponent::onChangeNodeOwnerEvent(EventCustom* pEvent)
{
}
}  // namespace game
