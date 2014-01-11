#include "TextRender.h"


TextRender::TextRender(){
	setup = false;
	textureID = -1;

	verts = NULL;
	cords = NULL;
}

TextRender::~TextRender(){
	if (verts != NULL) free(verts);
	if (cords != NULL) free(cords);
}

// Must be called before the renderer can be used 
void TextRender::init(){
	textureID = FileHelper::loadPNG("text.png");
	createFontBuffers();
	setup = true;
}

// Draw text to the screen with the following properties 
void TextRender::drawText(GLHandler mgl, char* text, float x, float y, float rotation, float fontSize){
	if (setup){
		float scale = fontSize / TR_FONT_SIZE;
		float length = (float)strlen(text);

		/** Matrix transform **/
		// Starting matrix 
		glm::mat4 mMatrix;
		// Translate 
		mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
		// Rotation
		if (rotation != 0)
			mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		// Scale 
		mMatrix = glm::scale(mMatrix, glm::vec3(scale));
        
		/// Set up vertex and coord buffers 
		glEnableVertexAttribArray(mgl.mPositionHandle);
		glVertexAttribPointer(mgl.mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, verts );

		/// Bind texture
		glEnableVertexAttribArray(mgl.mTextCordHandle);
		glVertexAttribPointer(mgl.mTextCordHandle, 2,GL_FLOAT, GL_FALSE, 0, cords);

		mgl.toggleTextures(true);
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl.mTextureHandle, 0);

		if (length > 0){
			float size = 0;

			for (int i =0; i < length; i++){
				char c = text[i];
				if (c  != '\n' && c != ' '){
					// Translate
					glm::mat4 matrix;
					matrix = glm::translate(mMatrix, glm::vec3(size, 0.0f, 0.0f));
					mgl.setModelMatrix(matrix);
					
					// Draw Letter
					setIndicies(c);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
					
					size += getLetterWidth(c);
				}else if (c == ' '){
					size += TR_SPACE_LENGTH;
				}
				else if (c == '\n'){
					mMatrix = glm::translate(mMatrix, glm::vec3(0.0f, TR_FONT_SIZE, 0.0f));
					size = 0;
				}
			}
		}

		glDisableVertexAttribArray(mgl.mPositionHandle);
		glDisableVertexAttribArray(mgl.mTextCordHandle);
	}
	else{
		printf("Error: Font not initialized\n");
	}
}

// Measure how long the text will be on screen
float TextRender::measureString(char* text, float size){
	float scale = size/72.0f;
	float length = 0;
	int textLength = strlen(text);
	char c; 

	for (int i = 0; i < textLength; i++){
		c = text[i];
		length += getLetterWidth(c);
	}
		
	return (length * scale);
}

// Get the index for the sent char
int TextRender::getCharIndex(char c){
	switch (c){
		// Row 1 Start
		case 'A':
			return 0;
		case 'a':
			return 1;
		case 'B':
			return 2;
		case 'b':
			return 3;
		case 'C':
			return 4;
		case 'c':
			return 5;
		case 'D':
			return 6;
		case 'd':
			return 7;
		case 'E':
			return 8;
		case 'e':
			return 9;
		case 'F':
			return 10;
		case 'f':
			return 11;
		// Row 2 Start
		case 'G':
			return 12;
		case 'g':
			return 13;
		case 'H':
			return 14;
		case 'h':
			return 15;
		case 'I':
			return 16;
		case 'i':
			return 17;
		case 'J':
			return 18;
		case 'j':
			return 19;
		case 'K':
			return 20;
		case 'k':
			return 21;
		case 'L':
			return 22;
		case 'l':
			return 23;
		case 'M':
			return 24;
		case 'm':
			return 25;
		// Row 3 Start
		case 'N':
			return 26;
		case 'n':
			return 27;
		case 'O':
			return 28;
		case 'o':
			return 29;
		case 'P':
			return 30;
		case 'p':
			return 31;
		case 'Q':
			return 32;
		case 'q':
			return 33;
		case 'R':
			return 34;
		case 'r':
			return 35;
		case 'S':
			return 36;
		case 's':
			return 37;
		// Row 4 Start
		case 'T':
			return 38;
		case 't':
			return 39;
		case 'U':
			return 40;
		case 'u':
			return 41;
		case 'V':
			return 42;
		case 'v':
			return 43;
		case 'W':
			return 44;
		case 'w':
			return 45;
		case 'X':
			return 46;
		case 'x':
			return 47;
		case 'Y':
			return 48;
		case 'y':
			return 49;
		case 'Z':
			return 50;
		case 'z':
			return 51;
		// Row 4 Start
		case '0':
			return 52;
		case '1':
			return 53;
		case '2':
			return 54;
		case '3':
			return 55;
		case '4':
			return 56;
		case '5':
			return 57;
		case '6':
			return 58;
		case '7':
			return 59;
		case '8':
			return 60;
		case '9':
			return 61;
		case ':':
			return 62;
		case '.':
			return 63;
		case '%':
			return 64;
		case '-':
			return 65;
		case '/':
			return 66;
		case '?':
			return 67;
		default:
			return 0;
	}
}

