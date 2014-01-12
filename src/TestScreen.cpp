#include "TestScreen.h"

TestScreen::TestScreen()
	: UIScreen(){}

TestScreen::~TestScreen(){
	UIScreen::~UIScreen();
}

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

	printf("Screen Loaded \n");
}

// Update the state of the screen
void TestScreen::update(float deltaTime)
{
	UIScreen::update(deltaTime);

	rotstat += 90.0f * deltaTime;
	sprite.setRotation(rotstat);
}

// Update input to the screen 
void TestScreen::updateInput(KeyHandler mKeyH){
	UIScreen::updateInput(mKeyH);

	if (mKeyH.keyDown(KEY_W))
		cube.setRotationX(cube.getRotationX() - 5.0f);
	if (mKeyH.keyDown(KEY_S))
		cube.setRotationX(cube.getRotationX() + 5.0f);
	if (mKeyH.keyDown(KEY_A))
		cube.setRotationY(cube.getRotationY() - 5.0f);
	if (mKeyH.keyDown(KEY_D))
		cube.setRotationY(cube.getRotationY() + 5.0f);
}

// Draw the screen
void TestScreen::draw(GLHandler* mgl, TextRender* mTR){
	UIScreen::draw(mgl,mTR);

	mgl->setWorldMatrix(mgl->orthoMatrix);

	GLfloat color[] = {1.0f,0.0f,0.0f,1.0f};
	mgl->setFlatColor(color);
	mTR->drawText(*mgl,
		"AaBbCcDdEeFf\n"
		"GgHhIiJjKkLlMm\n"
		"NnOoPpQqRrSs\n"
		"TtUuVvWwXxYyZz\n"
		"0123456789:.%-/?\n"
		,150,10,0,20);
	GLfloat color2[] = {.5,.5f,.5f,1.0f};
	mgl->setFlatColor(color2);
	mTR->drawText(*mgl, 
		"This is an example sentence.",
		50,150,0,25);
	mTR->drawText(*mgl, 
		"This is an example rotated sentence.",
		50,200,20,25);
	sprite.draw(*mgl);

	mgl->setWorldMatrix(mgl->camera3DMatrix);
	cube.draw(*mgl);
}
