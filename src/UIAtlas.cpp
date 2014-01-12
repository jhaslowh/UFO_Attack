#include "UIAtlas.h"


UIAtlas::UIAtlas()
{

}

UIAtlas::~UIAtlas()
{
	if (mTextRender != NULL)
		delete(mTextRender);
}

// Set up the stucture of this atlas 
void UIAtlas::init(){
	// Load texture
	textureID = FileHelper::loadPNG("UI-Sheet.png");
	// Set offset to the number of characters
	// becaue the text renderer shares these buffers
	setIndiceOffset(TR_CHARACTERS);

	// Make text renderer 
	mTextRender = new TextRender();
	VertCordGenerator* vcg = new VertCordGenerator(1024,1024);
	mTextRender->createFontBuffers(vcg);

	// Add UI elements to the buffers
	// Button Normal
	vcg->addFrame(631,0,100,35);
	// Button Hover
	vcg->addFrame(631,35,100,35);
	// Button Click
	vcg->addFrame(631,70,100,35);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}
