/**
 * Interface for observable objects
 */
#pragma once
#include "../utility.h"
#include "observer.h"
#include <algorithm>
#include <memory>
#include <vector>
class Observable
{
public:
	void registerObserver(std::shared_ptr<Observer> o)
	{
		if (std::find(observers.begin(), observers.end(), o) == observers.end()) {
			// does not contains
			observers.emplace_back(o);
		}
	}

	void removeObserver(std::shared_ptr<Observer> o)
	{
		observers.erase(std::find(observers.begin(), observers.end(), o));
	}

	virtual void notifyObservers() const = 0;

protected:
	std::vector<std::shared_ptr<Observer>> observers;
};