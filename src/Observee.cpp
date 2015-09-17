#include "Observee.h"
#include "IObserver.h"


void Observee::AddObserver(IObserver * obs)
{
	observers.push_back(obs);
}

void Observee::NotifyObservers(int type)
{
	for(IObserver * obs : observers)
	{
		obs->Notify(type);
	}
}
