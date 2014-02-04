#ifndef GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H

#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Graphics/AnimatedSpriteComponent.h"

namespace Graphics
{
class HeroAnimatedSpriteComponent : public AnimatedSpriteComponent
{
private:
	Physics::EventListenerCustom* pChangePositionEventListener;

	Physics::EventListenerCustom* pEditMoveEventListener;

	Physics::EventListenerCustom* pJumpEventListener;

	Physics::EventListenerCustom* pInterruptMoveEventListener;

	Physics::EventListenerCustom* pChangeNodeOwnerEventListener;

	Physics::EventListenerCustom* pToggleLightEventListener;

	Physics::EventListenerCustom* pDeathEventListener;

	Physics::EventListenerCustom* pWinEventListener;

	Physics::EventListenerCustom* pResetLevelEventListener;


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

}  // namespace Graphics
#endif
