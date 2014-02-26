#ifndef SYSTEM_I_O_MANAGER_H
#define SYSTEM_I_O_MANAGER_H

#include "core/SynthConfig.h"

namespace synthsystem
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

	core::xml loadXML(char* filepath);

	void saveXML(char* filepath, core::xml data);

};

}  // namespace synthsystem
#endif
