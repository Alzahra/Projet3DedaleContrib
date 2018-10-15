#pragma once
#include "includes.h"
#include "Vector3.h"

class Object
{
protected:
	Vector3* location;
public:
	virtual void draw();
	virtual void update();
	Vector3* getLocation();
};

