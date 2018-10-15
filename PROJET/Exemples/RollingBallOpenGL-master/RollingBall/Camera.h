#pragma once
#include "includes.h"
#include "Object.h"
#include "Ball.h"

class Camera : public Object
{
private:
	Ball* ball;
	const double distanceFromBall = 20;
public:
	Camera(Ball* ball);
	~Camera();
	void update() override;
};

