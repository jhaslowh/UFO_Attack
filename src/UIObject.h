#pragma once
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "GLHandler.h"
#include "UIAtlas.h"

class UIObject
{
protected:
	// Location settings 
	float loc_x,loc_y,width,height;
	GLfloat flatColor[4];

public:
	UIObject();
	virtual ~UIObject();
	
	// Getters and setters 
	virtual void setLocation(float x, float y);
	float getX();
	virtual void setX(float);
	float getY();
	virtual void setY(float);
	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	void setColor(float r, float g, float b);
	void setColor(float r, float g, float b, float a);
	GLfloat* getColor();
	void setAlpha(float a);
	float getAlpha();

	// Call if object has child objects that need to be set up
	virtual void init(float screen_width, float screen_height);
	// Call if object has child objects that need to be loaded
	virtual void load(TextureAtlas* mAtlas);

	// Update the button 
	virtual void update(float deltaTime);
	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Draw the object to the screen at sent offset.
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy);

	// Check if the sent location is inside the objc
	virtual bool contains(float x, float y);
};

