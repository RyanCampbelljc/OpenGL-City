//-----------------------------------------------------------------------------
// File:			CityRenderable.h
// Original Author:	Ryan Campbell
//
// base class for objects that can be rendered in the city
// mostly used for polymorphic reasons
//-----------------------------------------------------------------------------

#pragma once
#include "../wolf/wolf.h"
#include "utility.h"

class CityRenderable
{
public:
	using ptr = std::shared_ptr<CityRenderable>;
	virtual void render(const glm::mat4& proj, const glm::mat4& view) const = 0;
};
