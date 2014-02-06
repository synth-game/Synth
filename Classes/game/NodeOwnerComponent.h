#ifndef GAME_NODE_OWNER_COMPONENT_H
#define GAME_NODE_OWNER_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

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

	void onToggleLightEvent(EventCustom* pEvent);

	void onChangeNodeOwnerEvent(EventCustom* pEvent);

public:
	/**
	 *
	 */
	~NodeOwnerComponent();

	bool init();

	static NodeOwnerComponent* create(Node* pOwnedNode);

	Node* getOwnedNode();

	void setOwnedNode(Node* pOwnedNode);

};

}  // namespace game
#endif
