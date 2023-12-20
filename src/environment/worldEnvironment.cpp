#include "worldEnvironment.h"

// seconds in day
const float WorldEnvironment::timeInDay = 24 * 60 * 60;
// how many times faster a day is in this simulation compared to an actual day
const float WorldEnvironment::timeScale = 1800.0f;
//(seconds in a day is timeInDay/timeScale)

// helper function
static inline float lerp(float low, float high, float percent)
{
	return low + ((high - low) * percent);
}
// helper function
static inline glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float percent)
{
	return start + ((end - start) * percent);
}

void WorldEnvironment::notifyObservers() const
{
	for (const auto& o : observers) {
		o->update();
	}
}

void WorldEnvironment::update(float dt)
{
	static bool pause = false;
	auto pApp = (wolf::App*)(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	if (pApp->isKeyJustDown(GLFW_KEY_SPACE))
		pause = !pause;
	m_dt = dt;
	m_time += dt * (pause ? 0.f : timeScale);
	if (m_time >= timeInDay)
		m_time = 0.0f;
	updateSkyColor();
	updateSunPos();
	notifyObservers();
}

glm::vec3 WorldEnvironment::getSunPosition()
{
	return m_sunPosition;
}

glm::vec3 WorldEnvironment::getSunDirection()
{
	return glm::normalize(m_sunPosition);
}

glm::vec3 WorldEnvironment::getSkyColor()
{
	return m_skyColor;
}

glm::vec3 WorldEnvironment::getCamPos()
{
	return m_camPosition;
}

void WorldEnvironment::setCamPos(glm::vec3 pos)
{
	m_camPosition = pos;
}

void WorldEnvironment::updateSunPos()
{
	m_sunPosition = (glm::vec3)(
		glm::rotate(glm::mat4(1.0f), lerp(PI, -PI, m_time / timeInDay), glm::vec3(0, 0, 1))
		* glm::vec4(m_sunStartPos, 1));
}
void WorldEnvironment::updateSkyColor()
{
	if (m_time >= (timeInDay / 2.0f)) { // midday to midnight
		m_skyColor = //(m_time - (timeInDay / 2.0f)) / (timeInDay / 2.0f)
			lerp(glm::vec3(0.384f, 0.586f, 0.712f), glm::vec3(0.0f, 0.0f, 0.0f), (2 * m_time / timeInDay) - 1.0f);
	} else {
		m_skyColor = lerp(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.384f, 0.586f, 0.712f), m_time / (timeInDay / 2.0f));
	}
}
