#pragma once
#include <string>
#include "TextureAtlas.h"
#include "TextRender.h"
#include "VertCordGenerator.h"

// UI Index's
#define UII_BUTTON_NORMAL 0
#define UII_BUTTON_HOVER 1
#define UII_BUTTON_CLICK 2
#define UII_CHECKBOX_NORMAL 3
#define UII_CHECKBOX_CHECKED 4

class UIAtlas : public TextureAtlas
{
	
public:
	// Text renderer is part of this texture sheet
	// so we use it in here. 
	TextRender* mTextRender;

	UIAtlas();
	virtual ~UIAtlas();

	// Set up the stucture of this atlas 
	void init();
};

