/* *****************************************************
 *		SynthComponent.h - @ Tom Duchêne - 30/01/14
 ***************************************************** */

#ifndef __CORE_SYNTH_COMPONENT_H__
#define __CORE_SYNTH_COMPONENT_H__

#include "cocos2d.h"

USING_NS_CC;

class SynthComponent : public Component {

public:
	SynthComponent();
	~SynthComponent();
	virtual bool init(const char* sComponentType);

protected:
	virtual void initListeners() = 0;


};

#endif // __CORE_SYNTH_COMPONENT_H__