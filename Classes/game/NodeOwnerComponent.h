#ifndef GAME_NODE_OWNER_COMPONENT_H
#define GAME_NODE_OWNER_COMPONENT_H

#include "Node.h"
#include "Physics/EventListenerCustom.h"
#include "Core/SynthComponent.h"

namespace game
{
class NodeOwnerComponent : public core::SynthComponent
{
private:
	EventListenerCustom* _pToggleLightListener;

	EventListenerCustom* _pChangeNodeOwnerListener;


protected:
	Node* _pOwnedNode;


public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	NodeOwnerComponent();

	void initListeners();

	void onToggleLightEvent : EventCustom*)();

	void onChangeNodeOwnerEvent : EventCustom*)();

public:
	/**
	 *
	 */
	~NodeOwnerComponent();

	bool init();

	static NodeOwnerComponent* create(Node* pOwnedNode);

	Node getOwnedNode();

	void setOwnedNode(Node* pOwnedNode);

};

}  // namespace game
#endif
