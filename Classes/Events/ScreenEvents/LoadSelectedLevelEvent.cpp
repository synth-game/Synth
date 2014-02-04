#include "LoadSelectedLevelEvent.h"

namespace Events
{
namespace ScreenEvents
{
char* LoadSelectedLevelEvent::sEventName;

LoadSelectedLevelEvent::LoadSelectedLevelEvent()
{
}

LoadSelectedLevelEvent::~LoadSelectedLevelEvent()
{
}

int LoadSelectedLevelEvent::getLevel()
{
	return 0;
}

void LoadSelectedLevelEvent::setLevel(int level)
{
}
}  // namespace ScreenEvents
}  // namespace Events
