#pragma once
#include "Point.h"

class Rec
{
	// Properties 
	float mX;
	float mY;
	float mWidth;
	float mHeight;

public:
	Rec();
	Rec(float x, float y, float w, float h);
	~Rec();

	/// Getters and settings

	void setLocation(float, float);
	void setX(float);
	float getX();
	void setY(float);
	float getY();
	void setSize(float, float);
	void setWidth(float);
	float getWidth();
	void setHeight(float);
	float getHeight();

	/// Functions
	
	// Edges 
	float right();
	float left();
	float top();
	float bottom();

	// Check if this AABB contains the sent point 
	bool contains(float x, float y);
	// Check if this AABB contains the sent point at the sent offset
	bool contains(float x, float y, float offx, float offy);
	// Expand the rec 
	void expand(float amount);
	// Reset values 
	void reset(float x, float y, float w, float h);
	// Copy the sent rec properties into this one
	void copy(Rec* r);
};

