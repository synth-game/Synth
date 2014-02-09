/*!
 * \file SynthActor.h
 * \brief Base classe of Synth game objects
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef CORE_SYNTH_ACTOR_H
#define CORE_SYNTH_ACTOR_H

#include <string>
#include "cocos2d.h"

USING_NS_CC;

/*! \namespace core
 *
 * namespace of all essential and mother classes
 */
namespace core {

/*! \class SynthActor
 * \brief Base object of Synth
 *
 * It inherits of Cocos2d Node object. Each SynthActor have a unique ID and a tag
 */
class SynthActor : public Node {
public:
	/*! \brief Constructor
	 * 
	 * Constructor which initializes the SynthActor tag
	 * \param sTag : initialization tag
	 */
	SynthActor(std::string sTag);

	/*! \brief Default destructor
	 */
	~SynthActor();

	/*! \brief Get SynthActor's identifiant
	 */
	inline int getActorID() { return _iActorID; }

	/*! \brief Get SynthActor's tag
	 */
	inline std::string getActorTag() { return _sTag; }
	
	static int _iActorCount; /*! counter of every SynthActor. It is automatically incremented */

protected:
	int _iActorID; /*! \brief unique identifiant */
	std::string _sTag; /*! \brief tag which describes SynthActor's type */
};

}  // namespace core
#endif
