/*!
 * \file GraphicManager.h
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 * \author Chupee
 * \date 12/02/2014
 */
#ifndef GRAPHICS_GRAPHIC_MANAGER_H
#define GRAPHICS_GRAPHIC_MANAGER_H

#include <vector>
#include <map>
#include "cocos2d.h"
#include "core/SynthActor.h"
#include "core/ActorType.h"
#include "core/SynthConfig.h"
#include "graphics/AnimationType.h"

USING_NS_CC;



namespace graphics {

/*! \class GraphicManager
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 *
 * It inherits of Cocos2d Component object for using Cocos2d component system
 */
class GraphicManager {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~GraphicManager();

	/*! \brief Get the singleton instance _pInstance */
	static GraphicManager* getInstance();

	void init(core::xml data);

	Sprite* createSprite(std::string sSpriteName);

	Animation* getAnimation(AnimationType eAnimationType, SpriteFrameCache* pFrameCache);

	Animation* getNextAnimation(AnimationType eAnimationType);

	SpriteBatchNode* getBatchNode(core::ActorType eType);

	SpriteFrameCache* getFrameCache(core::ActorType eType);

	bool isLoopAnimation(std::string sAnimName);

private:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	GraphicManager();

	/*
	 * Members
	 */
	
	/*! \brief The singleton instance */
	static GraphicManager* _pInstance;

	std::vector<Sprite*> _staticSprites;

	std::map<AnimationType, Animation*> _animations;

};

}  // namespace graphics
#endif
