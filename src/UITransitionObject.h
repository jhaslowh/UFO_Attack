#pragma once
#include <math.h>
#include "UIObject.h"

#define HT_VERTICAL 0
#define HT_HOROZONTAL 1
#define HT_NONE 2

class UITransitionObject : public UIObject
{
public:
	enum TransitionState { SHOWN,SHOWING,HIDDEN,HIDING };
protected:
	
	// Properties 
	float mNormalLoc, mHideLoc;
	float mHideSpeed;
	int mHideType;
	float mOpacity;
	bool mFadeOut;
	
	// Hide time of the object, 0 is shown
	// chideTime == hideTime is hidden. 
	float chideTime;
	float hideTime;

	// States 
	TransitionState mState;
	bool mHide;

public:

	UITransitionObject();
	virtual ~UITransitionObject();

	// Get object opacity
	// This is used by fadeout, and is different
	// than alpha. 
	float getOpacity();

	// Quick one step setup 
	void setupHide(int hideType, float hideLoc, float hideTime, bool fadeOut);

	// Set the way the object transitions 
	void setHideType(int hideType);
	// Set the normal location for the object
	void setNormalLoc(float location);
	// Tell the object where to hide to
	void setHideLoc(float location);
	// Set hide location by a specified distance.
	// Will only work correctly if normal location is set first.
	void setHideLocByDistance(float distance);
	// Set the speed the object will hide 
	void setHideSpeed(float speed);
	// Set the hide speed based off how long it should take to hide
	void setHideSpeedOnTime(float time);
	// Set to true to fade out the object when hiding
	void setFadeOut(bool value);

	// Update the object
	virtual void update(float deltaTime);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Tell the object to hide
	virtual void hide();
	// Tell the object to show
	virtual void show();

	// Check if the object is hidden
	bool hidden();
	// Check if the object is shown
	bool shown();

	// Instantly hide the object
	virtual void setHidden();
	// Instantly show the object 
	virtual void setShown();
};

