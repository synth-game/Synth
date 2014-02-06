#ifndef SYSTEM_I_O_MANAGER_H
#define SYSTEM_I_O_MANAGER_H

class xml;

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

	xml loadXML(char* filepath);

	void saveXML(char* filepath, xml data);

};

}  // namespace synthsystem
#endif
