#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->w = 1;
}

Vector3::Vector3(GLdouble x, GLdouble y, GLdouble z) {

	this->x = x;
	this->y = y;
	this->z = z;
	
	this->w = 1;
}

Vector3::~Vector3()
{
}

GLdouble Vector3::getX() {
	
	return this->x;
}


GLdouble Vector3::getY() {
	
	return this->y;
}

GLdouble Vector3::getZ() {

	return this->z;
}

Vector3* Vector3::add(Vector3* v) {

	return new Vector3(
		this->getX() + v->getX(),
		this->getY() + v->getY(),
		this->getZ() + v->getZ()
	);
}

Vector3* Vector3::mul(double scalar) {

	return new Vector3(
		this->getX() * scalar,
		this->getY() * scalar,
		this->getZ() * scalar
	);
}

// theta: angle with horizontal plane
// phi: left-right angle
Vector3* Vector3::spherical(double r, double theta, double phi) {

	double x = r * cos(theta) * sin(phi);
	double y = r * sin(theta) * sin(phi);
	double z = r * cos(phi);

	return new Vector3(x, y, z);
}