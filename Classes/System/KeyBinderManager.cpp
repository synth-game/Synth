#include "KeyBinderManager.h"

namespace system
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

void KeyBinderManager::init(xml maps)
{
}

void KeyBinderManager::onMapKey(EventCustom* event)
{
}

BindedAction KeyBinderManager::getBindedAction(enumGLFW keyCode)
{
	return 0;
}

xml KeyBinderManager::getKeyMapConfig()
{
	return 0;
}
}  // namespace system
