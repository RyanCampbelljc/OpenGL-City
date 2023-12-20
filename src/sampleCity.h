//-----------------------------------------------------------------------------
// File:			SampleCity.h
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "../samplefw/Grid3D.h"
#include "../samplefw/Sample.h"
#include "../wolf/wolf.h"
#include "city.h"

class SampleCity : public Sample
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	SampleCity(wolf::App* pApp);
	~SampleCity();

	void init() override;
	void update(float dt) override;
	void render(int width, int height) override;
	//------------------------------------

private:
	//------------------------------------
	// PRIVATE MEMBERS
	//------------------------------------
	float m_dt;
	City m_city;
	Sphere m_sun;
	Camera m_camera;
	Grid3D m_grid;
	WorldEnvironment& m_worldEnvironment;
	//------------------------------------
};
