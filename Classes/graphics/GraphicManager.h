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

	void init(/*core::xml data*/);

	Sprite* createSprite(std::string sSpriteName);

	Animation* getAnimation(AnimationType eAnimationType);

	Animation* getNextAnimation(AnimationType eAnimationType);

	inline SpriteBatchNode* getBatchNode() { return _pBatchNode; }

	inline SpriteFrameCache* getFrameCache() { return _pFrameCache; }

	bool isLoopAnimation(std::string sAnimName);

private:
	/*
	 * Methods
	 */
	Animation* __createAnimation(std::vector<std::string> aFrames);

	/*! \brief Constructor */
	GraphicManager();

	/*
	 * Members
	 */
	
	/*! \brief The singleton instance */
	static GraphicManager* _pInstance;

	/*! \brief The cache of the images (takes the plist file) */
	SpriteFrameCache* _pFrameCache;

	/*! \brief The batch node of the animation (takes the pvr file) */
	SpriteBatchNode* _pBatchNode;

	/*! \brief All the static sprite of the game */
	std::vector<Sprite*> _staticSprites;

	/*! \brief All the animations of the game */
	std::map<AnimationType, Animation*> _animations;

};

}  // namespace graphics
#endif
