/* *****************************************************
 *		SynthComponent.h - @ Tom Duchêne - 30/01/14
 ***************************************************** */

#ifndef __SYNTH_COMPONENT_H__
#define __SYNTH_COMPONENT_H__

#include "cocos2d.h"

USING_NS_CC;

class SynthComponent : Component {

public:
	SynthComponent();
	~SynthComponent();
	virtual bool init(const char* sComponentType);

protected:
	virtual void initListeners() = 0;


};

#endif // __SYNTH_COMPONENT_H__