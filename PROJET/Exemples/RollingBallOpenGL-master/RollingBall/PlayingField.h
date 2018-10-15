#pragma once
#include "includes.h"
#include "Object.h"

class PlayingField : public Object
{
private:
	double wallHeight;
public:
	static const int WIDTH = 20, DEPTH = 20;
	PlayingField(int w, int h, double wh, Vector3* location);
	~PlayingField();
	void draw() override;
};

