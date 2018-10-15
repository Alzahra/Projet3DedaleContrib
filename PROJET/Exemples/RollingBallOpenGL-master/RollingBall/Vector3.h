#pragma once
#include "includes.h"

class Vector3
{
private:
	GLdouble x, y, z, w;
public:
	Vector3();
	Vector3(GLdouble x, GLdouble y, GLdouble z);
	~Vector3();
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	Vector3* add(Vector3* v);
	Vector3* mul(double scalar);
	static Vector3* spherical(double r, double theta, double phi);
};

