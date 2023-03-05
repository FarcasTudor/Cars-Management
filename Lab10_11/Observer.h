#pragma once

class Observer {
public:
	virtual void update() = 0;

};

#include <vector>
#include <algorithm>

class Observable {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}
	void removeObserver(Observer* observer) {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}
	void notify() {
		for (auto observer : observers)
		{
			observer->update();
		}
	}
};