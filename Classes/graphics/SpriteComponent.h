/* *****************************************************
 *		SpriteComponent.h - @ Damaris Ankou - 30/01/14
 ***************************************************** */

#ifndef GRAPHICS_SPRITE_COMPONENT_H
#define GRAPHICS_SPRITE_COMPONENT_H

#include <string>
#include "cocos2d.h"
#include "Component.h"
#include "EventCustom.h"
#include "Graphics/Sprite.h"
#include "Graphics/Layer.h"
#include "Core/SynthComponent.h"

namespace Graphics
{
class SpriteComponent : public Component, public Core::SynthComponent
{
protected:
	std::string _sSpriteName;

	Sprite* _pSprite;

	Layer* _pParent;

	EventCustom* _pEditMoveEventListener;

public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	SpriteComponent();

	virtual void initListeners();

public:
	/**
	 *
	 *
	 */
	~SpriteComponent();

	virtual bool init();

	/**
	 * Ask the GraphicManager the sprite with giving name to set it to the actor
	 */
	static SpriteComponent* create(std::string sSpriteName, Layer parent);

	/**
	 *
	 */
	void onEditMove(EventCustom* pEvent);

};

}  // namespace Graphics
#endif
