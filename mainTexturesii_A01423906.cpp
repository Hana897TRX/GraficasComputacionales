#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <glut.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <time.h>

using namespace std;

typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned char uchar;

int w = 640, h = 480;

// Global variables
// ------------------------------------
// Light Components
static float globAmb = 0.3;
static float globDif = 0.4;
static float globSpe = 0.7;

// Material Components
static float globMatAmb = 0.5;
static float globMatDif = 0.5;
static float globMatSpe = 0.5;
static float globExp = 4.0;

static float xSpeed = 0.0, ySpeed = 0.0, xAngle = 0.0, yAngle = 0.0;

GLfloat texParam = GL_REPLACE;

//TextureRepeat
float textureRepeat = 1.0;

static int texSelect = 0;

// Cylinder parameters
static int m = 10;
static int n = 3;
static float height = 3.0;
static float radius = 1.0;

#define PI 3.1416

static GLuint name[6];

fstream inf; // global in this file for convenience

// A few class definitions
class mRGB {
public:
	unsigned char r,g,b;

	mRGB(){r = g = b = 0;}
	mRGB(mRGB& p){r = p.r; g = p.g; b = p.b;}
	mRGB(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb;}
	void set(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb;}
};

ushort getShort() //helper function
{ //BMP format uses little-endian integer types
  // get a 2-byte integer stored in little-endian form
		char ic;
		ushort ip;
		inf.get(ic); ip = ic;  //first byte is little one
		inf.get(ic);  ip |= ((ushort)ic << 8); // or in high order byte
		return ip;
}
//<<<<<<<<<<<<<<<<<<<< getLong >>>>>>>>>>>>>>>>>>>
ulong getLong() //helper function
{  //BMP format uses little-endian integer types
   // get a 4-byte integer stored in little-endian form
		ulong ip = 0;
		char ic = 0;
		unsigned char uc = ic;
		inf.get(ic); uc = ic; ip = uc;
		inf.get(ic); uc = ic; ip |=((ulong)uc << 8);
		inf.get(ic); uc = ic; ip |=((ulong)uc << 16);
		inf.get(ic); uc = ic; ip |=((ulong)uc << 24);
		return ip;
	}

class RGBpixmap {
public:
	int nRows, nCols;
	mRGB *pixel;

	float gr, gg, gb;

	void MakeCheckerBoard();
	void MakeShadedCircle();
	void MakeRandom();
	int readBMPFile(char *fname);

	void SetTexColor(float rin, float gin, float bin);
	void SetTexture(GLuint textureName);
};

void RGBpixmap::SetTexColor(float rin, float gin, float bin)
{
	// Set multipliers to set the color of the parameterized textures
	gg = gin;
	gr = rin;
	gb = bin;
}

void RGBpixmap::MakeCheckerBoard()
{
	// Set size of the checkerboard
	nRows = nCols = 64;
	int numBytes = 3*nRows*nCols;
	long count = 0;
	pixel = new mRGB[numBytes];

	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			int c = (((i&8)^(j&8))*255);
			pixel[count].r = static_cast<unsigned char>(gr*c);
			pixel[count].g = static_cast<unsigned char>(gg*c);
			pixel[count++].b = static_cast<unsigned char>(gb*c);
		}
}

void RGBpixmap::MakeRandom()
{
	// assign random rgb values
	nRows = nCols = 64;
	int numBytes = 3*nRows*nCols;
	long count = 0;
	pixel = new mRGB[numBytes];

	// TO DO
	// Assign random values for each pixel
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			int val = rand();
			pixel[count].r = static_cast<unsigned char>(gr* val);
			val = rand();
			pixel[count].g = static_cast<unsigned char>(gr * val);
			val = rand();
			pixel[count++].b = static_cast<unsigned char>(gr * val);
		}
}

void RGBpixmap::MakeShadedCircle()
{
	// Make a shaded circle
	nRows = nCols = 64;
	int numBytes = 3*nRows*nCols;
	pixel = new mRGB[numBytes];
	float r, val;
	long count = 0;

	// TO DO
	// Assign pixel vales based on shaded circle given in class presentations
	// Include multipliers (gr, gg, gb) to give the texture a color
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			// TO DO 
			// Assign pixel values
			pixel[count].r = (unsigned char)(gr * 255.0);
			pixel[count].g = (unsigned char)(gg * 255.0) * ((float)(i + j) / (float)(nRows + nCols));
			pixel[count++].b = (unsigned char)(gb * 255.0);
		}
}

