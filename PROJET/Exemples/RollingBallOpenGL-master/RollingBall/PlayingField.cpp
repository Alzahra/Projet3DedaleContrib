#include "PlayingField.h"

PlayingField::PlayingField(int w, int d, double wh, Vector3* location)
{
	this->location = location;

	this->wallHeight = wh;
}

PlayingField::~PlayingField()
{
}

void PlayingField::draw() {

	glColor4d(1, 1, 1, 0.8);

	glBegin(GL_QUADS);

	// draw floor
	glTexCoord2d(0.0, 0.0);
	glVertex3i(
		this->location->getX() - PlayingField::WIDTH / 2,
		this->location->getY(),
		this->location->getZ() - PlayingField::DEPTH / 2
	);
	glTexCoord2d(1.0, 0.0);
	glVertex3i(
		this->location->getX() + PlayingField::WIDTH / 2,
		this->location->getY(),
		this->location->getZ() - PlayingField::DEPTH / 2
	);
	glTexCoord2d(1.0, 1.0);
	glVertex3i(
		this->location->getX() + PlayingField::WIDTH / 2,
		this->location->getY(),
		this->location->getZ() + PlayingField::DEPTH / 2
	);
	glTexCoord2d(0.0, 1.0);
	glVertex3i(
		this->location->getX() - PlayingField::WIDTH / 2,
		this->location->getY(),
		this->location->getZ() + PlayingField::DEPTH / 2
	);

	glEnd();
}