#ifndef SYSTEM_I_O_MANAGER_H
#define SYSTEM_I_O_MANAGER_H

class xml;

namespace system
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

}  // namespace system
#endif
