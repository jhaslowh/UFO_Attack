#include "TestScreen.h"

TestScreen::TestScreen() : UIScreen(){}
TestScreen::~TestScreen(){
	delete button1;
	delete button2;
	delete button3;
	delete checkbox1;
	delete close;
}

// Initialize screen
void TestScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	button1 = new UIButton(500,100,100,35, std::string("Button1"));
	button1->setupHide(HT_VERTICAL,200.0f,.4f,true);
	button2 = new UIButton(500,150,100,35, std::string("Button2"));
	button2->setupHide(HT_VERTICAL,250.0f,.4f,true);
	button3 = new UIButton(500,200,100,35, std::string("Button3"));
	button3->setupHide(HT_VERTICAL,300.0f,.4f,true);

	checkbox1 = new UICheckbox(620,100,24,24, std::string("Test Transitions"));
	close = new UIButton(10,screen_height - 45.0f,100,35, std::string("Back"));

	printf("Screen initalized \n");
}

// Load screen
void TestScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	button1->centerText(mUI->mTextRender);
	button2->centerText(mUI->mTextRender);
	button3->centerText(mUI->mTextRender);
	close->centerText(mUI->mTextRender);

	
	sprite.setup(64.f,64.f, std::string("test2.png"));
	sprite.setPosition(64.f,64.f);
	sprite.setScale(1.0f);
	sprite.setOrigin(32.0f,32.0f);
	sprite.setAlpha(.2f);

	cube.setScale(5.0f);
	cube.setTexture( std::string("test.png"));
	printf("Screen Loaded \n");
}

// Update the state of the screen
void TestScreen::update(float deltaTime)
{
	UIScreen::update(deltaTime);


	rotstat += 90.0f * deltaTime;
	sprite.setRotation(rotstat);

	button1->update(deltaTime);
	button2->update(deltaTime);
	button3->update(deltaTime);
	checkbox1->update(deltaTime);
	close->update(deltaTime);

	if (!checkbox1->Checked()){
		button1->show();
		button2->show();
		button3->show();
	}
	else {
		button1->hide();
		button2->hide();
		button3->hide();
	}
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
	button2->updateInput(mKeyH, mMouseH);
	button3->updateInput(mKeyH, mMouseH);
	checkbox1->updateInput(mKeyH, mMouseH);
	close->updateInput(mKeyH, mMouseH);

	if (close->wasClicked())
		transitionCode = SCREEN_MAIN;

	if (button1->wasClicked())
		printf("Button 1 Clicked\n");
}

// Draw the screen
void TestScreen::draw(GLHandler* mgl,  TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	std::string s1("AaBbCcDdEeFf\n"
		"GgHhIiJjKkLlMm\n"
		"NnOoPpQqRrSs\n"
		"TtUuVvWwXxYyZz\n"
		"0123456789:.%-/?\n");
	std::string s2("This is an example sentence.");
	std::string s3("This is an example rotated sentence.");
	
	// Draw test text 1 
	GLfloat color[] = {0.7f,0.0f,0.0f,1.0f};
	mgl->setFlatColor(color);
	mUI->mTextRender->drawText(*mgl,s1,150,10,0,20);

	// Draw test text 2
	GLfloat color2[] = {.5,.5f,.5f,1.0f};
	mgl->setFlatColor(color2);
	mUI->mTextRender->drawText(*mgl, s2,50,150,0,25);

	// Draw test text 3
	mUI->mTextRender->drawText(*mgl, s3,50,200,20,25);

	button1->draw(mgl, mUI);
	button2->draw(mgl, mUI);
	button3->draw(mgl, mUI);
	checkbox1->draw(mgl, mUI);
	close->draw(mgl, mUI);

	sprite.draw(*mgl);

	mgl->setProjectionMatrix(mgl->camera3DMatrix);
	cube.draw(*mgl);
}
