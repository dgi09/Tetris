#pragma once 

class IObserver 
{
public:
	virtual void Notify(int type) = 0;
};