#include "IOManager.h"

namespace synthsystem
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

core::xml IOManager::loadXML(char* filepath)
{
	core::xml fakeXml;
	return fakeXml;
}

void IOManager::saveXML(char* filepath, core::xml data)
{
}
}  // namespace synthsystem
