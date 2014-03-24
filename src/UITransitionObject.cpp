#include "UITransitionObject.h"

UITransitionObject::UITransitionObject() : UIObject(){
	mState = SHOWN;
	mNormalLoc = 0;
	mHideLoc = 0;
	mHideSpeed = 1000.0f;
	mHideType = HT_NONE;
	mHide = false;
	mFadeOut = false;
	mOpacity = 1.0f;
	chideTime = 0.0f;
	hideTime = 1.0f;
}
UITransitionObject::~UITransitionObject(){}

// Get object opacity
// This is used by fadeout, and is different
// than alpha. 
float UITransitionObject::getOpacity(){return mOpacity;}

// Quick one step setup 
void UITransitionObject::setupHide(int hideType, float hideLoc, float ht, bool fadeOut){
	setHideType(hideType);
	mHideLoc = hideLoc;
	hideTime = ht;
	setHideSpeedOnTime(ht);
	mFadeOut = fadeOut;
}

// Set the way the object transitions 
void UITransitionObject::setHideType(int value){ 
	mHideType = value;
	if (mHideType == HT_VERTICAL) mNormalLoc = loc_y;
	else mNormalLoc = loc_x;
}

// Set the normal location for the object
void UITransitionObject::setNormalLoc(float location){mNormalLoc = location;}

// Tell the object where to hide to
void UITransitionObject::setHideLoc(float location){ mHideLoc = location;}

// Set hide location by a specified distance.
// Will only work correctly if normal location is set first.
void UITransitionObject::setHideLocByDistance(float distance){
	mHideLoc = mNormalLoc + distance;
}

// Set the speed the object will hide 
void UITransitionObject::setHideSpeed(float speed){mHideSpeed = speed;}

// Set the hide speed based off how long it should take to hide
void UITransitionObject::setHideSpeedOnTime(float time){
	mHideSpeed = abs(mNormalLoc - mHideLoc)/ time;
}

// Set to true to fade out the object when hiding
void UITransitionObject::setFadeOut(bool value){mFadeOut = value;}

// Update the object
void UITransitionObject::update(float deltaTime){
	if (mHideType != HT_NONE){
		// Update hide time 
		if (mHide){
			chideTime += deltaTime;
			if (chideTime > hideTime)
				chideTime = hideTime;
		}
		else {
			chideTime -= deltaTime;
			if (chideTime < 0.0f)
				chideTime = 0.0f;
		}

		// Get percentage
		float per = chideTime / hideTime;

		// Fix position 
		if (mHideType == HT_HOROZONTAL){
			loc_x = mNormalLoc + (per * (mHideLoc - mNormalLoc));

			if (loc_x == mHideLoc)
				mState = HIDDEN;
			if (loc_x == mNormalLoc)
				mState = SHOWN;
		}
		else if (mHideType == HT_VERTICAL){
			loc_y = mNormalLoc + (per * (mHideLoc - mNormalLoc));

			if (loc_y == mHideLoc)
				mState = HIDDEN;
			if (loc_y == mNormalLoc) 
				mState = SHOWN;
		}

		// Fade out if set 
		if (mFadeOut) 
			mOpacity = 1.0f - per;
	}
}

// Draw the object to the screen
// UIAtles must be bound first.
void UITransitionObject::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UIObject::draw(mgl, mAtlas);
}

// Tell the object to hide
void UITransitionObject::hide(){mHide = true;}
// Tell the object to show
void UITransitionObject::show(){mHide = false;}


// Check if the object is hidden
bool UITransitionObject::hidden(){
	if (mHideType == HT_NONE)
		return false;
	else if (mHideType == HT_HOROZONTAL)
		return loc_x == mHideLoc;
	else 
		return loc_y == mHideLoc;
}

// Check if the object is shown
bool UITransitionObject::shown(){
	if (mHideType == HT_NONE)
		return true;
	else if (mHideType == HT_HOROZONTAL)
		return loc_x == mNormalLoc;
	else 
		return loc_y == mNormalLoc;
}

// Instantly hide the object
void UITransitionObject::setHidden(){
	mState = HIDDEN; 
	mHide = true;
	chideTime = hideTime;
	if (mFadeOut) mOpacity = 0.0f;
		
	if (mHideType == HT_HOROZONTAL)
		loc_x = mHideLoc;
	else if (mHideType == HT_VERTICAL)
		loc_y = mHideLoc;
}

// Instantly show the object 
void UITransitionObject::setShown(){
	mState = SHOWN;
	mHide = false;
	chideTime = 0.0f;
	if (mFadeOut) mOpacity = 1.0f;
	
	if (mHideType == HT_HOROZONTAL)
		loc_x = mNormalLoc;
	else if (mHideType == HT_VERTICAL)
		loc_y = mNormalLoc;
}
