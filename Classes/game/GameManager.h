/* *****************************************************
 *		GameManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef GAME_GAME_MANAGER_H
#define GAME_GAME_MANAGER_H

#include <vector>
#include <map>
#include "cocos2d.h"
#include "Color4B.h"
#include "Game/Layer.h"
#include "Game/ParallaxNode.h"
#include "Game/LevelSprite.h"
#include "Game/Rect.h"
#include "Game/Event.h"
#include "Graphics/Layer.h"
#include "Core/SynthActor.h"

USING_NS_CC;

namespace Game
{
class GameManager : public Layer
{
private:
	int _iCurrentLevelId;

	/**
	 * collection de SynthActor (hero, firefly, light, lightSwitch, pig?)
	 * Pour les identifier, regarder leur tag
	 */
	vector<SynthActor*> _levelActors;

	Graphics::Layer* _pBackgroundLayer;

	Graphics::Layer* _pIntermediarLayer;

	Graphics::Layer* _pLevelLayer;

	Graphics::Layer* _pSkinningLayer;

	/**
	 * -> component : TextSpriteComponent
	 */
	Layer _pSubtitlesLayer;

	ParallaxNode* _pParallaxManager;

	/**
	 * Peut être une class particulière
	 */
	LevelSprite* _pLevelSprite;

	/**
	 * Ceci est la carte des illuminations:
	 *
	 * C'est un tableau 2D de la taille du LevelSprite (ou de résolution moindre). Chaque case du tableau contient une liste des indices des lumières qui éclairent le pixel correspondant
	 */
	vector<vector<int>> _lightsMap;

	/**
	 * associate trigger zone with a tag (end, voice)
	 */
	map<string,Rect> _triggers;

	float _fTimeSinceLevelStart;


protected:
	/**
	 *
	 */
	GameManager();

	GameManager();

	vector<SynthActor*> getActorByTag(string sTag);

public:
	static GameManager* create();

	virtual bool init(); // redéfinition de la méthode de Cocos2dx

	void loadLevel(int iLevelId);

	void resetLevel();

	/**
	 * This function have to:
	 *  - check triggers
	 *  - test hero's death -> send DeathEvent and resetLevel()
	 *
	 */
	virtual void update(float fDt); // pareil

	/**
	 * Have to handle event :
	 *  - Move Hero
	 *  - Jump Hero
	 *  - Take Firefly
	 *  - Place Firefly
	 *  - Pull LightSwitch
	 */
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	static Color4B getLightColor(Core::SynthActor* pLight);

};

}  // namespace Game
#endif
