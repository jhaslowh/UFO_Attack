#include "Point.h"

Point::Point()
{
	mX = 0;
	mY = 0;
}
Point::Point(float x, float y)
{
	mX = x;
	mY = y;
}

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