#ifndef GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H

#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Graphics/AnimatedSpriteComponent.h"

namespace graphics
{
class HeroAnimatedSpriteComponent : public AnimatedSpriteComponent
{
private:
	EventListenerCustom* pChangePositionEventListener;

	EventListenerCustom* pEditMoveEventListener;

	EventListenerCustom* pJumpEventListener;

	EventListenerCustom* pInterruptMoveEventListener;

	EventListenerCustom* pChangeNodeOwnerEventListener;

	EventListenerCustom* pToggleLightEventListener;

	EventListenerCustom* pDeathEventListener;

	EventListenerCustom* pWinEventListener;

	EventListenerCustom* pResetLevelEventListener;


protected:
	HeroAnimatedSpriteComponent();

	void initListeners();

public:
	~HeroAnimatedSpriteComponent();

	/**
	 * Get the batchnode from the GraphicManager and init with the idl_animation
	 *
	 */
	static HeroAnimatedSpriteComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onEditMove(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	void onChangeNodeOwner(EventCustom* pEvent);

	void onToggleLight(EventCustom* pEvent);

	void onDeath(EventCustom* pEvent);

	void onWin(EventCustom* pEvent);

	void onResetLevel(EventCustom* pEvent);

};

}  // namespace graphics
#endif
