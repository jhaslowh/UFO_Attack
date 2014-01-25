#include "Point.h"

Point::Point()
{
	mX = 0;
	mY = 0;
	next = NULL;
	prev = NULL;
}
Point::Point(float x, float y)
{
	mX = x;
	mY = y;
	next = NULL;
	prev = NULL;
}
Point::~Point(){}

void Point::setLocation(float x, float y){
	mX = x;
	mY = y;
}
void Point::setX(float x){
	mX = x;
}
float Point::getX(){
	return mX;
}
void Point::setY(float y){
	mY = y;
}
float Point::getY(){
	return mY;
}

// Checks if p1 == p2
bool  operator==(Point p1, Point p2){
	return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}
	
// Checks if p1 != p2
bool  operator!=(Point p1, Point p2){
	return (p1.getX() != p2.getX()) || (p1.getY() != p2.getY());
}

// Point addition (p1 + p2)
Point operator+ (Point p1, Point p2){
	return Point(p1.getX() + p2.getX(), p1.getY() + p2.getY());
}
	
// Point subtraction (p1 - p2)
Point operator- (Point p1, Point p2){
	return Point(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

// Scalar multiplication (s * p1)
Point operator* (float s, Point p1){
	return Point(p1.getX() * s, p1.getY() * s);
}
	
// Scalar multiplication (p1 * s)
Point operator* (Point p1, float s){
	return Point(p1.getX() * s, p1.getY() * s);
}