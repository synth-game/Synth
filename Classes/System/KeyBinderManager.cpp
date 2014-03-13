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

void KeyBinderManager::init()
{
}

void KeyBinderManager::onMapKey(EventCustom* event)
{
}

BindedAction KeyBinderManager::getBindedAction(int keyCode)
{
	return BindedAction::NO_ACTION;
}

tinyxml2::XMLDocument* KeyBinderManager::getKeyMapConfig()
{
	tinyxml2::XMLDocument* fakeXml;
	return fakeXml;
}

}  // namespace synthsystem
