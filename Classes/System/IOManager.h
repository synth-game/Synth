/*!
 * \file IOManager.h
 * \brief Singleton dealing with the loading and saving of data
 * \author Chupee
 * \date 11/03/2014
 */
#ifndef SYSTEM_I_O_MANAGER_H
#define SYSTEM_I_O_MANAGER_H

#include "cocos2d.h"
#include "core/SynthConfig.h"

namespace synthsystem {

/*! \class IOManager
 * \brief Singleton dealing with the loading and saving of data
 */
class IOManager {

public:

	~IOManager();

	static IOManager* getInstance();

	tinyxml2::XMLDocument* loadXML(std::string filepath);

	void saveXML(char* filepath, core::xml data);

private:
	IOManager();

	/*! \brief The singleton instance */
	static IOManager* _pInstance;


};

}  // namespace synthsystem
#endif
