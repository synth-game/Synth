#ifndef SYSTEM_KEY_BINDER_MANAGER_H
#define SYSTEM_KEY_BINDER_MANAGER_H

#include <map>
#include "cocos2d.h"
#include "System/BindedAction.h"
#include "core/SynthConfig.h"

USING_NS_CC;



namespace synthsystem
{
class KeyBinderManager
{
private:
	std::map<BindedAction,int> _keyMap; //TO CHANGE enumGLFW

	std::map<BindedAction,int> _padMap;

	EventListenerCustom* _pMapKeyEventListener;


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
	void init(core::xml maps);

	/**
	 * Change la touche associé à l'action spécifiée. Tester si touche clavier ou manette.
	 */
	void onMapKey(EventCustom* event);

	/**
	 * Renvoie l'enum correspondant au keycode/padcode envoyé
	 */
	BindedAction getBindedAction(int keyCode);

	core::xml getKeyMapConfig();

};

}  // namespace synthsystem
#endif
