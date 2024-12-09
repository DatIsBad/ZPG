#pragma once
class Observer
{
public:
	virtual void updateObservedKey(char userInput) = 0;
	virtual void updateObservedCursor(double x, double y) = 0;
	//virtual void update() = 0;
};

