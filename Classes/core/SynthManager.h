/* *****************************************************
 *		SynthManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef __SYNTH_MANAGER_H__
#define __SYNTH_MANAGER_H__

#include "cocos2d.h"

class SynthManager {
public:
	SynthManager();
	~SynthManager();

	void init();

private:
	cocos2d::Scene* _pGameScene;
};

#endif //__SYNTH_MANAGER_H__
