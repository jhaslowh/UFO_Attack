#pragma once
#include <stdlib.h>

class Point
{
	float mX; 
	float mY;

public:
	Point* next;
	Point* prev;

	Point();
	Point(float x, float y);
	~Point();

	void setLocation(float x, float y);
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();

	// Checks if p1 == p2
 	friend bool  operator==(Point p1, Point p2);
	
	// Checks if p1 != p2
	friend bool  operator!=(Point p1, Point p2);
	
	// Point addition (p1 + p2)
	friend Point operator+ (Point p1, Point p2);
	
	// Point subtraction (p1 - p2)
	friend Point operator- (Point p1, Point p2);

	// Scalar multiplication (s * p1)
	friend Point operator* (float s, Point p1);
	
	// Scalar multiplication (p1 * s)
	friend Point operator* (Point p1, float s);
};

