/*!
 * \file IOManager.cpp
 * \brief Singleton dealing with the loading and saving of data
 * \author Chupee
 * \date 11/03/2014
 */
#include "IOManager.h"

namespace synthsystem {

IOManager* IOManager::_pInstance = nullptr;

IOManager::IOManager() {
}

IOManager::~IOManager() {
}

IOManager* IOManager::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new IOManager();
    }
	return _pInstance;
}

tinyxml2::XMLDocument* IOManager::loadXML(std::string filepath) {
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile(filepath.c_str());
	CCASSERT(xmlerror==0, "ERROR WHILE LOADING XML FILE");
	return pXMLFile;
}

bool IOManager::saveXML(std::string filepath, tinyxml2::XMLDocument* file) {
	int xmlerror = file->SaveFile(filepath.c_str());
	CCASSERT(xmlerror==0, "ERROR WHILE SAVING XML FILE");
	return true;
}

}  // namespace synthsystem
