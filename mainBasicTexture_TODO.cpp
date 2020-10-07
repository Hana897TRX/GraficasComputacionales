#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
typedef unsigned char uchar;
#define PI 3.1416

// enumerator for selecting lights
enum LightSelect { NONE, WHITE, RED, GREEN, BLUE };
LightSelect lightSelect;
float lightInc = 0.5;

// globals for changing overall orientation of model
static float rotX = 0.0;
static float rotY = 0.0;

// Light Positions
GLfloat light_position0[] = { 0.0, 4.0, 0.0, 0.0 };   // white light, position from above
GLfloat light_position1[] = { 4.0, 0.0, 0.0, 0.0 };  // red light, position to the right
GLfloat light_position2[] = { -4.0, 0.0, 0.0, 0.0 };  // green light, position to the left
GLfloat light_position3[] = { 0.0, -4.0, 0.0, 0.0 };  // blue light, position to the bottom
static float lightIntensity = 0.5;
bool toggleShadeModel;

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

void drawColoredCylinderS(float r, float g, float b, float rs, float gs, float bs, float exp, float radius, float height, int slices, int stacks) {
	float cyAngleInc = 2.0 * M_PI / (float)slices;
	float cyHeightInc = height / (float)stacks;

	//Define material properties
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { rs, gs, bs, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &exp);

	glRotated(-120, 1.0, 0.0, 0.0);
	for (int rad = 0; rad < slices; rad++)
		for (int h = 0; h < stacks; h++) {
			glBegin(GL_QUADS);

			//0
			glTexCoord2f((float)rad / (float)slices, (float)h / (float)stacks);
			glVertex3f(radius * sin((float)rad * cyAngleInc), radius * cos((float)rad * cyAngleInc), h * cyHeightInc);
			glNormal3f(radius * sin((float)rad * cyAngleInc), radius * cos((float)rad * cyAngleInc), h * cyHeightInc);

			//1
			glTexCoord2f((float)(rad + 1) / (float)slices, (float)h / (float)stacks);
			glVertex3f(radius * sin((float)rad * cyAngleInc), radius * cos((float)rad * cyAngleInc), (h + 1) * cyHeightInc);
			glNormal3f(radius * sin((float)rad * cyAngleInc), radius * cos((float)rad * cyAngleInc), (h + 1) * cyHeightInc);

			//2
			glTexCoord2f((float)(rad + 1) / (float)slices, (float)(h + 1) / (float)stacks);
			glVertex3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc), (h + 1) * cyHeightInc);
			glNormal3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc), (h + 1) * cyHeightInc);

			//3
			glTexCoord2f((float)rad / (float)slices, (float)(h + 1) / (float)stacks);
			glVertex3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc), h * cyHeightInc);
			glNormal3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc), h * cyHeightInc);
			glEnd();
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// Initialization function
void init(void)
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

	//LIGHTNING
	//---------------------
	glClearColor(0.3, 0.32, 0.354, 0.0);

	// Set light properties...
	// Light 0
	GLfloat light_color0[] = { 0.0, 0.0, lightIntensity, 1.0 };      // white light

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);     // white light
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color0);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color0);

	// Light 1
	GLfloat light_color1[] = { lightIntensity, 0.0, 0.0, 1.0 }; //red
	GLfloat light_color1_amb[] = { lightIntensity * 0.3, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);     // white light
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_color1_amb);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_color1);

	// Light 2
	GLfloat light_color2[] = { 0.0, lightIntensity, 0.0, 1.0 }; //green
	GLfloat light_color2_amb[] = { lightIntensity * 0.3, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);     // white light
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_color2_amb);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_color2);

	// Light 3
	GLfloat light_color3[] = { 0.0, 0.0, lightIntensity, 1.0 }; //blue
	GLfloat light_color3_amb[] = { lightIntensity * 0.3, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);     // white light
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_color3_amb);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color3);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_color3);

	// Set shading model to use
	// TO DO 
	toggleShadeModel = false;

	// Enable lighting
	glEnable(GL_LIGHTING);
	// Enable correct vector calculation
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Activate (enable) light 0
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);
	// Activate (enable) light 1-3
	// TO DO

	// for KB select and moving lights
	lightSelect = NONE;

	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);
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
	/*glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f( -0.5, -0.5, 0.0 );
    
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.5, -0.5, 0.0);
    
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, 0.0 );
    
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.5, 0.5, 0.0 );

	glEnd();*/
	drawColoredCylinderS(0.2, 1.0, 0.2, 0.8, 0.8, 0.8, 50.0, 1.0, 2.0, 64, 64);

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
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.01, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the look at parameters
	gluLookAt(0.0, 3.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
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
