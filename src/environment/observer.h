/**
 * Class to represent an object that observes an observable object
 */
#pragma once

class Observer
{
public:
	virtual void update() = 0;

private:
};