//-----------------------------------------------------------------------------
// File:			Utility.h
// Original Author:	Ryan Campbell
// Utility namespace for any other file
// Holds the paths to all the textures
//-----------------------------------------------------------------------------

#pragma once
#include "../wolf/wolf.h"
#include "environment/worldEnvironment.h"
#include <cassert>
#include <cstdlib>
#include <memory>
#include <time.h>
#include <utility>
#include <vector>
namespace Utility
{
using TexturePair = std::pair<std::string, std::string>;
float randomFloat(float min, float max);
int randomInt(int min, int max);
TexturePair randomBuildingTexture();
constexpr const char* const GRASS_TEXTURE = "textures/grass.png";
constexpr const char* const INTERSECTION_TEXTURE = "textures/intersection.png";
constexpr const char* const ROAD_TEXTURE = "textures/road.png";

constexpr const char* const BUILDING_TEXTURE_3 = "textures/Facades_03/Facades_03_basecolor.jpg";
constexpr const char* const BUILDING_TEXTURE_3_SPEC = "textures/Facades_03/Facades_03_glossiness.jpg";
constexpr const char* const BUILDING_TEXTURE_4 = "textures/Facades_06/Facades_06_basecolor.jpg";
constexpr const char* const BUILDING_TEXTURE_4_SPEC = "textures/Facades_06/Facades_06_glossiness.jpg";
constexpr const char* const BUILDING_TEXTURE_5 = "textures/Facades_07/Facades_07_basecolor.jpg";
constexpr const char* const BUILDING_TEXTURE_5_SPEC = "textures/Facades_07/Facades_07_glossiness.jpg";
constexpr const char* const BUILDING_TEXTURE_6 = "textures/Facades_08/Facades_08_basecolor.jpg";
constexpr const char* const BUILDING_TEXTURE_6_SPEC = "textures/Facades_08/Facades_08_glossiness.jpg";

extern std::vector<TexturePair> BuildingTextures;
}; // namespace Utility
