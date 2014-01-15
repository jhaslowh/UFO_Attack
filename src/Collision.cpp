#include "Collision.h"

// Check if two line segments intersect. 
// *p = the point of intersection 
bool checkSegSeg(Point a1, Point a2, Point b1, Point b2){
	// TODO 
	printf("checkSegSeg not implemented \n");
	return false;
}
bool checkSegSeg(Point p1, Point p2, Point b1, Point b2, Point* p){
	// TODO 
	printf("checkSegSeg not implemented \n");
	return false;
}

// Check if two rectangles intersect
bool checkRecRec(Rec* r1, Rec* r2){
	return 
		!(r1->bottom() < r2->getY()	  ||
		  r1->getY()   > r2->bottom() ||
		  r1->right()  < r2->getX()   ||
		  r1->getX()   > r2->right());
}

// Check if a rectangle intersects a line segment 
bool checkRecSeg(Rec* r, Point a, Point b){
	return checkRecSeg(r,a,b,NULL);
}
bool checkRecSeg(Rec* r, Point a, Point b, Point* p){
	Point c;
	Point d;

	// Check top side 
	c.setLocation(r->getX(), r->getY());
	d.setLocation(r->getX() + r->getWidth(), r->getY());
	if (checkSegSeg(a,b,c,d,p))
		return true;

	// Check left side 
	d.setLocation(r->getX(), r->getY() + r->getHeight());
	if (checkSegSeg(a,b,c,d,p))
		return true;

	// Check bottom side
	c.setLocation(r->getX() + r->getWidth(), r->getY() + r->getHeight());
	if (checkSegSeg(a,b,c,d,p))
		return true;

	// Check right side
	d.setLocation(r->getX() + r->getWidth(), r->getY());
	if (checkSegSeg(a,b,c,d,p))
		return true;

	return false;
}