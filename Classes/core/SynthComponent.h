/* *****************************************************
 *      SynthComponent.h - @ Tom Duchêne - 30/01/14
 ***************************************************** */

#ifndef CORE_SYNTH_COMPONENT_H
#define CORE_SYNTH_COMPONENT_H

#include "cocos2d.h"

USING_NS_CC;

namespace Core
{
class SynthComponent : public Component
{
private:
	Component component;

protected:
	virtual void initListeners()=0;

public:
	/**
	 *
	 */
	~SynthComponent();

	virtual bool init(const char* componentType);

};

}  // namespace Core
#endif
