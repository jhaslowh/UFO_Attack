#pragma once
#include <glew.h>
#include "GLHandler.h"
#include "TextureAtlas.h"
#include "GameAtlas.h"

// Times of day 
#define DAWN_START 4.0f
#define DAWN_END 7.0f
#define DAWN_FADEOFF 10.0f
#define DUSK_START 17.0f
#define DUSK_END 20.0f
#define DUSK_FADEOFF 14.0f

// Night light times 
#define LIGHTS_OFF_START 3.0f
#define LIGHTS_OFF_END 6.0f
#define LIGHTS_ON_START 18.0f
#define LIGHTS_ON_END 21.0f

// Clouds
#define CLOUD_MIN_ALPHA .2f
#define CLOUD_MAX_ALPHA 1.0f

// States 
#define SKY_STATE_DAY 1
#define SKY_STATE_NIGHT 2

class Sky
{
	// Scale of background 
	float scalex, scaley;

	// State for the sky 
	int skyState;

	// Sky properties 
	float mTime;
	float mHoursPerSecond;
	GLfloat mBlueColor[4];
	GLfloat mNightColor[4];
	GLfloat mOrangeColor[4];

	// Nights lights 
	float mMaxLightAlpha;
	GLfloat mNightLightColor[4];
	float lightValue;

public:
	Sky();
	~Sky();

	float getLightValue();

	// Set the current time of day 
	void setTimeOfDay(float time);

	// Set progression time
	void setHoursPerSecond(float value);

	// Set up sky 
	void init(float screen_width, float screen_height);

	// Update sky
	void update(float deltaTime);

	// Draw sky 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

