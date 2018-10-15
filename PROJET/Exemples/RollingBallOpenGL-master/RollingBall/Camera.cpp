#include "Camera.h"

Camera::Camera(Ball* ball)
{
	this->ball = ball;
}

Camera::~Camera()
{
}

void Camera::update() {

	GLdouble ballX = ball->getLocation()->getX();
	GLdouble ballY = ball->getLocation()->getY();
	GLdouble ballZ = ball->getLocation()->getZ();

	GLdouble x = ballX + cos(90) * this->distanceFromBall;
	GLdouble y = ballY + 20;
	GLdouble z = ballZ + cos(90) * this->distanceFromBall;

	gluLookAt(
		x, y, z,
		ballX, ballY, ballZ, 
		0, 1, 0
	);
}