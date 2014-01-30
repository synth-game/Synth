/* *****************************************************
 *		SynthActor.cpp - @ Xochitl Florimont - 30/01/14
 ***************************************************** */

#include "SynthActor.h"

int SynthActor::_iActorCount = 0;

SynthActor::SynthActor()
	: Node(), _iActorID(_iActorCount++){
	
}

SynthActor::~SynthActor() {

}