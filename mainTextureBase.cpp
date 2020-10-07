#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <glut.h>

typedef unsigned char uchar;
#define PI 3.1416

// A Class definition to hold the pixel data
class mRGB {
public:
	unsigned char r,g,b;

	mRGB(){r = g = b = 0;}
	mRGB(mRGB& p){r = p.r; g = p.g; b = p.b;}
	mRGB(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb;}
	void set(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb;}
};


// Variables for TEXTURE
static GLuint name[1];
int nRows, nCols;
mRGB *pixel;


// Create the texture data using a method - this way we don't need to load an image
void MakeShadedCircle()
{
	// Make a shaded circle
	nRows = 64;
	nCols = 64;
	int numBytes = 3*nRows*nCols;
	pixel = new mRGB[numBytes];
	float r, val;
	long count = 0;

	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			// TO DO 
			// Assign pixel values
			pixel[count].r = (unsigned char)(0.0*255.0);
			pixel[count].g = (unsigned char)(0.8*255.0)*((float)(i+j)/(float)(nRows+ nCols));
			pixel[count++].b = (unsigned char)(0.0*255.0);
		}
}

// Relate the texture (pixel) to OpenGL
void SetTexture(GLuint textureName)
{
	// Set texture parameters to initial values
	// Set wrapping and interpolation
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nCols, nRows, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	// This line has to be called EACH TIME the texture mode changes
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

// Initialization function
void init( void )
{
	glClearColor(0.75, 0.75, 0.75, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// Get OpenGL to automatically generate the texture "names"
	glGenTextures(1, name);

	// Create the texture data
	MakeShadedCircle();

	// Assign the texture
	// Link the information in pixel to OpenGL
	SetTexture(name[0]);
}

// Display function - Draw polygons with texture
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// select which texture is displayed
	glBindTexture(GL_TEXTURE_2D, name[0]);

	// Create a simple quad polygon from scratch
	// Polygon has lower left corner (x,y) = (-0.5,-0.5)
	// Polygon has upper right corner (x,y) = (0.5,0.5)
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f( -0.5, -0.5, 0.0 );
    
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.5, -0.5, 0.0);
    
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, 0.0 );
    
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.5, 0.5, 0.0 );

	glEnd();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// Standard Reshape method
void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the view volume - NOTE: It is ortho!!
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.01, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the look at parameters
	gluLookAt(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Standard Keyboard method
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
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

// Main entry point into program
int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Texture Example");

	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
