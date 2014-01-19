#pragma once
#include <glew.h>
#include "UIScreen.h"
#include "UIAtlas.h"
#include <string>

class IntroLoadScreen : public UIScreen
{
	float waitTime;
	GLfloat mColor[4];

public:
	IntroLoadScreen();
	~IntroLoadScreen();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

