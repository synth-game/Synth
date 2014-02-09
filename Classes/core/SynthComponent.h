/*!
 * \file SynthComponent.h
 * \brief Base classe of components in the game
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef CORE_SYNTH_COMPONENT_H
#define CORE_SYNTH_COMPONENT_H

#include "cocos2d.h"

USING_NS_CC;

namespace core {

/*! \class SynthComponent
 * \brief Base abstract class of each of our components
 *
 * It inherits of Cocos2d Component object for using Cocos2d component system
 */
class SynthComponent : public Component {
public:
	/*! \brief Constructor */
	SynthComponent();
	/*! \brief Destructor */
	~SynthComponent();

	/*! \brief Initialize the component with a component name
	 * \param sComponentType component type name
	 * \return true
	 */
	virtual bool init(const char* sComponentType);

protected:
	/*! \brief Abstract method to initialize and add the event listeners. Must be overriden
	 */
	virtual void initListeners() = 0;
};

}  // namespace core
#endif
