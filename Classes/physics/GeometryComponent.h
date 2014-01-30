/* *****************************************************
 *		GeometryComponent.h - @ Flora Jullien - 30/01/14
 ***************************************************** */

#ifndef __GEOMETRY_COMPONENT_H__
#define __GEOMETRY_COMPONENT_H__

#include "cocos2d.h"
#include "core/SynthComponent.h"

USING_NS_CC;

class GeometryComponent : public SynthComponent {

public:
	~GeometryComponent();
	virtual bool init();
	static GeometryComponent* create(Point position);

	inline Point getPosition() { return _position; }
	inline void setPosition(Point position) { _position = position; }

	static const char* COMPONENT_TYPE;

protected:
	GeometryComponent();
	virtual void initListeners();
	
	Point _position;

};

#endif // __GEOMETRY_COMPONENT_H__