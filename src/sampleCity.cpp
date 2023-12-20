//-----------------------------------------------------------------------------
// File:			SampleCity.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "sampleCity.h"
#include "../samplefw/Grid2D.h"

#include <iostream>
// number of rows and columns in the city
static const int citySize = 24;

SampleCity::SampleCity(wolf::App* pApp)
	: Sample(pApp, "Sample of city")
	, m_camera(1280, 720, pApp)
	, m_grid(1)
	, m_city(citySize)
	, m_sun(10.0f)
	, m_worldEnvironment(WorldEnvironment::instance())
{
	m_sun.SetColor(glm::vec3(255, 255, 0));
	m_sun.SetPosition(m_worldEnvironment.getSunPosition());
}

SampleCity::~SampleCity()
{
}

void SampleCity::init()
{
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
}

// every frame updates the world environment
void SampleCity::update(float dt)
{
	m_dt = dt;
	m_worldEnvironment.update(m_dt);
	m_worldEnvironment.setCamPos(m_camera.getCamPos());
	m_sun.SetPosition(m_worldEnvironment.getSunPosition());
	if (m_pApp->isKeyJustDown('r')) {
		m_city.refresh();
	}
}

void SampleCity::render(int width, int height)
{
	glm::vec3 clearColor = m_worldEnvironment.getSkyColor();

	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.setWidth(width);
	m_camera.setHeight(height);
	m_camera.update(m_dt);
	m_city.render(m_camera);
	m_sun.render(m_camera.getProjection(), m_camera.getView());
	// m_grid.render(m_camera.getView(), m_camera.getProjection());
}