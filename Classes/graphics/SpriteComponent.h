#ifndef GRAPHICS_SPRITE_COMPONENT_H
#define GRAPHICS_SPRITE_COMPONENT_H

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
	string _sSpriteName;

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

	void initListeners();

public:
	/**
	 *  
	 *  
	 */
	~SpriteComponent();

	boolean init();

	/**
	 * Ask the GraphicManager the sprite with giving name to set it to the actor
	 */
	static SpriteComponent* create(string sSpriteName, Layer parent);

	/**
	 *  
	 */
	void onEditMove(EventCustom* pEvent);

};

}  // namespace Graphics
#endif
