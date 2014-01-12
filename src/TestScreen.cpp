#include "TestScreen.h"

TestScreen::TestScreen() : UIScreen(){}
TestScreen::~TestScreen(){}

// Initialize screen
void TestScreen::init(){
	UIScreen::init();
	// Testing 
	sprite.setup(64.f,64.f,"test2.png");
	sprite.setPosition(64.f,64.f);
	sprite.setScale(1.0f);
	sprite.setOrigin(32.0f,32.0f);
	sprite.setAlpha(1.0f);

	cube.setScale(5.0f);
	cube.setTexture("test.png");

	button1 = new UIButton(500,100,100,35,"Button1");

	printf("Screen initalized \n");
}


// Load screen
void TestScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	button1->centerText(mUI->mTextRender);
	printf("Screen Loaded \n");
}

// Update the state of the screen
void TestScreen::update(float deltaTime)
{
	UIScreen::update(deltaTime);

	rotstat += 90.0f * deltaTime;
	sprite.setRotation(rotstat);

	button1->update(deltaTime);
}

// Update input to the screen 
void TestScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	if (mKeyH->keyDown(KEY_W))
		cube.setRotationX(cube.getRotationX() - 5.0f);
	if (mKeyH->keyDown(KEY_S))
		cube.setRotationX(cube.getRotationX() + 5.0f);
	if (mKeyH->keyDown(KEY_A))
		cube.setRotationY(cube.getRotationY() - 5.0f);
	if (mKeyH->keyDown(KEY_D))
		cube.setRotationY(cube.getRotationY() + 5.0f);

	button1->updateInput(mKeyH, mMouseH);

	if (button1->wasClicked())
		printf("Button 1 Clicked\n");
}

// Draw the screen
void TestScreen::draw(GLHandler* mgl,  TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setWorldMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);
	
	// Draw test text 1 
	GLfloat color[] = {0.7f,0.0f,0.0f,1.0f};
	mgl->setFlatColor(color);
	mUI->mTextRender->drawText(*mgl,
		"AaBbCcDdEeFf\n"
		"GgHhIiJjKkLlMm\n"
		"NnOoPpQqRrSs\n"
		"TtUuVvWwXxYyZz\n"
		"0123456789:.%-/?\n"
		,150,10,0,20);

	// Draw test text 2
	GLfloat color2[] = {.5,.5f,.5f,1.0f};
	mgl->setFlatColor(color2);
	mUI->mTextRender->drawText(*mgl, 
		"This is an example sentence.",
		50,150,0,25);

	// Draw test text 3
	mUI->mTextRender->drawText(*mgl, 
		"This is an example rotated sentence.",
		50,200,20,25);

	button1->draw(mgl, mUI);

	sprite.draw(*mgl);

	mgl->setWorldMatrix(mgl->camera3DMatrix);
	cube.draw(*mgl);
}
