//-----------------------------------------------------------------------------
// File:			City.h
// Original Author:	Ryan Campbell
//
// class to represent the city
//-----------------------------------------------------------------------------
#pragma once
#include "../samplefw/Sphere.h"
#include "../wolf/wolf.h"
#include "basicBuilding.h"
#include "camera.h"
#include "rectangle.h"
#include "utility.h"
#include <vector>

class City
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	City(int rows);
	~City();

	void render(const Camera& camera) const;
	void refresh();
	//------------------------------------

private:
	//------------------------------------
	// PRIVATE MEMBERS
	//------------------------------------
	const int m_rows;
	float m_dt;
	glm::vec2 m_downTown;
	glm::vec2 m_topLeft;
	std::vector<CityRenderable::ptr> m_cityObjects;
	std::vector<std::vector<int>> m_structureArray;

	void createCityObjectArray();
	void createBuilding(int x, int z, const glm::vec3& position);
	void createCuboidBuilding(int x, int z, const glm::vec3& position);
	// param not const as position is modified
	glm::vec3 alignBuildingWithRoad(int x, int z, glm::vec3 pos, float width);
	void createRoad(int x, int z, const glm::vec3& position);
	void createStructureArray();
	void locateDownTown();
	float randomHeight(const glm::vec3& pos) const;
	bool indexInRange(int row, int col) const;
	//--------------------------------------
};