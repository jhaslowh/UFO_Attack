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
	VertCordGenerator* vcg = new VertCordGenerator(1024,512);
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
	// Bubble center
	vcg->addFrame(732.0f,67.0f,1.0f,20.0f);
	// Bubble edge
	vcg->addFrame(735.0f,67.0f,10.0f,20.0f);
	// Bubble arrow
	vcg->addFrame(747.0f,67.0f,10.0f,10.0f);

	// UI Outline boxes
	// Top left corner
	vcg->addFrame(690.0f, 106.0f, 6.0f, 6.0f);
	// Top right corner 
	vcg->addFrame(697.0f, 106.0f, 6.0f, 6.0f);
	// Bottom left corner 
	vcg->addFrame(690.0f, 113.0f, 6.0f, 6.0f);
	// Bottom right corner 
	vcg->addFrame(697.0f, 113.0f, 6.0f, 6.0f);
	// Top border
	vcg->addFrame(696.0f, 106.0f, 1.0f, 6.0f);
	// Bottom border
	vcg->addFrame(696.0f, 113.0f, 1.0f, 6.0f);
	// Left border
	vcg->addFrame(690.0f, 112.0f, 6.0f, 1.0f);
	// Right border
	vcg->addFrame(697.0f, 112.0f, 6.0f, 1.0f);
	// Middle
	vcg->addFrame(696.0f, 112.0f, 1.0f, 1.0f);
	// Currency Animal
	vcg->addFrame(632.0f, 130.0f, 20.0f, 20.0f);
	// Currency Human
	vcg->addFrame(654.0f, 130.0f, 20.0f, 20.0f);
	// Combo box arrow
	vcg->addFrame(632.0f, 152.0f, 20.0f, 20.0f);

	// LS Buttons
	// LS Target Light
	vcg->addFrame(798.0f, 1.0f, 50.0f, 50.0f);
	// LS Target Dark
	vcg->addFrame(850.0f, 1.0f, 50.0f, 50.0f);
	// LS Home
	vcg->addFrame(902.0f, 1.0f, 50.0f, 50.0f);
	// LS Target Light Check 
	vcg->addFrame(798.0f, 53.0f, 50.0f, 50.0f);
	// LS Target Dark Check 
	vcg->addFrame(850.0f, 53.0f, 50.0f, 50.0f);

	// Difficulty 1
	vcg->addFrame(705.0f, 106.0f, 30.0f, 30.0f);
	// Difficulty 2
	vcg->addFrame(737.0f, 106.0f, 30.0f, 30.0f);
	// Difficulty 3
	vcg->addFrame(769.0f, 106.0f, 30.0f, 30.0f);

	// Tut arrow
	vcg->addFrame(631.0f, 175.0f, 20.0f, 20.0f);

	// Tut ammo
	vcg->addFrame(801.0f, 106.0f, 20.0f, 20.0f);

	// Grab the arrays 
	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete vcg;
}