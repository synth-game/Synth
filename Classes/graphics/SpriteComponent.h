/*!
 * \file SpriteComponent.h
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 12/02/2014
 */
#ifndef GRAPHICS_SPRITE_COMPONENT_H
#define GRAPHICS_SPRITE_COMPONENT_H

#include <string>
#include "cocos2d.h"
#include "Core/SynthComponent.h"

namespace graphics {

/*! \class SpriteComponent
 * \brief Add a sprite image (fixed) to the actor.
 *
 * 
 */
class SpriteComponent : public core::SynthComponent {

public:
	/*
	 * Methods
	 */
	~SpriteComponent();

	virtual bool init();

	/**
	 * Ask the GraphicManager the sprite with giving name to set it to the actor
	 */
	static SpriteComponent* create(std::string sSpriteName, Layer* pParent);

	void onEditMove(EventCustom* pEvent);

	/*
	 * Members
	 */
	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */
	SpriteComponent();

	virtual void initListeners();

	/*
	 * Members
	 */
	std::string _sSpriteName;

	Sprite* _pSprite;

	Layer* _pParent;

	EventCustom* _pEditMoveEventListener;

};

}  // namespace graphics
#endif
