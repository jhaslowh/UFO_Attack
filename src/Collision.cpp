#include "Collision.h"

// Returns 2 times the signed triangle area. The result is positive if 
// abc is ccw, negative if abc is cw, zero if abc is degenerate.
float Signed2DTriArea(Point a, Point b, Point c){
	return (a.getX() - c.getX()) * (b.getY() - c.getY()) 
		- (a.getY() - c.getY()) * (b.getX() - c.getX());
}

// Check if two line segments intersect. 
// *p = the point of intersection 
bool checkSegSeg(Point a, Point b, Point c, Point d){
	return checkSegSeg(a,b,c,d,NULL);
}
bool checkSegSeg(Point a, Point b, Point c, Point d, Point* p){
	// CS 425 Teacher magic 
	float D = 
		(a.getX() * (d.getY() - c.getY())) +
		(b.getX() * (c.getY() - d.getY())) + 
		(d.getX() * (b.getY() - a.getY())) + 
		(c.getX() * (a.getY() - b.getY()));
		
	if ((float)abs(D) < 0.000001)
		return false;
	
	// More CS 425 Teacher magic 
	float s = 
		((a.getX() * (d.getY() - c.getY())) + 
		 (c.getX() * (a.getY() - d.getY())) + 
		 (d.getX() * (c.getY() - a.getY())))/D;
	float t = 
		-((a.getX() * (c.getY() - b.getY())) +
         (b.getX() * (a.getY() - c.getY())) +
         (c.getX() * (b.getY() - a.getY())))/D;
	
	// Collision point is outside line bounds 
	if (s < 0 || s > 1 || t > 1 || t < 0)
		return false;
	
	// Set return point values 
	if (p != NULL){
		p->setX(a.getX() + (s * (b.getX() - a.getX())));
		p->setY(a.getY() + (s * (b.getY() - a.getY())));
	}

	// Vertex collision 
	//if (s == 0 || s == 1 || t == 1 || t == 0) 
	return true;
}
bool checkSegSeg(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2){
	return checkSegSeg(a1,a2,b1,b2,c1,c2,d1,d2,NULL);
}
bool checkSegSeg(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2, Point* p){
	// CS 425 Teacher magic 
	float D = 
		(a1 * (d2 - c2)) +
		(b1 * (c2 - d2)) + 
		(d1 * (b2 - a2)) + 
		(c1 * (a2 - b2));
		
	if ((float)abs(D) < 0.000001)
		return false;
	
	// More CS 425 Teacher magic 
	float s = 
		((a1 * (d2 - c2)) + 
		 (c1 * (a2 - d2)) + 
		 (d1 * (c2 - a2)))/D;
	float t = 
		-((a1 * (c2 - b2)) +
         (b1 * (a2 - c2)) +
         (c1 * (b2 - a2)))/D;
	
	// Collision point is outside line bounds 
	if (s < 0 || s > 1 || t > 1 || t < 0)
		return false;
	
	// Set return point values 
	if (p != NULL){
		p->setX(a1 + (s * (b1 - a1)));
		p->setY(a2 + (s * (b2 - a2)));
	}

	// Vertex collision 
	//if (s == 0 || s == 1 || t == 1 || t == 0) 
	return true;
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
bool checkRecSeg(Rec* r, float a1, float a2, float b1, float b2){
	return checkRecSeg(r,a1,a2,b1,b2,NULL);
}
bool checkRecSeg(Rec* r, float a1, float a2, float b1, float b2, Point* p){
	// Check top side 
	if (checkSegSeg(a1,a2,b1,b2,r->getX(), r->getY(),r->getX() + r->getWidth(), r->getY(),p))
		return true;

	// Check left side 
	if (checkSegSeg(a1,a2,b1,b2,r->getX(), r->getY(),r->getX(), r->getY() + r->getHeight(),p))
		return true;

	// Check bottom side
	if (checkSegSeg(a1,a2,b1,b2,r->getX() + r->getWidth(), r->getY() + r->getHeight(),r->getX(), r->getY() + r->getHeight(),p))
		return true;

	// Check right side
	if (checkSegSeg(a1,a2,b1,b2,r->getX() + r->getWidth(), r->getY() + r->getHeight(),r->getX() + r->getWidth(), r->getY(),p))
		return true;

	return false;
}

// Find the distance between point a and b
float dist(Point a, Point b){
	float x = b.getX() - a.getX();
	x *= x;
	float y = b.getY() - a.getY();
	y *= y;
	return sqrt(x + y);
}

// Find the distance between target and loc
float dist(float tarX, float tarY, float locX, float locY){
	float x = tarX - locX;
	x *= x;
	float y = tarY - locY;
	y *= y;
	return sqrt(x + y);
}

// Find the angle between point a and b.
// Return angle in degrees. 
float angle(Point a, Point b){
	return (180.0f / 3.14159f) * (float)atan2(b.getY() - a.getY(), b.getX() - a.getX());
}