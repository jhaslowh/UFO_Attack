#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Point.h"
#include "Rec.h"

// Returns 2 times the signed triangle area. The result is positive if 
// abc is ccw, negative if abc is cw, zero if abc is degenerate.
float Signed2DTriArea(Point a, Point b, Point c);

// Check if two line segments intersect. 
// *p = the point of intersection 
bool checkSegSeg(Point a, Point b, Point c, Point d);
bool checkSegSeg(Point a, Point b, Point c, Point d, Point* p);

// Check if two rectangles intersect
bool checkRecRec(Rec* r1, Rec* r2);

// Check if a rectangle intersects a line segment 
bool checkRecSeg(Rec* r, Point a, Point b);
bool checkRecSeg(Rec* r, Point a, Point b, Point* p);