#include "TextRender.h"


TextRender::TextRender(){}
TextRender::~TextRender(){}

// Draw text to the screen with the following properties 
void TextRender::drawText(GLHandler mgl, std::string text, float x, float y, float rotation, float fontSize){
	float scale = fontSize / TR_FONT_SIZE;
	float length = (float)text.length();

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

	if (length > 0){
		float size = 0;

		for (int i =0; i < length; i++){
			char c = text.at(i);
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
}

// Measure how long the text will be on screen
float TextRender::measureString(std::string text, float size){
	// Variables use to get length 
	float scale = size/72.0f;
	float maxSize = 0.0f;
	float length = 0;
	int textLength = text.length();
	char c; 

	for (int i = 0; i < textLength; i++){
		c = text.at(i);

		// Check if we hit the end of the line 
		if (c == '\n'){
			if (length > maxSize)
				maxSize = length;
			length = 0.0f;
		}
		// Otherwise add normal length 
		else {
			length += getLetterWidth(c);
		}
	}

	// Check against max size 
	if (maxSize > length)
		length = maxSize;
		
	return length * scale;
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
		case '[':
			return 68;
		case ']':
			return 69;
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
	case '[':
		return letterWidth[68];
	case ']':
		return letterWidth[69];
	default:
		return 30.0f;
	}
}

// Setup the buffers for the font 
void TextRender::createFontBuffers(VertCordGenerator* vcg){
	// A 
	vcg->addFrame(0.0f, 0.0f, 52.7f, 71.0f);
	letterWidth[0] = 53.0f;
		
	// a  
	vcg->addFrame(54.61f,0.0f,36.2f,72.0f);
	letterWidth[1] =  40.0f;
		
	// B 
	vcg->addFrame(97.79f, 0.0f, 43.8f, 71.0f);
	letterWidth[2] = 44.0f;
		
	// b  
	vcg->addFrame(148.59f, 0.0f, 36.8f, 71.0f);
	letterWidth[3] = 37.0f;
		
	// C 
	vcg->addFrame(190.5f, 0.0f, 46.4f, 71.0f);
	letterWidth[4] = 47.0f;
		
	// c 
	vcg->addFrame(241.3f, 0.0f, 37.4f, 71.0f);
	letterWidth[5] = 38.0f;
		
	// D 
	vcg->addFrame(284.48f, 0.0f, 46.0f, 71.0f);
	letterWidth[6] = 46.0f;
		
	// d 
	vcg->addFrame(334.645f, 0.0f, 42.0f, 72.0f);
	letterWidth[7] = 42.0f;
		
	// E 
	vcg->addFrame(381.0f, 0.0f, 40.6f, 72.0f);
	letterWidth[8] = 41.0f;
		
	// e 
	vcg->addFrame(425.45f, 0.0f, 38.0f, 71.0f);
	letterWidth[9] = 38.0f;
		
	// F 
	vcg->addFrame(468.63f, 0.0f, 38.1f, 72.0f);
	letterWidth[10] = 39.0f;
		
	// f 
	vcg->addFrame(508.635f, 0.0f, 27.3f, 72.0f);
	letterWidth[11] = 28.0f;
		
	// Row 2 Start
	// G 
	vcg->addFrame(0.0f, 72.0f, 45.7f, 72.0f);
	letterWidth[12] = 46.0f;
		
	// g
	vcg->addFrame(50.8f, 72.0f, 41.5f, 72.0f);
	letterWidth[13] = 42.0f;
		
	// H 
	vcg->addFrame(97.79f, 72.0f, 46.3f, 71.0f);
	letterWidth[14] = 47.0f;
		
	// h 
	vcg->addFrame(149.225f, 72.0f, 41.2f, 72.0f);
	letterWidth[15] = 42.0f;
		
	// I 
	vcg->addFrame(193.04f, 72.0f, 16.5f, 72.0f);
	letterWidth[16] = 17.0f;
		
	// i 
	vcg->addFrame(215.9f, 72.0f, 13.0f, 71.0f);
	letterWidth[17] = 14.0f;
		
	// J 
	vcg->addFrame(231.775f, 72.0f, 36.2f, 72.0f);
	letterWidth[18] = 37.0f;
		
	// j 
	vcg->addFrame(267.97f, 72.0f, 22.8f, 72.0f);
	letterWidth[19] = 23.0f;
		
	// K 
	vcg->addFrame(295.91f, 72.0f, 47.0f, 71.0f);
	letterWidth[20] = 47.0f;
		
	// k 
	vcg->addFrame(347.34f, 72.0f, 35.5f, 72.0f);
	letterWidth[21] = 37.0f;
		
	// L 
	vcg->addFrame(387.985f, 72.0f, 38.7f, 72.0f);
	letterWidth[22] = 39.0f;
		
	// l 
	vcg->addFrame(427.0f, 72.0f, 20.0f, 72.0f);
	letterWidth[23] = 20.0f;
		
	// M
	vcg->addFrame(451.485f, 72.0f, 56.0f, 71.0f);
	letterWidth[24] = 56.0f;
		
	// m 
	vcg->addFrame(510.54f, 72.0f, 58.4f, 72.0f);
	letterWidth[25] = 59.0f;
		
	// Row 3 Start
	// N 
	vcg->addFrame(0.0f, 144.0f, 43.1f, 72.0f);
	letterWidth[26] = 45.0f;
		
	// n
	vcg->addFrame(47.625f, 144.0f, 40.6f, 71.0f);
	letterWidth[27] = 41.0f;
		
	// O  
	vcg->addFrame(92.71f, 144.0f, 52.0f, 72.0f);
	letterWidth[28] = 52.0f;
		
	// o  
	vcg->addFrame(148.59f, 144.0f, 40.0f, 71.0f);
	letterWidth[29] = 41.0f;
		
	// P 
	vcg->addFrame(194.95f, 144.0f, 41.0f, 72.0f);
	letterWidth[30] = 41.0f;
		
	// p
	vcg->addFrame(242.57f, 144.0f, 38.1f, 72.0f);
	letterWidth[31] = 38.0f;
		
	// Q 
	vcg->addFrame(284.48f, 144.0f, 54.0f, 72.0f);
	letterWidth[32] = 54.0f;
		
	// q 
	vcg->addFrame(340.99f, 144.0f, 38.7f, 72.0f);
	letterWidth[33] = 39.0f;
		
	// R 
	vcg->addFrame(386.715f, 144.0f, 48.2f, 72.0f);
	letterWidth[34] = 49.0f;
		
	// r 
	vcg->addFrame(437.515f, 144.0f, 27.3f, 72.0f);
	letterWidth[35] = 28.0f;
		
	// S  
	vcg->addFrame(464.82f, 144.0f, 43.0f, 72.0f);
	letterWidth[36] = 45.0f;
		
	// s 
	vcg->addFrame(511.81f, 144.0f, 36.2f, 72.0f);
	letterWidth[37] = 37.0f;
		
	// Row 4 Start
	// T 
	vcg->addFrame(0.0f , 216.0f, 40.6f, 72.0f);
	letterWidth[38] = 41.0f;
		
	// t 
	vcg->addFrame(41.91f, 216.0f, 26.0f, 71.0f);
	letterWidth[39] = 26.0f;
		
	// U 
	vcg->addFrame(69.85f, 216.0f, 42.5f, 72.0f);
	letterWidth[40] = 43.0f;
		
	// u
	vcg->addFrame(114.3f, 216.0f, 46.0f, 71.0f);
	letterWidth[41] = 46.0f;
		
	// V 
	vcg->addFrame(160.655f, 216.0f, 48.8f, 72.0f);
	letterWidth[42] = 49.0f;
		
	// v 
	vcg->addFrame(212.725f, 216.0f, 36.2f, 72.0f);
	letterWidth[43] = 37.0f;
		
	// W
	vcg->addFrame(249.555f, 216.0f, 67.3f, 72.0f);
	letterWidth[44] = 68.0f;
		
	// w
	vcg->addFrame(318.0f, 216.0f, 56.5f, 72.0f);
	letterWidth[45] = 57.0f;
		
	// X
	vcg->addFrame(373.38f, 216.0f, 47.0f, 72.0f);
	letterWidth[46] = 47.0f;
		
	// x 
	vcg->addFrame(423.0f, 216.0f, 37.0f, 71.0f);
	letterWidth[47] = 37.0f;
		
	// Y 
	vcg->addFrame(460.375f, 216.0f, 49.5f, 71.0f);
	letterWidth[48] = 50.0f;
		
	// y 
	vcg->addFrame(509.905f, 216.0f, 38.7f, 72.0f);
	letterWidth[49] = 39.0f;
		
	// Z 
	vcg->addFrame(549.91f, 216.0f, 43.8f, 72.0f);
	letterWidth[50] = 44.0f;
		
	// z  
	vcg->addFrame(593.725f, 216.0f, 36.2f, 72.0f);
	letterWidth[51] = 37.0f;
		
	// Row 4 Start 
 	// 0  
	vcg->addFrame(0.0f , 288.0f, 35.5f, 54.0f);
	letterWidth[52] = 36.0f;
		
	// 1 
	vcg->addFrame(41.91f, 288.0f, 26.0f, 54.0f);
	letterWidth[53] = 26.0f;
		
	// 2 
	vcg->addFrame(78.74f, 288.0f, 36.2f, 54.0f);
	letterWidth[54] = 37.0f;
		
	// 3
	vcg->addFrame(118.745f, 288.0f, 36.8f, 54.0f);
	letterWidth[55] = 37.0f;
		
	// 4
	vcg->addFrame(157.48f, 288.0f, 40.0f, 54.0f);
	letterWidth[56] = 40.0f;
		
	// 5
	vcg->addFrame(199.39f, 288.0f, 36.2f, 54.0f);
	letterWidth[57] = 37.0f;
		
	// 6
	vcg->addFrame(239.395f, 288.0f, 36.2f, 54.0f);
	letterWidth[58] = 37.0f;
		
	// 7 
	vcg->addFrame(279.4f, 288.0f, 36.2f, 54.0f);
	letterWidth[59] = 37.0f;
		
	// 8 
	vcg->addFrame(319.405f, 288.0f, 35.5f, 54.0f);
	letterWidth[60] = 36.0f;
		
	// 9 
	vcg->addFrame(358.775f, 288.0f, 36.8f, 54.0f);
	letterWidth[61] = 37.0f;
		
	// : 
	vcg->addFrame(403.86f, 288.0f, 12.0f, 54.0f);
	letterWidth[62] = 12.0f;
		
	// . 
	vcg->addFrame(425.45f, 288.0f, 12.0f, 54.0f);
	letterWidth[63] = 13.0f;
		
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

	// [
	vcg->addFrame(0.0f, 344.0f, 22.0f, 72.0f);
	letterWidth[68] = 22.0f;

	// ]
	vcg->addFrame(24.0f, 344.0f, 22.0f, 72.0f);
	letterWidth[69] = 22.0f;
}