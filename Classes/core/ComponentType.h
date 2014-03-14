/*!
 * \file ComponentType.h
 * \brief enum for each component type
 * \author Xopi
 * \date 26/02/2014
 */
#ifndef CORE_COMPONENT_TYPE_H
#define CORE_COMPONENT_TYPE_H

namespace core {
typedef enum {
	GEOMETRY,
	MOVEMENT,
	FOLLOWMOVEMENT,
	COLLISION,
	SPRITE,
	HEROANIMATEDSPRITE,
	FIREFLYANIMATEDSPRITE,
	NODEOWNER,
	LIGHTATTR,
	HEROSOUND,
	FIREFLYSOUND,
	SWITCHABLE
} ComponentType;

}  // namespace core
#endif
