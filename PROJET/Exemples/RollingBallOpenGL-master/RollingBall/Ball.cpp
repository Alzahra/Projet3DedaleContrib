#include "Ball.h"

const double Ball::PI = 3.14159265359;

Ball::Ball(GLdouble r, GLint slices, GLint stacks)
{
	this->location = new Vector3();
	this->quadric = gluNewQuadric();

	this->radius = r;
	this->slices = slices;
	this->stacks = stacks;

	this->speed = 0;
	this->speedDelta = 0.00001;
	this->brakeFactor = 0.99;
	this->friction = 0.999;
	this->rotationY = 0;
	this->rotationYDelta = 0.008;
}

Ball::~Ball()
{
	delete this->location;
	gluDeleteQuadric(this->quadric);
}

void Ball::draw() {

	/*OutputDebugString(L"Drawing ball\n")*/;

	glPushMatrix();

	glRotated(this->rotationY, 0, 1, 0);

	glTranslated(this->location->getX(), this->location->getY(), this->location->getZ());

	gluQuadricDrawStyle(this->quadric, GLU_FILL);
	glColor4f(1, 1, 1, 1);

	gluSphere(this->quadric, this->radius, this->slices, this->stacks);

	glPopMatrix();
}

void Ball::update() {

	wchar_t str[100];
	swprintf_s(str, 100, L"Rotation: %f Speed %f\n", this->rotationY, this->speed);
	OutputDebugString(str);
	
	swprintf_s(str, 100, L"Location: %f %f %f\n", this->location->getX(), this->location->getY(), this->location->getZ());
	OutputDebugString(str);

	this->speed *= this->friction;

	// update location based on speed and rotation around the Y axis
	this->location = this->location->add(Vector3::spherical(this->speed, 0, this->rotationY));

	// alternative solution for updating location using the unit circle
	/*Vector3* unit = new Vector3(sin(this->rotationY), 0, cos(this->rotationY));
	this->location = this->location->add(unit->mul(this->speed));*/

	// reflecting the ball angle when it reaches the edges
	if (this->location->getX() < -PlayingField::WIDTH / 2)
		this->rotationY = 2 * Ball::PI - this->rotationY;
	else if (this->location->getX() > PlayingField::WIDTH / 2)
		this->rotationY = this->rotationY + Ball::PI - this->rotationY / 2;
	else if (this->location->getZ() < -PlayingField::DEPTH / 2) {
		this->rotationY = (Ball::PI - this->rotationY) / 2;
		if (this->rotationY < 0) this->rotationY += 2.0 * Ball::PI;
	}
	else if (this->location->getZ() > PlayingField::DEPTH / 2) {
		this->rotationY = this->rotationY + Ball::PI - this->rotationY * 2;
		if (this->rotationY < 0) this->rotationY += 2.0 * Ball::PI;
	}
}

void Ball::handleInput(Directions d) {

	if (d.up) {
		this->speed += this->speedDelta;
	}
	else if (d.down) {
		this->speed *= this->brakeFactor;
	}

	if (d.right) {
		this->rotationY -= this->rotationYDelta;
		if (this->rotationY < 0) this->rotationY += 2.0 * Ball::PI;
	}
	else if (d.left) {
		this->rotationY += this->rotationYDelta;
		if (this->rotationY > 2.0 * Ball::PI) this->rotationY -= 2.0 * Ball::PI;
	}
}