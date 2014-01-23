#pragma once
#include "UIObject.h"
#include <math.h>

#define HT_VERTICAL 0
#define HT_HOROZONTAL 1

class UITransitionObject : public UIObject
{
public:
	enum TransitionState { SHOWN,SHOWING,HIDDEN,HIDING };
protected:
	
	// Properties 
	float mNormalLoc, mHideLoc;
	float mHideSpeed;
	int mHideType;
	bool mFadeOut;

	// States 
	TransitionState mState;
	bool mHide;

public:

	UITransitionObject();
	virtual ~UITransitionObject();

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
	void hide();
	// Tell the object to show
	void show();

	// Check if the object is hidden
	bool hidden();
	// Check if the object is shown
	bool shown();

	// Instantly hide the object
	void setHidden();
	// Instantly show the object 
	void setShown();
};

