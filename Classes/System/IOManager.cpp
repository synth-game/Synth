#include "IOManager.h"

namespace System
{

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

IOManager* IOManager::getInstance()
{
	return 0;
}

xml IOManager::loadXML(char* filepath)
{
	return 0;
}

void IOManager::saveXML(char* filepath, xml data)
{
}
}  // namespace System
