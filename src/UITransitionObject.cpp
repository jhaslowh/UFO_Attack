#include "UITransitionObject.h"

UITransitionObject::UITransitionObject() : UIObject(){
	mState = SHOWN;
	mNormalLoc = 0;
	mHideLoc = 0;
	mHideSpeed = 1000.0f;
	mHideType = HT_VERTICAL;
	mHide = false;
	mFadeOut = false;
}
UITransitionObject::~UITransitionObject(){}

// Quick one step setup 
void UITransitionObject::setupHide(int hideType, float hideLoc, float hideTime, bool fadeOut){
	setHideType(hideType);
	mHideLoc = hideLoc;
	setHideSpeedOnTime(hideTime);
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
	if (mHideType == HT_HOROZONTAL){
		if (mNormalLoc > mHideLoc){
			if (mHide){
				if (loc_x != mHideLoc){
					loc_x -= deltaTime * mHideSpeed;
					if (loc_x < mHideLoc){
						loc_x = mHideLoc;
						mState = HIDDEN;
					}
				}
			}else {
				if (loc_x != mNormalLoc){
					loc_x += deltaTime * mHideSpeed;
					if (loc_x > mNormalLoc){
						loc_x = mNormalLoc;
						mState = SHOWN;
					}
				}
			}
		}
		else if (mNormalLoc < mHideLoc){
			if (mHide){
				if (loc_x != mHideLoc){
					loc_x += deltaTime * mHideSpeed;
					if (loc_x > mHideLoc){
						loc_x = mHideLoc;
						mState = HIDDEN;
					}
				}
			}else {
				if (loc_x != mNormalLoc){
					loc_x -= deltaTime * mHideSpeed;
					if (loc_x < mNormalLoc){
						loc_x = mNormalLoc;
						mState = SHOWN;
					}
				}
			}
		}
		if (mFadeOut) 
			flatColor[3] = (float)abs(loc_x - mHideLoc) / (float)abs(mNormalLoc - mHideLoc);
	}
	else if (mHideType == HT_VERTICAL){
		if (mNormalLoc > mHideLoc){
			if (mHide){
				if (loc_y != mHideLoc){
					loc_y -= deltaTime * mHideSpeed;
					if (loc_y < mHideLoc){
						loc_y = mHideLoc;
						mState = HIDDEN;
					}
				}
			}else {
				if (loc_y != mNormalLoc){
					loc_y += deltaTime * mHideSpeed;
					if (loc_y > mNormalLoc){
						loc_y = mNormalLoc;
						mState = SHOWN;
					}
				}
			}
		}else if (mNormalLoc < mHideLoc){
			if (mHide){
				if (loc_y != mHideLoc){
					loc_y += deltaTime * mHideSpeed;
					if (loc_y > mHideLoc){
						loc_y = mHideLoc;
						mState = HIDDEN;
					}
				}
			}else {
				if (loc_y != mNormalLoc){
					loc_y -= deltaTime * mHideSpeed;
					if (loc_y < mNormalLoc){
						loc_y = mNormalLoc;
						mState = SHOWN;
					}
				}
			}
		}
	
		if (mFadeOut) 
			flatColor[3] = (float)abs(loc_y - mHideLoc) / (float)abs(mHideLoc - mNormalLoc);
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
	if (mHideType == HT_HOROZONTAL)
		return loc_x == mHideLoc;
	else 
		return loc_y == mHideLoc;
}

// Check if the object is shown
bool UITransitionObject::shown(){
	if (mHideType == HT_HOROZONTAL)
		return loc_x == mNormalLoc;
	else 
		return loc_y == mNormalLoc;
}

// Instantly hide the object
void UITransitionObject::setHidden(){
	mState = HIDDEN; 
	mHide = false;
	if (mFadeOut) flatColor[3] = 0.0f;
		
	if (mHideType == HT_HOROZONTAL)
		loc_x = mHideLoc;
	else if (mHideType == HT_VERTICAL)
		loc_y = mHideLoc;
}

// Instantly show the object 
void UITransitionObject::setShown(){
	mState = SHOWN;
	mHide = false;
	if (mFadeOut) flatColor[3] = 1.0f;
	
	if (mHideType == HT_HOROZONTAL)
		loc_x = mNormalLoc;
	else if (mHideType == HT_VERTICAL)
		loc_y = mNormalLoc;
}
