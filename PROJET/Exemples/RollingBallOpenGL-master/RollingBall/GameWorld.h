#pragma once
#include "includes.h"
#include "BitmapLoader.h"
#include "Ball.h"
#include "Camera.h"
#include "PlayingField.h"

class GameWorld
{
private:
	Ball* ball;
	Camera* camera;
	PlayingField* playingField;
	const static int WIDTH = 800, HEIGHT = 600;
public:
	GameWorld(HDC deviceContext);
	~GameWorld();
	void render(HDC deviceContext);
	void update(Directions dirs);
};

