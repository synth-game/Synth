#ifndef GAME_PERIODIC_LAUNCHER_COMPONENT_H
#define GAME_PERIODIC_LAUNCHER_COMPONENT_H

#include "Core/SynthComponent.h"

namespace game
{
class PeriodicLauncherComponent : public core::SynthComponent
{
protected:
	float _fPeriod;

	float _fTimeSinceLastLaunch;

public:
	static char* COMPONENT_TYPE;


protected:
	PeriodicLauncherComponent();

	void initListeners();

public:
	/**
	 *
	 */
	~PeriodicLauncherComponent();

	static PeriodicLauncherComponent* create(float fPeriod);

	void update(float fDt);

	float getPeriod();

	void setPeriod(float fPeriod);

};

}  // namespace game
#endif
