#pragma once
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"

class UIScreen
{
protected:
	bool loaded;

public:
	UIScreen();
	~UIScreen();

	// Initialize screen
	virtual void init();

	// Load screen
	virtual void load(TextureAtlas* mAtlas);

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

