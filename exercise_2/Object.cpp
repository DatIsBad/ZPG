#include "Object.h"
Object::Object() {
	float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};

	m_size = 9;
	m_points = new float[m_size];

	for (int i = 0; i < m_size; i++) {
		m_points[i] = points[i];
	}
}


Object::Object(float arr[], int size) {
	m_points = new float[size];
	m_size = size;
	for (int i = 0; i < size; i++) {
		m_points[i] = arr[i];
	}
}


Object::~Object() {
	delete[] m_points;
}


float* Object::getPoints() {
	return m_points;
}


int Object::getSize() {
	return m_size;
}