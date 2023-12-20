//-----------------------------------------------------------------------------
// File:			City.cpp
// Original Author:	Ryan Campbell
//
// class to represent the city
//-----------------------------------------------------------------------------
#include "city.h"

// city constructor
City::City(int rows)
	: m_rows(rows)
	, m_dt(0.0f)
{
	m_topLeft = glm::vec2(-m_rows / 2, -m_rows / 2);
	locateDownTown();
	createStructureArray();
	createCityObjectArray();
}

City::~City()
{
}

// renders all the objects in the city(buildings/ground)
void City::render(const Camera& camera) const
{
	for (const auto& c : m_cityObjects)
		c->render(camera.getProjection(), camera.getView());
}

// called when 'r' is pressed and recreates the city randomly
void City::refresh()
{
	m_cityObjects.clear();
	locateDownTown();
	createStructureArray();
	createCityObjectArray();
}

// creates the vector the holds all the objects to be renders in the city
void City::createCityObjectArray()
{
	for (int y = 0; y < m_rows; ++y) {
		for (int x = 0; x < m_rows; ++x) {
			// each grid square is 1x1. position is the center of next grid square to be dealt with
			glm::vec3 position = glm::vec3(m_topLeft.x + 0.5 + x, 0.0f, m_topLeft.y + 0.5 + y);
			if (m_structureArray[y][x] == 0) { // creates a road
				createRoad(y, x, position);
			} else if (m_structureArray[y][x] == 1) {
				if (Utility::randomInt(1, 5) != 1) // creates a basic building
					createBuilding(y, x, position);
				else
					createCuboidBuilding(y, x, position); // creates cuboid building
			}
		}
	}
}

const float maxHeight = 10.0f;
const float minHeight = 4.0f;
// random height for building in a city based on downtown location
// assumes city is centered at origin.
float City::randomHeight(const glm::vec3& pos) const
{
	float distanceToDownTown = glm::length(m_downTown - glm::vec2(pos.x, pos.z));
	// distance to downtown/maxdistance it could be(city diagnol)
	float percent = distanceToDownTown / (2 * glm::length(m_topLeft));
	float height = minHeight + ((1.0f - percent) * (maxHeight - minHeight));
	// height based on distance + or - 1
	return Utility::randomFloat(height - 1.0f, height + 1.0f);
}

// makes sure that an array index is in bound
bool City::indexInRange(int row, int col) const
{
	return row >= 0 && row <= m_rows - 1 && col >= 0 && col <= m_rows - 1;
}

// aligns a building to its adjacent roads if there are any
glm::vec3 City::alignBuildingWithRoad(int row, int col, glm::vec3 pos, float width)
{
	if (indexInRange(row - 1, col) && m_structureArray[row - 1][col] == 0) { // road above
		pos.z -= (1.0f - width) / 2.0f;
	} else if (indexInRange(row + 1, col) && m_structureArray[row + 1][col] == 0) { // road below
		pos.z += (1.0f - width) / 2.0f;
	}
	if (indexInRange(row, col - 1) && m_structureArray[row][col - 1] == 0) { // road left
		pos.x -= (1.0f - width) / 2.0f;
	} else if (indexInRange(row, col + 1) && m_structureArray[row][col + 1] == 0) { // road right
		pos.x += (1.0f - width) / 2.0f;
	}
	return pos;
}

// array if widths that a building can be
// didnt make it completely random becuase sometimes
// they were too close and it looked bad
static const float widths[] = {0.5f, 0.6f, 0.7f, 0.8f, 1.0f};

/**
 * HOW GRID SYSTEM WORKS
 * grid is x by x (currently 24x24)
 * each grid holds 1 building
 * each building is aligned with road or centerd
 */
void City::createBuilding(int row, int col, const glm::vec3& position)
{
	auto b = std::make_shared<BasicBuilding>(Utility::randomBuildingTexture());
	static bool once = true;
	if (once) {
		// only need to register one observer since it only updates static member
		WorldEnvironment::instance().registerObserver(b);
		once = false;
	}
	float randWidth = widths[Utility::randomInt(0, sizeof(widths) / sizeof(float) - 1)];
	b->setScale(glm::vec3(randWidth, randomHeight(position), randWidth));

	// so that the buildings line up with the road instead of centered down each row
	b->setPosition(alignBuildingWithRoad(row, col, position, randWidth));
	m_cityObjects.push_back(b);

	// also create floor
	auto grass = std::make_shared<Rectangle>(Utility::GRASS_TEXTURE);
	grass->setPosition(position);
	m_cityObjects.push_back(grass);
}

