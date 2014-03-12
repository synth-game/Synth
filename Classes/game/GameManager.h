/*!
 * \file GameManager.h
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef GAME_GAME_MANAGER_H
#define GAME_GAME_MANAGER_H

#include <vector>
#include <stack>
#include <map>
#include "cocos2d.h"
#include "Game/LevelSprite.h"
#include "Core/SynthActor.h"

USING_NS_CC;

/*! \namespace events
 *
 * namespace regrouping gameplay classes
 */
namespace game {

/*! \class GameManager
 * \brief Manager of the entire game
 *
 * It our blob object. 
 * It initializes the level, update SynthActor, etc.
 * It inherites from Cocos2d's Layer to catch keyboard event
 */
class GameManager : public Layer {
public:
	/*! \brief Destructor */
	~GameManager();

	static GameManager* create();
	/*! \brief Initialisation function called in create() method */
	virtual bool init();
	virtual void update(float fDt);

	void loadLevel(/*int iLevelId*/std::string level);
	void clearLevel();
	void resetLevel();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	static Color4B getLightColor(core::SynthActor* pLight);

	inline Layer* getLevelLayer() { return _pLevelLayer; }

	/*void GameManager::onEditMove(EventCustom* event);*/

	core::SynthActor* hero;
	std::vector<core::SynthActor*> _levelActors;
	std::map<std::string,Rect> _triggers;

protected:
	/*! \brief Constructor */
	GameManager();
	std::vector<core::SynthActor*> getActorsByTag(std::string sTag);
	core::SynthActor* getNearActor(core::SynthActor* actor);

	int _iCurrentLevelId;
	float _fTimeSinceLevelStart;
	
	
	LevelSprite* _pLevelSprite;

	Layer* _pBackgroundLayer;
	Layer* _pIntermediarLayer;
	Layer* _pLevelLayer;
	Layer* _pSkinningLayer;
	Layer* _pSubtitlesLayer;
	ParallaxNode* _pParallaxManager;

	std::vector<EventKeyboard::KeyCode> _keyPressedCode;

};

}  // namespace game
#endif
