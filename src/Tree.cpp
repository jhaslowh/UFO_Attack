#include "Tree.h"


Tree::Tree() : SceneryObject()
{
	type = "tree";
	width = 100.0f;
	height = 100.0f;
	originX = 50.0f;
	originY = 100.0f;
	imageID = GI_TREE1;
}

Tree::~Tree(){}
