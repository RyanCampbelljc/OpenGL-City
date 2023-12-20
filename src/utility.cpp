//-----------------------------------------------------------------------------
// File:			Utility.cpp
// Original Author:	Ryan Campbell
// see header file
//-----------------------------------------------------------------------------

#include "utility.h"

namespace Utility
{
std::vector<TexturePair> BuildingTextures = {
	{Utility::BUILDING_TEXTURE_4, Utility::BUILDING_TEXTURE_4_SPEC},
	{Utility::BUILDING_TEXTURE_5, Utility::BUILDING_TEXTURE_5_SPEC},
	{Utility::BUILDING_TEXTURE_6, Utility::BUILDING_TEXTURE_6_SPEC},
	{Utility::BUILDING_TEXTURE_3, Utility::BUILDING_TEXTURE_3_SPEC}};

TexturePair randomBuildingTexture()
{
	int n = randomInt(0, BuildingTextures.size() - 1);
	return BuildingTextures[n];
}

// random seed for random function
static void initSeed()
{
	static bool once = true;
	if (once) {
		srand((unsigned int)time(NULL));
		once = false;
	}
}

// returns random float inclusive
float randomFloat(float min, float max)
{
	initSeed();
	if (max < min) {
		return min;
		puts("max was less than min in utility::randomFloat()");
	}
	float somePercentage = (float)rand() / (float)RAND_MAX;
	return min + (somePercentage * (max - min));
}

// returns random in inclusive
int randomInt(int min, int max)
{
	initSeed();
	if (max < min) {
		return min;
	}
	return (rand() % (max - min + 1)) + min;
}

} // namespace Utility