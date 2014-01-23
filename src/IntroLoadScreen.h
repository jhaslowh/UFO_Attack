#pragma once
#include <glew.h>
#include <string>
#include "UIScreen.h"
#include "UIAtlas.h"
#include "Sprite.h"

class IntroLoadScreen : public UIScreen
{
	float waitTime;
	GLfloat mColor[4];
	Sprite DGSplash;

public:
	IntroLoadScreen();
	virtual ~IntroLoadScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load Screen
	virtual void load(TextureAtlas* mAtlas);

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

