#include "UIAtlas.h"

UIAtlas::UIAtlas(){
	mTextRender = NULL;
}
UIAtlas::~UIAtlas()
{
	delete mTextRender;
}

// Set up the stucture of this atlas 
void UIAtlas::load(){
	// Load texture
	textureID = loadPNG( std::string("images/AtlasUI.png"));
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
	// Checkbox Normal
	vcg->addFrame(631,105,24,24);
	// Checkbox Checked 
	vcg->addFrame(655,105,24,24);
	// Rec
	vcg->addFrame(14.0f,33.0f,1.0f,1.0f);
	// Level Arrow
	vcg->addFrame(732.0f, 1.0f,64.0f,64.0f);
	// Point
	vcg->addFrame(680.0f,106.0f,8.0f,8.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}