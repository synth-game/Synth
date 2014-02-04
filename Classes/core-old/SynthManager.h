/* *****************************************************
 *		SynthManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef __SYNTH_MANAGER_H__
#define __SYNTH_MANAGER_H__

#include "cocos2d.h"
#include "game/GameManager.h"

class SynthManager {
public:
	SynthManager();
	~SynthManager();

	bool init();

private:
	cocos2d::Scene* _pGameScene;
	GameManager*	_pGameManager;
};

#endif //__SYNTH_MANAGER_H__
