/* *****************************************************
 *		SynthActor.h - @ Xochitl Florimont - 30/01/14
 ***************************************************** */

#ifndef __SYNTH_ACTOR_H__
#define __SYNTH_ACTOR_H__

#include "cocos2d.h"

USING_NS_CC;

class SynthActor : public Node {

public:
	SynthActor();
	~SynthActor();
	inline int getActorID() { return _iActorID; }

	static int _iActorCount;

protected:
	int _iActorID;

};
#endif // __SYNTH_ACTOR_H__