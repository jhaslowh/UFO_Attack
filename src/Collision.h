#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "Rec.h"

// Check if two line segments intersect. 
// *p = the point of intersection 
bool checkSegSeg(Point a1, Point a2, Point b1, Point b2);
bool checkSegSeg(Point p1, Point p2, Point b1, Point b2, Point* p);

// Check if two rectangles intersect
bool checkRecRec(Rec* r1, Rec* r2);

// Check if a rectangle intersects a line segment 
bool checkRecSeg(Rec* r, Point a, Point b);
bool checkRecSeg(Rec* r, Point a, Point b, Point* p);