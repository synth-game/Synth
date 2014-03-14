/*!
 * \file GameManager.h
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef GAME_GAME_MANAGER_H
#define GAME_GAME_MANAGER_H

#include <vector>
#include <string>
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
	void nextLevel();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	static Color4B getLightColor(core::SynthActor* pLight);

	inline LevelSprite* getLevelSprite() { return _pLevelSprite; }
	inline Layer* getLevelLayer() { return _pLevelLayer; }
	inline int getCurrentLevelIndex() { return _iCurrentLevelId; }
	
	std::vector<core::SynthActor*> getActorsByType(core::ActorType type);

	bool bResetRequested;
	bool bNextRequested;

	/*void GameManager::onEditMove(EventCustom* event);*/

protected:
	/*! \brief Constructor */
	GameManager();
	core::SynthActor* getNearActor(core::SynthActor* actor);
	core::SynthActor* getNearLightSwitch(core::SynthActor* actor);

	void onEnterLight(EventCustom* pEvent);

	int _iCurrentLevelId;
	float _fTimeSinceLevelStart;
	std::vector<std::string> _levelsName;
	std::vector<core::SynthActor*> _levelActors;
	std::map<std::string,Rect> _triggers;

	LevelSprite* _pLevelSprite;

	Layer* _pBackgroundLayer;
	Layer* _pIntermediarLayer;
	Layer* _pLevelLayer;
	Layer* _pSkinningLayer;
	Layer* _pSubtitlesLayer;
	ParallaxNode* _pParallaxManager;

	EventListenerCustom* _pEnterLightListener;

	std::vector<EventKeyboard::KeyCode> _keyPressedCode;

	int stepsSoundId;

};

}  // namespace game
#endif
