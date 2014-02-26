#include "KeyBinderManager.h"

namespace synthsystem
{



KeyBinderManager::KeyBinderManager()
{
}

KeyBinderManager::~KeyBinderManager()
{
}

KeyBinderManager* KeyBinderManager::getInstance()
{
	return 0;
}

void KeyBinderManager::init(core::xml maps)
{
}

void KeyBinderManager::onMapKey(EventCustom* event)
{
}

BindedAction KeyBinderManager::getBindedAction(int keyCode)
{
	return BindedAction::NO_ACTION;
}

core::xml KeyBinderManager::getKeyMapConfig()
{
	core::xml fakeXml;
	return fakeXml;
}
}  // namespace synthsystem
