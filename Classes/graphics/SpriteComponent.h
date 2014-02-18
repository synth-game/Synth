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

	void onEnter(); //Appelée après l'ajout dans le componentContainer par la classe Node (avant le owner n'est pas défini)


	/*
	 * Members
	 */
	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */
	SpriteComponent();
	SpriteComponent(Layer* pParent); 
	SpriteComponent(std::string sSpriteName, Layer* pParent); 

	virtual void initListeners();

	/*
	 * Members
	 */
	std::string _sSpriteName;

	Sprite* _pSprite;

	Layer* _pParent;

	EventListenerCustom* _pEditMoveEventListener;

};

}  // namespace graphics
#endif
