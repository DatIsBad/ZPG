#pragma once
class Object
{
public:
	Object();
	Object(float arr[], int size);
	~Object();
	float* getPoints();
	int getSize();

private:
	float* m_points;
	int m_size;
};

