#pragma once
#include "GLColors.h"
#include "UITransitionObject.h"

class UILevelButton : public UITransitionObject
{
protected: 
	// States
	bool clicked, hovered, down;
	int imageHover;
	int imageNormal;
	int diffIcon;
	float diffOffsetX, diffOffsetY;

	// Shadow variables
	GLfloat shadowColor[4];
	bool drawShadow;
	float shadowOffX, shadowOffY;

	// Labels
	std::string title;
	float titleLocX, titleLocY;
	float titleTextSize;
	std::string desc;
	float descLocX, descLocY;
	float descTextSize;

	// Difficulty setting
	int difficulty;
	bool completed;
	bool locked;

public:
	UILevelButton();
	UILevelButton(float x, float y, float w, float h);
	virtual ~UILevelButton();

	// Getters and setters 
	void setDifficulty(int diff);
	int getDifficulty();
	void setCompleted(bool c);
	bool getCompleted();
	void setLocked(bool l);
	bool getLocked();
	void setTitle(std::string t);
	std::string getTitle();
	void setDesc(std::string d);
	std::string getDesc();

	// Center title text and fix location of title and description
	// Note: call the after the title and scale have been set 
	void fixTextLoc(TextRender* mTR);

	// Update button 
	virtual void update(float deltaTime);
	// Update button input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool wasClicked();
};

