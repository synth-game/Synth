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
#include "core/ActorType.h"

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
	 * \param eType : type of the actor
	 */
	SynthActor(ActorType eType);

	/*! \brief Destructor */
	~SynthActor();

	/*! \brief compare actor IDs */
	inline bool operator==(SynthActor other) { return _iActorID == other.getActorID(); }

	/*! \brief Get SynthActor's identifiant
	 */
	inline int getActorID() { return _iActorID; }

	/*! \brief Get SynthActor's type
	 */
	inline ActorType getActorType() { return _eType; }

	bool isFirefly();
	
	static int _iActorCount; /*!< counter of every SynthActor. It is automatically incremented */

protected:
	int _iActorID; /*! \brief unique identifiant */
	ActorType _eType; /*! \brief enum which describes SynthActor's type */
};

}  // namespace core
#endif
