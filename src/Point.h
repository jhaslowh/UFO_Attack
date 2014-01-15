#pragma once
class Point
{
	float mX; 
	float mY;

public:
	Point();
	Point(float x, float y);

	void setLocation(float x, float y);
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
};

