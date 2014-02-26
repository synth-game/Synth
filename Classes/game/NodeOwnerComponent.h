/*!
 * \file NodeOwnerComponent.h
 * \brief Component that makes the actor the owner of an other actor.
 * \author Chupee
 * \date 26/02/2014
 */
#ifndef GAME_NODE_OWNER_COMPONENT_H
#define GAME_NODE_OWNER_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace game {

/*! \class GraphicManager
 * \brief Component that makes the actor the owner of an other actor.
 *
 */
class NodeOwnerComponent : public core::SynthComponent {

public:
	/*
	 * Methods
	 */
	/*! \brief Desctructor */
	~NodeOwnerComponent();

	/*! \brief Init the component */
	bool init();

	/*! \brief Create the component */
	static NodeOwnerComponent* create(Node* pOwnedNode);

	/*! \brief  */
	inline Node* getOwnedNode() { return _pOwnedNode; };

	/*! \brief Set the owned node */
	inline void setOwnedNode(Node* pOwnedNode) { _pOwnedNode = pOwnedNode; };

	/*
	 * Members
	 */

	/*! \brief The component type */
	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	NodeOwnerComponent();

	/*! \brief  */
	void initListeners();

	/*! \brief  */
	void onToggleLight(EventCustom* pEvent);

	/*! \brief  */
	void onChangeNodeOwner(EventCustom* pEvent);

	/*
	 * Members
	 */

	/*! \brief The node that is owned by the actor */
	Node* _pOwnedNode;


private:
	/*
	 * Members
	 */

	/*! \brief  */
	EventListenerCustom* _pToggleLightEventListener;

	/*! \brief  */
	EventListenerCustom* _pChangeNodeOwnerEventListener;
};

}  // namespace game
#endif
