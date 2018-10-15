#pragma once
#include "includes.h"
#include "Object.h"
#include "PlayingField.h"
#include "Timer.h"

struct Directions {

	bool left;
	bool right;
	bool up;
	bool down;
};

class Ball : public Object
{
private:
	GLUquadricObj* quadric;

	GLdouble radius;
	GLint slices;
	GLint stacks;

	double speed, speedDelta, maxSpeed,
		brakeFactor, friction,
		rotationY, rotationYDelta;
public:
	static const double PI;
	Ball(GLdouble r, GLint slices, GLint stacks);
	~Ball();
	void draw() override;
	void update() override;
	void handleInput(Directions d);
};

