/* *****************************************************
 *      SynthActor.h - @ Jijidici - 09/02/14
 ***************************************************** */
#ifndef CORE_SYNTH_ACTOR_H
#define CORE_SYNTH_ACTOR_H

#include "cocos2d.h"

USING_NS_CC;

namespace core
{
class SynthActor : public Node
{
private:
	static int _iActorCount;

	std::string _sTag;

	Node node;

protected:
	int _iActorID;


public:
	/**
	 * Increment the actor count. Init actorID
	 *
	 *
	 *
	 *
	 */
	SynthActor(std::string sTag);

	/**
	 *
	 */
	int getActorID();

	std::string getTag();

};

}  // namespace core
#endif
