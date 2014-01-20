#include "Collision.h"

// Check if two line segments intersect. 
// *p = the point of intersection 
bool checkSegSeg(Point a, Point b, Point c, Point d){
	return checkSegSeg(a,b,c,d,NULL);
}
bool checkSegSeg(Point a, Point b, Point c, Point d, Point* p){
	float D = 
		(a.getX() * (d.getY() - c.getY())) +
		(b.getX() * (c.getY() - d.getY())) + 
		(d.getX() * (b.getY() - a.getY())) + 
		(c.getX() * (a.getY() - b.getY()));
		
	if ((float)abs(D) < 0.000001)
		return false;
	
	float s = 
		((a.getX() * (d.getY() - c.getY())) + 
		 (c.getX() * (a.getY() - d.getY())) + 
		 (d.getX() * (c.getY() - a.getY())))/D;
	float t = 
		-((a.getX() * (c.getY() - b.getY())) +
         (b.getX() * (a.getY() - c.getY())) +
         (c.getX() * (b.getY() - a.getY())))/D;
	
	if (s < 0 || s > 1 || t > 1 || t < 0)
		return false;
	
	if (p != NULL){
		p->setX(a.getX() + (s * (b.getX() - a.getX())));
		p->setY(a.getY() + (s * (b.getY() - a.getY())));
	}
	
	//if (s == 0 || s == 1 || t == 1 || t == 0) // Vertex collision 
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