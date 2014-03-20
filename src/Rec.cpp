#include "Rec.h"

Rec::Rec()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
}
Rec::Rec(float x, float y, float w, float h){
	mX = x;
	mY = y;
	mWidth = w;
	mHeight = h;
}
Rec::~Rec(){}

/// Getters and settings

void Rec::setLocation(float x, float y){
	mX = x;
	mY = y;
}
void Rec::setX(float x){
	mX = x;
}
float Rec::getX(){
	return mX;
}
void Rec::setY(float y){
	mY = y;
}
float Rec::getY(){
	return mY;
}
void Rec::setSize(float w, float h){
	mWidth = w;
	mHeight = h;
}
void Rec::setWidth(float w){
	mWidth = w;
}
float Rec::getWidth(){
	return mWidth;
}
void Rec::setHeight(float h){
	mHeight = h;
}
float Rec::getHeight(){
	return mHeight;
}

/// Functions

// Edges 
float Rec::right(){
	return mX + mWidth;
}
float Rec::left(){
	return mX;
}
float Rec::top(){
	return mY;
}
float Rec::bottom(){
	return mY + mHeight;
}

// Check if this AABB contains the sent point 
bool Rec::contains(float x, float y){
	if (x > mX && x < right() && y > mY && y < bottom())
		return true;
	return false;
}

// Check if this AABB contains the sent point at the sent offset
bool Rec::contains(float x, float y, float offx, float offy){
	if (x > mX + offx && x < right() + offx && 
		y > mY + offy && y < bottom() + offy)
		return true;
	return false;
}

// Expand the rec 
void Rec::expand(float amount){
	mX -= amount;
	mY -= amount;
	mWidth += amount;
	mHeight += amount;
}

// Reset values 
void Rec::reset(float x, float y, float w, float h){
	mX = x;
	mY = y;
	mWidth = w;
	mHeight = h;
}

// Copy the sent rec properties into this one
void Rec::copy(Rec* r){
	mX = r->mX;
	mY = r->mY;
	mWidth = r->mWidth;
	mHeight = r->mHeight;
}