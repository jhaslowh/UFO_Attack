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
	mTextRender = new TextRender();

	VertCordGenerator* vcg = new VertCordGenerator(1024,1024);
	mTextRender->createFontBuffers(vcg);

	textureID = FileHelper::loadPNG("text.png");

	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}
