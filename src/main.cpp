#include "../samplefw/SampleRunner.h"
#include "../wolf/wolf.h"
#include "sampleCity.h"
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>

class Week2 : public wolf::App
{
public:
	Week2()
		: wolf::App("City")
	{
		m_sampleRunner.addSample(new SampleCity(this));
	}

	~Week2()
	{
	}

	void update(float dt) override
	{
		if (isKeyDown(' ')) {
			m_lastDown = true;
		} else if (m_lastDown) {
			m_sampleRunner.nextSample();
			m_lastDown = false;
		}

		m_sampleRunner.update(dt);
	}

	void render() override
	{
		m_sampleRunner.render(m_width, m_height);
	}

private:
	SampleRunner m_sampleRunner;
	bool m_lastDown = false;
};

int main(int, char**)
{
	Week2 week2;
	week2.run();
}