#ifndef SYSTEM_KEY_BINDER_MANAGER_H
#define SYSTEM_KEY_BINDER_MANAGER_H

#include <map>
#include "enumGLFW.h"


#include "System/BindedAction.h"
#include "System/xml.h"

namespace system
{
class KeyBinderManager
{
private:
	std::map<BindedAction,enumGLFW> _keyMap;

	std::map<BindedAction,enumGLFW> _padMap;

	EventListenerCustom* _ pMapKeyEventListener;


private:
	KeyBinderManager();

public:
	/**
	 *
	 */
	~KeyBinderManager();

	static KeyBinderManager* getInstance();

	/**
	 *
	 */
	void init(xml maps);

	/**
	 * Change la touche associé à l'action spécifiée. Tester si touche clavier ou manette.
	 */
	void onMapKey(EventCustom* event);

	/**
	 * Renvoie l'enum correspondant au keycode/padcode envoyé
	 */
	BindedAction getBindedAction(enumGLFW keyCode);

	xml getKeyMapConfig();

};

}  // namespace system
#endif