int RGBpixmap::readBMPFile(char *fname)
{  // Read into memory an mRGB image from an uncompressed BMP file.
	// return 0 on failure, 1 on success
	inf.open(fname, ios::in|ios::binary); //read binary char's
	if(!inf){ cout << " can't open file: " << fname << endl; return 0;}
	int k, row, col, numPadBytes, nBytesInRow;
	// read the file header information
	char ch1, ch2;
	inf.get(ch1); inf.get(ch2); //type: always 'BM'
	ulong fileSize =      getLong();
	ushort reserved1 =    getShort();    // always 0
	ushort reserved2= 	getShort();     // always 0
	ulong offBits =		getLong(); // offset to image - unreliable
	ulong headerSize =     getLong();     // always 40
	ulong numCols =		getLong(); // number of columns in image
	ulong numRows = 		getLong(); // number of rows in image
	ushort planes=    	getShort();      // always 1
	ushort bitsPerPixel=   getShort();    //8 or 24; allow 24 here
	ulong compression =    getLong();      // must be 0 for uncompressed
	ulong imageSize = 	getLong();       // total bytes in image
	ulong xPels =    	getLong();    // always 0
	ulong yPels =    	getLong();    // always 0
	ulong numLUTentries = getLong();    // 256 for 8 bit, otherwise 0
	ulong impColors = 	getLong();       // always 0
	if(bitsPerPixel != 24)
	{ // error - must be a 24 bit uncompressed image
		cout << "not a 24 bit/pixelimage, or is compressed!\n";
		inf.close(); return 0;
	}
	//add bytes at end of each row so total # is a multiple of 4
	// round up 3*numCols to next mult. of 4
	nBytesInRow = ((3 * numCols + 3)/4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols; // need this many
	nRows = numRows; // set class's data members
	nCols = numCols;
    pixel = new mRGB[nRows * nCols]; //make space for array
	if(!pixel) return 0; // out of memory!
	long count = 0;
	char dum;
	for(row = 0; row < nRows; row++) // read pixel values
	{
		for(col = 0; col < nCols; col++)
		{
			char r,g,b;
			inf.get(b); inf.get(g); inf.get(r); //read bytes
			pixel[count].r = r; //place them in colors
			pixel[count].g = g;
			pixel[count++].b = b;
		}
   		for(k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
			inf >> dum;
	}
	inf.close(); return 1; // success
}

void RGBpixmap::SetTexture(GLuint textureName)
{
	// Set texture parameters to initial values
	// Set wrapping and interpolation

	// TO DO
	// Bind 2D textures, based on input name
	// Set appropriate texture parameters
	// Generate 2D texture image - use class member variables: nCols, nRows, pixel

	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nCols, nRows, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	// This line has to be called EACH TIME the texture mode changes
	if(texParam == GL_REPLACE)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
}

RGBpixmap myTexs[6];

void updateLights( void )
{
	// Update LIGHT properties
	GLfloat myAmb[] = {globAmb, globAmb, globAmb, 1.0};
	GLfloat myDif[] = {globDif, globDif, globDif, 1.0};
	GLfloat mySpe[] = {globSpe, globSpe, globSpe, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, myAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, myDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mySpe);
}

void init( void )
{
	srand(time(NULL));
	glClearColor(0.75, 0.75, 0.75, 1.0);
	//glClearColor( 1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Get OpenGL to automatically generate the texture "names"
	glGenTextures(6, name);

	// TO DO
	// Create and bind all textures using name[i], myTexs[i]

	myTexs[0].SetTexColor(0.25, 0.48, 0.55);
	myTexs[0].MakeCheckerBoard();
	myTexs[0].SetTexture(name[0]);

	myTexs[1].SetTexColor(0.8, 0.7, 0.25);
	myTexs[1].MakeShadedCircle();
	myTexs[1].SetTexture(name[1]);

	myTexs[2].SetTexColor(0.2, 0.8, 0.55);
	myTexs[2].MakeRandom();
	myTexs[2].SetTexture(name[2]);

	myTexs[3].SetTexColor(0.65, 0.28, 0.84);
	myTexs[3].MakeCheckerBoard();
	myTexs[3].SetTexture(name[3]);

	if (myTexs[4].readBMPFile((char*)"C:\\Users\\Hana897TRX\\Documents\\Universities\\Tec\\Quinto Semestre\\Graficas\\cppCodes\\GraficasComputacionales\\monito.bmp") == 0)
		cout << "impossible to read";
	else {
		myTexs[4].SetTexture(name[4]);
	}

	if (myTexs[5].readBMPFile((char*)"C:\\Users\\Hana897TRX\\Documents\\Universities\\Tec\\Quinto Semestre\\Graficas\\cppCodes\\GraficasComputacionales\\oldman.bmp") == 0)
		cout << "impossible to read";
	else {
		myTexs[5].SetTexture(name[5]);
	}


	// Using RGBpixmap member functions (MakeCheckerBoard(), MakeShadedCircle(), MakeRandom(), readJPGFile() ):
	// Create 6 textures
	// Set/assign these 6 textures (HINT: Use SetTexture())
	// If appropriate (checkerboard, shaded circle, random values), assign a color
	// Set at least one checkerboard
	// Set at least one shaded circle
	// Set at least one random valued texture
	// All should be different colors
	// Set at least one image. NOTE: complete image name/path must be used
	// At least one pattern should repeat itself once (i.e. two whole patterns on the face) Hint: Done in display()
	// At least one pattern should repeat itself twice (i.e. three whole patterns on the face) Hint: Done in display()
	// NOTE: Do not make the random pattern repeat itself

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set light
	GLfloat myPos[] = {10.0, 3.0, 3.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, myPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Update LIGHT properties
	updateLights();

	// Translate camera
	glRotated(15.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -8.0);
}

void setMaterials( void )
{
	GLfloat matAmbi[] = {globMatAmb, globMatAmb, globMatAmb, 1.0};
	GLfloat matDiff[] = {globMatDif, globMatDif, globMatDif, 1.0};
	GLfloat matSpec[] = {globMatSpe, globMatSpe, globMatSpe, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbi);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, &globExp);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);
	glViewport(0, 0, w * 0.5, h);
	// Set material properties
	setMaterials();

	// TO DO
	// Set texture mode

	// TO DO
	// Bind texture i using name[i], depending on parameter texSelect
	//myTexs[texSelect].SetTexture(name[texSelect]);
	glBindTexture(GL_TEXTURE_2D, name[texSelect]);
	//myTexs[texSelect].SetTexture(name[texSelect]);

	// Create cylinder from scratch
	// "circular" base around XZ (use m divisions to divide circle (slices))
	// height along Y (use n divisions (stacks))
	// NOTE: We assume the cyclinder is centered around the origin, with "height" height
	float angle, angleNext;
	float frac, fracNext;
	float H, HNext;
	float div, divNext;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < m; i++){
	    frac = (float)(i)/(float)(m);
        fracNext = (float)(i+1)/(float)(m);
        angle = 2.0*PI*frac;
        angleNext = 2.0*PI*fracNext;

		GLfloat mat_ambient[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
		GLfloat diffuse[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
		GLfloat specular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
		float shine = 25.6f;


		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shine);

	    for (int j = 0; j < n; j++){
	        div = (float)(j)/(float)(n);
	        divNext = (float)(j+1)/(float)(n);
	        H = height*div - height/2.0;
	        HNext = height*divNext - height/2.0;

	        // TO DO
	        // Set texture coordinates for each vertex
	        // Add comments - Explain how the cylinder is created

			glTexCoord2f(textureRepeat * (float) i / (float)m, (float) j / (float) n);
			glVertex3f(radius * sin(angle), H, radius * cos(angle));
			glTexCoord2f(textureRepeat * (float)(i + 1) / (float)m, (float) j / (float)n);
			glVertex3f(radius * sin(angleNext), H, radius * cos(angleNext));
			glTexCoord2f(textureRepeat * (float)(i + 1) / (float)m, (float)(j + 1) / (float)n);
			glVertex3f(radius * sin(angleNext), HNext, radius * cos(angleNext));
			glTexCoord2f(textureRepeat * (float)i / (float)m, (float)(j + 1) / (float)n);
			glVertex3f(radius * sin(angle), HNext, radius * cos(angle));
	    }
	}
	glEnd();
	glPopMatrix();

	//Second ViewPort
	glViewport(w * 0.5, 0, w , h );
	glPushMatrix();
	glBegin(GL_QUADS);

		glTexCoord2f(textureRepeat * 0, 0);
		glVertex3f(-3.0, -1.5, 0.0);
		glTexCoord2f(textureRepeat * 0, 1);
		glVertex3f(-3.0, 1.5, 0.0);
		glTexCoord2f(textureRepeat * 1, 1);
		glVertex3f(0.0, 1.5, 0.0);
		glTexCoord2f(textureRepeat * 1, 0);
		glVertex3f(0.0, -1.5, 0.0);

	glEnd();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void spinner( void )
{
	// alter angles by small amount
	xAngle += xSpeed;
	yAngle += ySpeed;
	display();
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -6.0);
	glRotated(15.0, 1.0, 0.0, 0.0);
}

// Use the arrow keys (in OpenGL) for controlling cylinder parameters
void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_UP :
				m += 1;
				break;
		case GLUT_KEY_DOWN :
				m -= 1;
				if (m < 3)
                    m = 3;
				break;
		case GLUT_KEY_LEFT :
				n += 1;
				break;
        case GLUT_KEY_RIGHT :
				n -= 1;
				if (n < 1)
                    n = 1;
				break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

		case 't':
            // TO DO
            // Update value of texParam to take the different texture modes
			if (texSelect == GL_REPLACE)
				texSelect = GL_MODULATE;
			else
				texSelect = GL_REPLACE;
			glutPostRedisplay();
			break;
		// TO DO
		// Update value of texSelect for each number key 0-5
		case 'l':
			if(textureRepeat < 8)
				textureRepeat++;
			break;
		case 'L':
			if (textureRepeat >= 2)
				textureRepeat--;
			break;
		case'j':
			n++;
			break;
		case 'J':
			n--;
			break;
		case 'h':
			m++;
			break;
		case 'H':
			m--;
			break;
		case 'g':
			height++;
			break;
		case 'G':
			height--;
			break;
		case 'u':
			radius++;
			break;
		case 'U':
			radius--;
			break;
		case '0':
			texSelect = 0;
			break;

		case '1':
			texSelect = 1;
			break;

		case '2':
			texSelect = 2;
			break;

		case '3':
			texSelect = 3;
			break;

		case '4':
			texSelect = 4;
			break;

		case '5':
			texSelect = 5;
			break;

		case '+':
			xSpeed += 0.1;
			break;
		case '*':
			xSpeed -= 0.1;
            break;
		case '-':
			ySpeed += 0.1;
			break;
		case '_':
			ySpeed -= 0.1;
			break;

		// Set Smooth Shading (Gouraud)
		case 's':
			glShadeModel(GL_SMOOTH);
			break;
		// Set Flat Shading
		case 'f':
			glShadeModel(GL_FLAT);
			break;

		// Increase Ambient Light component (light)
		case 'A':
			globAmb = min(1.0,globAmb+0.1);
			break;
		// Decrease Ambient Light component (light)
		case 'a':
			globAmb = max(0.0,globAmb-0.1);
			break;

		// Increase Diffuse Light component (light)
		case 'D':
			globDif = min(1.0,globDif+0.1);
			break;
		// Decrease Diffuse Light component (light)
		case 'd':
			globDif = max(0.0,globDif-0.1);
			break;

		// Increase Specular Light component (light)
		case 'P':
			globSpe = min(1.0,globSpe+0.1);
			break;
		// Decrease Specular Light component (light)
		case 'p':
			globSpe = max(0.0,globSpe-0.1);
			break;

		// Increase Ambient refelctivity component (material)
		case 'M':
			globMatAmb = min(1.0,globMatAmb+0.1);
			break;
		// Decrease Ambient refelctivity component (material)
		case 'm':
			globMatAmb = max(0.0,globMatAmb-0.1);
			break;

		// Increase Diffuse refelctivity component (material)
		case 'N':
			globMatDif = min(1.0,globMatDif+0.1);
			break;
		// Decrease Diffuse refelctivity component (material)
		case 'n':
			globMatDif = max(0.0,globMatDif-0.1);
			break;

		// Increase Specular refelctivity component (material)
		case 'B':
			globMatSpe = min(1.0,globMatSpe+0.1);
			break;
		// Decrease Specular refelctivity component (material)
		case 'b':
			globMatSpe = max(0.0,globMatSpe-0.1);
			break;

		// Increase Specular Exponent (material)
		case 'E':
			globExp = min(128.0,globExp+2.0);
			break;
		// Decrease Specular Exponent (material)
		case 'e':
			globExp = max(0.0,globExp-2.0);
			break;

		// Reset All Light Values
		case 'R':
			globAmb = 0.3;
			globDif = 0.4;
			globSpe = 0.7;
			globExp = 4.0;

			globMatAmb = 0.5;
			globMatDif = 0.5;
			globMatSpe = 0.5;

			break;
        case 'r':
            xAngle = 0.0;
            yAngle = 0.0;
            break;

		// Quit
		case 0x1B:
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			break;
	}
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Texture Example");

	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinner);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
	return 0;
}
