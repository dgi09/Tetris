#pragma once 
#include <vector>

class IObserver;

class Observee
{

	std::vector<IObserver*> observers;
public:

	void AddObserver(IObserver * obs);
	
protected:
	void NotifyObservers(int type);
};