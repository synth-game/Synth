#ifndef CORE_SYNTH_COMPONENT_H
#define CORE_SYNTH_COMPONENT_H

#include "cocos2d.h"

USING_NS_CC;

namespace core
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

}  // namespace core
#endif
