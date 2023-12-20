/**
 * Singleton to hold world environment variables and can be observed.
 * Notify observers every frame when updated
 * observers can then decide what to do
 * environmental variables often needed in shaders
 * HOW TO USE
 * since the materials for building and rectangle are static only 1 instance of each needs to be observed
 * If more classes are made they will need to be added
 * Samplecity (basically the world) updates this class
 */
#pragma once
#include "observable.h"

class WorldEnvironment : public Observable
{
public:
	void notifyObservers() const override;

	static WorldEnvironment& instance()
	{
		static WorldEnvironment instance;
		return instance;
	}

	glm::vec3 getSunPosition();
	glm::vec3 getSunDirection();
	glm::vec3 getSkyColor();
	glm::vec3 getCamPos();
	void setCamPos(glm::vec3 pos);
	void update(float dt);

	static const float timeScale;
	static const float timeInDay;

private:
	WorldEnvironment()
		: m_sunStartPos(glm::vec3(0, 250, 0))
		, m_time(timeInDay / 2)
		, m_dt(0)
	{
	}
	glm::vec3 m_sunPosition;
	glm::vec3 m_skyColor;
	glm::vec3 m_camPosition;
	const glm::vec3 m_sunStartPos;
	float m_time;
	float m_dt;
	void updateSunPos();
	void updateSkyColor();
};