// Get the width of the sent character 
float TextRender::getLetterWidth(char c){
	switch (c){
	// Row 1 Start
	case 'A':
		return letterWidth[0];
	case 'a':
		return letterWidth[1];
	case 'B':
		return letterWidth[2];
	case 'b':
		return letterWidth[3];
	case 'C':
		return letterWidth[4];
	case 'c':
		return letterWidth[5];
	case 'D':
		return letterWidth[6];
	case 'd':
		return letterWidth[7];
	case 'E':
		return letterWidth[8];
	case 'e':
		return letterWidth[9];
	case 'F':
		return letterWidth[10];
	case 'f':
		return letterWidth[11];
	// Row 2 Start
	case 'G':
		return letterWidth[12];
	case 'g':
		return letterWidth[13];
	case 'H':
		return letterWidth[14];
	case 'h':
		return letterWidth[15];
	case 'I':
		return letterWidth[16];
	case 'i':
		return letterWidth[17];
	case 'J':
		return letterWidth[18];
	case 'j':
		return letterWidth[19];
	case 'K':
		return letterWidth[20];
	case 'k':
		return letterWidth[21];
	case 'L':
		return letterWidth[22];
	case 'l':
		return letterWidth[23];
	case 'M':
		return letterWidth[24];
	case 'm':
		return letterWidth[25];
	// Row 3 Start
	case 'N':
		return letterWidth[26];
	case 'n':
		return letterWidth[27];
	case 'O':
		return letterWidth[28];
	case 'o':
		return letterWidth[29];
	case 'P':
		return letterWidth[30];
	case 'p':
		return letterWidth[31];
	case 'Q':
		return letterWidth[32];
	case 'q':
		return letterWidth[33];
	case 'R':
		return letterWidth[34];
	case 'r':
		return letterWidth[35];
	case 'S':
		return letterWidth[36];
	case 's':
		return letterWidth[37];
	// Row 4 Start
	case 'T':
		return letterWidth[38];
	case 't':
		return letterWidth[39];
	case 'U':
		return letterWidth[40];
	case 'u':
		return letterWidth[41];
	case 'V':
		return letterWidth[42];
	case 'v':
		return letterWidth[43];
	case 'W':
		return letterWidth[44];
	case 'w':
		return letterWidth[45];
	case 'X':
		return letterWidth[46];
	case 'x':
		return letterWidth[47];
	case 'Y':
		return letterWidth[48];
	case 'y':
		return letterWidth[49];
	case 'Z':
		return letterWidth[50];
	case 'z':
		return letterWidth[51];
	// Row 4 Start
	case '0':
		return letterWidth[52];
	case '1':
		return letterWidth[53];
	case '2':
		return letterWidth[54];
	case '3':
		return letterWidth[55];
	case '4':
		return letterWidth[56];
	case '5':
		return letterWidth[57];
	case '6':
		return letterWidth[58];
	case '7':
		return letterWidth[59];
	case '8':
		return letterWidth[60];
	case '9':
		return letterWidth[61];
	case ':':
		return letterWidth[62];
	case '.':
		return letterWidth[63];
	case '%':
		return letterWidth[64];
	case '-':
		return letterWidth[65];
	case '/':
		return letterWidth[66];
	case '?':
		return letterWidth[67];
	default:
		return 30.0f;
	}
}

// Set the indexes based off a char
void TextRender::setIndicies(char c){
	int index = getCharIndex(c);

	indicies[0] = (GLushort)(4 * index);
	indicies[1] = (GLushort)((4 * index) + 1);
	indicies[2] = (GLushort)((4 * index) + 2);
	indicies[3] = (GLushort)((4 * index) + 2);
	indicies[4] = (GLushort)((4 * index) + 3);
	indicies[5] = (GLushort)(4 * index);
}