// makes a cuboid building
// essentially stacks 3 basic buildings on top of each other
void City::createCuboidBuilding(int x, int z, const glm::vec3& position)
{
	auto tex = Utility::randomBuildingTexture();
	glm::vec3 originalPosition = position;
	float height = randomHeight(position);
	float randWidth = widths[Utility::randomInt(0, sizeof(widths) / sizeof(float) - 1)];
	const float bottomHeight = height / 1.75f;

	auto b = std::make_shared<BasicBuilding>(tex);
	originalPosition = alignBuildingWithRoad(x, z, originalPosition, randWidth);
	b->setPosition(originalPosition);
	glm::vec3 bottomScale = glm::vec3(randWidth, bottomHeight, randWidth);
	b->setScale(bottomScale);

	auto m = std::make_shared<BasicBuilding>(tex);
	originalPosition.y = bottomHeight;
	m->setScale(bottomScale / glm::vec3(1.5, 2, 1.5));
	m->setPosition(originalPosition);

	auto t = std::make_shared<BasicBuilding>(tex);
	originalPosition.y = bottomHeight * 1.5f;
	t->setScale(bottomScale / glm::vec3(2, 4, 2));
	t->setPosition(originalPosition);

	m_cityObjects.push_back(b);
	m_cityObjects.push_back(m);
	m_cityObjects.push_back(t);

	auto grass = std::make_shared<Rectangle>(Utility::GRASS_TEXTURE);
	grass->setPosition(position);
	m_cityObjects.push_back(grass);
}

void City::createRoad(int row, int col, const glm::vec3& position)
{
	std::shared_ptr<Rectangle> road;
	if (indexInRange(row + 1, col + 1)
		&& (m_structureArray[row + 1][col] == 0 && m_structureArray[row][col + 1] == 0)) {
		road = std::make_shared<Rectangle>(Utility::INTERSECTION_TEXTURE);
	} else {
		road = std::make_shared<Rectangle>(Utility::ROAD_TEXTURE);
		if (col != 0 && col < m_rows - 1 && m_structureArray[row][col + 1] != 0
			&& m_structureArray[row][col - 1] != 0) {
			road->setRotation(glm::vec3(0, PI / 2, 0));
		}
	}
	static bool once = true;
	if (once) {
		// only need to register one observer since it only updates static member
		WorldEnvironment::instance().registerObserver(road);
		once = false;
	}
	road->setPosition(position);
	m_cityObjects.push_back(road);
}

// todo there must be a way to make structureArrayRowMaker (templates?)
//  and createStructureArray better. or atleast reuse this function.

// a helper function for create structure array.
// creates 1 row of the city
std::vector<int> structureArrayRowMaker(int end)
{
	std::vector<int> v;
	// number of buildings to now place consecutivley
	int numBuildings = 0;
	// current index in v
	int c = 0;
	while (c < end) {
		if (numBuildings == 0) {
			numBuildings = Utility::randomInt(2, 4);
			if (c != 0) {
				if (c == end - 1) {
					v.push_back(1);
					return v;
				}
				v.push_back(0);
				++c;
				continue;
			}
		}
		++c;
		v.push_back(1);
		--numBuildings;
	}
	return v;
}

// creates the structure array of ints
//  0 = road, 1 = Building
// this array represent the citys blueprint
void City::createStructureArray()
{
	m_structureArray.clear();
	std::vector<int> v;
	int numBuildings = 0;
	int c = 0;
	v = structureArrayRowMaker(m_rows);
	std::vector<int> zeros(m_rows, 0);
	while (c < m_rows) {
		if (numBuildings == 0) {
			numBuildings = Utility::randomInt(2, 4);
			if (c != 0) {
				if (c == m_rows - 1) {
					m_structureArray.push_back(v);
					return;
				}

				m_structureArray.push_back(zeros);
				++c;
				continue;
			}
		}
		++c;
		m_structureArray.push_back(v);
		--numBuildings;
	}
}

// assumes city is centered at origin.
void City::locateDownTown()
{
	m_downTown = glm::vec2(
		Utility::randomFloat(-m_rows / 2.0f, m_rows / 2.0f), Utility::randomFloat(-m_rows / 2.0f, m_rows / 2.0f));
}