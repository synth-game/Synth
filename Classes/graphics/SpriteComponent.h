#ifndef GRAPHICS_SPRITE_COMPONENT_H
#define GRAPHICS_SPRITE_COMPONENT_H

#include <string>
#include "cocos2d.h"
#include "Core/SynthComponent.h"

namespace graphics
{
class SpriteComponent : public core::SynthComponent
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
	static SpriteComponent* create(std::string sSpriteName, Layer* pParent);

	/**
	 *
	 */
	void onEditMove(EventCustom* pEvent);

};

}  // namespace graphics
#endif