// Setup the buffers for the font 
void TextRender::createFontBuffers(){
	VertCordGenerator* vcg = new VertCordGenerator(1024,1024);

	// A 
	vcg->addFrame(0.0f, 0.0f, 52.7f, 71.0f);
	letterWidth[0] = 52.7f;
		
	// a  
	vcg->addFrame(54.61f,0.0f,36.2f,72.0f);
	letterWidth[1] =  40.0f;
		
	// B 
	vcg->addFrame(97.79f, 0.0f, 43.8f, 72.0f);
	letterWidth[2] = 43.8f;
		
	// b  
	vcg->addFrame(148.59f, 0.0f, 36.8f, 72.0f);
	letterWidth[3] = 36.8f;
		
	// C 
	vcg->addFrame(190.5f, 0.0f, 46.4f, 72.0f);
	letterWidth[4] = 46.4f;
		
	// c 
	vcg->addFrame(241.3f, 0.0f, 37.4f, 71.0f);
	letterWidth[5] = 37.4f;
		
	// D 
	vcg->addFrame(284.48f, 0.0f, 46.0f, 71.0f);
	letterWidth[6] = 46.0f;
		
	// d 
	vcg->addFrame(334.645f, 0.0f, 42.0f, 72.0f);
	letterWidth[7] = 42.0f;
		
	// E 
	vcg->addFrame(381.0f, 0.0f, 40.6f, 72.0f);
	letterWidth[8] = 40.6f;
		
	// e 
	vcg->addFrame(425.45f, 0.0f, 38.0f, 72.0f);
	letterWidth[9] = 38.0f;
		
	// F 
	vcg->addFrame(468.63f, 0.0f, 38.1f, 72.0f);
	letterWidth[10] = 38.1f;
		
	// f 
	vcg->addFrame(508.635f, 0.0f, 27.3f, 72.0f);
	letterWidth[11] = 27.3f;
		
	// Row 2 Start
	// G 
	vcg->addFrame(0.0f, 72.0f, 45.7f, 72.0f);
	letterWidth[12] = 45.7f;
		
	// g
	vcg->addFrame(50.8f, 72.0f, 41.5f, 72.0f);
	letterWidth[13] = 41.5f;
		
	// H 
	vcg->addFrame(97.79f, 72.0f, 46.3f, 71.0f);
	letterWidth[14] = 46.3f;
		
	// h 
	vcg->addFrame(149.225f, 72.0f, 41.2f, 72.0f);
	letterWidth[15] = 41.2f;
		
	// I 
	vcg->addFrame(193.04f, 72.0f, 16.5f, 72.0f);
	letterWidth[16] = 16.5f;
		
	// i 
	vcg->addFrame(215.9f, 72.0f, 13.0f, 71.0f);
	letterWidth[17] = 13.5f;
		
	// J 
	vcg->addFrame(231.775f, 72.0f, 36.2f, 72.0f);
	letterWidth[18] = 36.2f;
		
	// j 
	vcg->addFrame(267.97f, 72.0f, 22.8f, 72.0f);
	letterWidth[19] = 22.8f;
		
	// K 
	vcg->addFrame(295.91f, 72.0f, 47.0f, 71.0f);
	letterWidth[20] = 47.0f;
		
	// k 
	vcg->addFrame(347.34f, 72.0f, 35.5f, 72.0f);
	letterWidth[21] = 37.0f;
		
	// L 
	vcg->addFrame(387.985f, 72.0f, 38.7f, 72.0f);
	letterWidth[22] = 38.7f;
		
	// l 
	vcg->addFrame(427.0f, 72.0f, 20.0f, 72.0f);
	letterWidth[23] = 20.0f;
		
	// M
	vcg->addFrame(451.485f, 72.0f, 56.0f, 71.0f);
	letterWidth[24] = 56.0f;
		
	// m 
	vcg->addFrame(510.54f, 72.0f, 58.4f, 72.0f);
	letterWidth[25] = 58.4f;
		
	// Row 3 Start
	// N 
	vcg->addFrame(0.0f, 144.0f, 43.1f, 72.0f);
	letterWidth[26] = 45.0f;
		
	// n
	vcg->addFrame(47.625f, 144.0f, 40.6f, 71.0f);
	letterWidth[27] = 40.6f;
		
	// O  
	vcg->addFrame(92.71f, 144.0f, 52.0f, 72.0f);
	letterWidth[28] = 52.0f;
		
	// o  
	vcg->addFrame(148.59f, 144.0f, 40.0f, 71.0f);
	letterWidth[29] = 40.0f;
		
	// P 
	vcg->addFrame(194.95f, 144.0f, 41.0f, 72.0f);
	letterWidth[30] = 41.0f;
		
	// p
	vcg->addFrame(242.57f, 144.0f, 38.1f, 72.0f);
	letterWidth[31] = 38.1f;
		
	// Q 
	vcg->addFrame(284.48f, 144.0f, 54.0f, 72.0f);
	letterWidth[32] = 54.0f;
		
	// q 
	vcg->addFrame(340.99f, 144.0f, 38.7f, 72.0f);
	letterWidth[33] = 38.7f;
		
	// R 
	vcg->addFrame(386.715f, 144.0f, 48.2f, 72.0f);
	letterWidth[34] = 48.2f;
		
	// r 
	vcg->addFrame(437.515f, 144.0f, 27.3f, 72.0f);
	letterWidth[35] = 27.3f;
		
	// S  
	vcg->addFrame(464.82f, 144.0f, 43.0f, 72.0f);
	letterWidth[36] = 45.0f;
		
	// s 
	vcg->addFrame(511.81f, 144.0f, 36.2f, 72.0f);
	letterWidth[37] = 36.2f;
		
	// Row 4 Start
	// T 
	vcg->addFrame(0.0f , 216.0f, 40.6f, 72.0f);
	letterWidth[38] = 40.6f;
		
	// t 
	vcg->addFrame(41.91f, 216.0f, 26.0f, 72.0f);
	letterWidth[39] = 26.0f;
		
	// U 
	vcg->addFrame(69.85f, 216.0f, 42.5f, 72.0f);
	letterWidth[40] = 42.5f;
		
	// u
	vcg->addFrame(114.3f, 216.0f, 46.0f, 72.0f);
	letterWidth[41] = 46.0f;
		
	// V 
	vcg->addFrame(160.655f, 216.0f, 48.8f, 72.0f);
	letterWidth[42] = 48.8f;
		
	// v 
	vcg->addFrame(212.725f, 216.0f, 36.2f, 72.0f);
	letterWidth[43] = 36.2f;
		
	// W
	vcg->addFrame(249.555f, 216.0f, 67.3f, 72.0f);
	letterWidth[44] = 67.3f;
		
	// w
	vcg->addFrame(318.0f, 216.0f, 56.5f, 72.0f);
	letterWidth[45] = 56.5f;
		
	// X
	vcg->addFrame(373.38f, 216.0f, 47.0f, 72.0f);
	letterWidth[46] = 47.0f;
		
	// x 
	vcg->addFrame(423.0f, 216.0f, 37.0f, 72.0f);
	letterWidth[47] = 37.0f;
		
	// Y 
	vcg->addFrame(460.375f, 216.0f, 49.5f, 71.0f);
	letterWidth[48] = 49.5f;
		
	// y 
	vcg->addFrame(509.905f, 216.0f, 38.7f, 72.0f);
	letterWidth[49] = 38.7f;
		
	// Z 
	vcg->addFrame(549.91f, 216.0f, 43.8f, 72.0f);
	letterWidth[50] = 43.8f;
		
	// z  
	vcg->addFrame(593.725f, 216.0f, 36.2f, 72.0f);
	letterWidth[51] = 36.2f;
		
	// Row 4 Start 
 	// 0  
	vcg->addFrame(0.0f , 288.0f, 35.5f, 54.0f);
	letterWidth[52] = 35.5f;
		
	// 1 
	vcg->addFrame(41.91f, 288.0f, 26.0f, 54.0f);
	letterWidth[53] = 26.0f;
		
	// 2 
	vcg->addFrame(78.74f, 288.0f, 36.2f, 54.0f);
	letterWidth[54] = 36.2f;
		
	// 3
	vcg->addFrame(118.745f, 288.0f, 36.8f, 54.0f);
	letterWidth[55] = 36.8f;
		
	// 4
	vcg->addFrame(157.48f, 288.0f, 40.0f, 54.0f);
	letterWidth[56] = 40.0f;
		
	// 5
	vcg->addFrame(199.39f, 288.0f, 36.2f, 54.0f);
	letterWidth[57] = 36.2f;
		
	// 6
	vcg->addFrame(239.395f, 288.0f, 36.2f, 54.0f);
	letterWidth[58] = 36.2f;
		
	// 7 
	vcg->addFrame(279.4f, 288.0f, 36.2f, 54.0f);
	letterWidth[59] = 36.2f;
		
	// 8 
	vcg->addFrame(319.405f, 288.0f, 35.5f, 54.0f);
	letterWidth[60] = 35.5f;
		
	// 9 
	vcg->addFrame(358.775f, 288.0f, 36.8f, 54.0f);
	letterWidth[61] = 36.8f;
		
	// : 
	vcg->addFrame(403.86f, 288.0f, 12.0f, 54.0f);
	letterWidth[62] = 12.0f;
		
	// . 
	vcg->addFrame(425.45f, 288.0f, 12.0f, 54.0f);
	letterWidth[63] = 12.0f;
		
	// % 
	vcg->addFrame(442.595f, 288.0f, 61.0f, 54.0f);
	letterWidth[64] = 61.0f;
		
	// - 
	vcg->addFrame(508.0f, 288.0f, 24.0f, 54.0f);
	letterWidth[65] = 24.0f;
		
	// '/'
	vcg->addFrame(534.0f, 288.0f, 24.0f, 54.0f);
	letterWidth[66] = 24.0f;
		
	// '?'
	vcg->addFrame(564.0f, 288.0f, 43.0f, 54.0f);
	letterWidth[67] = 43.0f;

	verts = vcg->getVertices();
	cords = vcg->getCoords();
	delete(vcg);
}