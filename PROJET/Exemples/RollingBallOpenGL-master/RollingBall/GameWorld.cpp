#include "GameWorld.h"

GameWorld::GameWorld(HDC deviceContext)
{
	/*** Dave Astle: "OpenGL Game Programming" ***/
	glViewport(0, 0, WIDTH, HEIGHT);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

											// calculate aspect ratio of window
	gluPerspective(54.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();
	/*** Dave Astle: "OpenGL Game Programming" ***/

	GLfloat lightPos[] = { 0, 20, 0, 1 };

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	BitmapLoader::loadBmp("normal.bmp");
	BitmapLoader::bindTexture(1);

	this->ball = new Ball(1, 20, 20);
	this->camera = new Camera(ball);
	this->playingField = new PlayingField(20, 20, 5, new Vector3(0, -1, 0));
}

GameWorld::~GameWorld()
{
	delete this->ball;
}

void GameWorld::render(HDC deviceContext) {

	glClearColor(0, 0, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->playingField->draw();
	this->ball->draw();

	SwapBuffers(deviceContext);
}

void GameWorld::update(Directions dirs) {

	glLoadIdentity();

	this->ball->handleInput(dirs);
	this->ball->update();

	this->camera->update();
}