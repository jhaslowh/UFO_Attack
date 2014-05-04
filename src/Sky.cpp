#include "Sky.h"


Sky::Sky()
{
	// Set properties 
	skyState = SKY_STATE_DAY;
	mTime = (float)(rand() % 24);
	mHoursPerSecond = .05f;
	mMaxLightAlpha = .5f;
	scalex = 1.0f;
	scaley = 1.0f;

	// Set colors 
	mBlueColor[0] = 0.45f;
	mBlueColor[1] = 0.61f;
	mBlueColor[2] = 1.0f; 
	mBlueColor[3] = 1.0f;

	mNightColor[0] = 0.1f;
	mNightColor[1] = 0.1f;
	mNightColor[2] = 0.1f;
	mNightColor[3] = 1.0f;

	mOrangeColor[0] = 1.0f;
	mOrangeColor[1] = 0.66f;
	mOrangeColor[2] = 0.1f;
	mOrangeColor[3] = 1.0f;

	mNightLightColor[0] = 1.0f;
	mNightLightColor[1] = 1.0f;
	mNightLightColor[2] = .7f;
	mNightLightColor[3] = 0.0f;

	// Do one update to fix colors 
	update(0.0f);
}

Sky::~Sky()
{

}

float Sky::getLightValue(){return lightValue;}

// Set the current time of day 
void Sky::setTimeOfDay(float time){
	if (time < 0.0f || time > 24.0f) return;
	mTime = time;
}


// Set progression time
void Sky::setHoursPerSecond(float value){
	mHoursPerSecond = value;
}

// Set up sky 
void Sky::init(float screen_width, float screen_height){
	scalex = screen_width;
	scaley = screen_height / 1022.0f;
}

// Update sky
void Sky::update(float deltaTime){
	// Increment time of day 
	mTime += mHoursPerSecond * deltaTime;
	if (mTime > 24)
		mTime = 0;
  
	// --------------------------
	// Update the main sky colors 
	// --------------------------
	// Night 
	if ((mTime >= 0 && mTime < DAWN_START) || mTime >= DUSK_END){
		mBlueColor[3] = 0.0f;
		lightValue = .2f;
		skyState = SKY_STATE_NIGHT;
	}
	// Night to Day 
	else if (mTime >= DAWN_START && mTime < DAWN_END){
		mBlueColor[3]  = mOrangeColor[3] = (mTime - DAWN_START) / (DAWN_END - DAWN_START);
		lightValue = .5f - (.3f - (((mTime - DAWN_START) / (DAWN_END - DAWN_START)) * .3f));
		skyState = SKY_STATE_DAY;
	}
	// Day
	else if (mTime >= DAWN_END && mTime < DUSK_START){
		mBlueColor[3] = 1.0f;
		lightValue = .5f;

		// Dusk dawn fade off 
		if (mTime < DAWN_FADEOFF)
			mOrangeColor[3] = 1.0f - ((mTime - DAWN_END) / (DAWN_FADEOFF - DAWN_END));
		else if (mTime >= DUSK_FADEOFF)
			mOrangeColor[3] = (mTime - DUSK_FADEOFF) / (DUSK_START - DUSK_FADEOFF);
		else 
			mOrangeColor[3] = 0;
    
		skyState = SKY_STATE_DAY;
	}
	// Day to Night
	else if (mTime >= DUSK_START && mTime < DUSK_END){
		mBlueColor[3] = mOrangeColor[3] = 1.0f - ((mTime - DUSK_START) / (DUSK_END - DUSK_START));
		lightValue = .5f - (((mTime - DUSK_START) / (DUSK_END - DUSK_START)) * .3f);
		skyState = SKY_STATE_NIGHT;
	}
  
	// ---------------------------------------------------------------
	// Night time lights to simulate the sun going down and comming up. 
	// ---------------------------------------------------------------
	// Night lights Off
	if (mTime >= LIGHTS_OFF_START && mTime < LIGHTS_OFF_END){
		mNightLightColor[3] = mMaxLightAlpha - (((mTime - LIGHTS_OFF_START) / (LIGHTS_OFF_END - LIGHTS_OFF_START)) * mMaxLightAlpha);
	}
	// Night lights on
	else if (mTime >= LIGHTS_ON_START && mTime < LIGHTS_ON_END){
		mNightLightColor[3] = ((mTime - LIGHTS_ON_START) / (LIGHTS_ON_END - LIGHTS_ON_START)) * mMaxLightAlpha;
	}
	// Neither. (Time is Day or Night, and not changing between the two) 
	else {
		// Night
		if ((mTime >= 0 && mTime < DAWN_START) || mTime >= DUSK_END)
			mNightLightColor[3] = mMaxLightAlpha;
		else
			mNightLightColor[3] = 0.0f;
	}
}

// Draw sky 
void Sky::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	// Draw sky
	mgl->setFlatColor(mNightColor);
	mAtlas->drawScale2(mgl, GI_SKY,0,0,scalex,scaley);
  
	mgl->setFlatColor(mBlueColor);
	mAtlas->drawScale2(mgl, GI_SKY,0,0,scalex,scaley);
  
	// If night 
	mgl->setFlatColor(mNightLightColor);
	mAtlas->drawScale2(mgl, GI_SKY_GLOW,0,0,scalex,scaley);
  
	// Draw orange glow 
	if ((mTime >= DAWN_START && mTime < DAWN_FADEOFF) || 
		(mTime >= DUSK_FADEOFF && mTime < DUSK_END)){
		mgl->setFlatColor(mOrangeColor);
		mAtlas->drawScale2(mgl, GI_SKY_GLOW,0,0,scalex,scaley);
	}
}

