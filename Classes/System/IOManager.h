#ifndef SYSTEM_I_O_MANAGER_H
#define SYSTEM_I_O_MANAGER_H

#include "System/xml.h"

namespace System
{
class IOManager
{
private:
	IOManager();

public:
	/**
	 *  
	 */
	~IOManager();

	static IOManager* getInstance();

	xml loadXML(char* filepath);

	void saveXML(char* filepath, xml data);

};

}  // namespace System
#endif
