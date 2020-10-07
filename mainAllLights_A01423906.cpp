#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define PI 3.1416

// enumerator for selecting lights
enum LightSelect {NONE, WHITE, RED, GREEN, BLUE};
LightSelect lightSelect;
float lightInc = 0.5;
float rotation = 0.0;
float rotationLight = 0.0;

// globals for changing overall orientation of model
static float rotX = 0.0;
static float rotY = 0.0;

// Set the increment
static float angleInc = 3.0;

static float lightIntensity = 0.5;
static float displace = 3.0;
float horizontalD = 3.0;

bool toggleShadeModel;

// Light Positions
GLfloat light_position0[] = { 0.0, 0.5, 0.0, 0.0};   // white light, position from above - directional
GLfloat light_position1[] = { 0.0, 8.0, 0.0, 1.0 };  // red light, position to the right - spotlight
GLfloat light_position3[] = { 0.0,-4.0, 0.0, 0.0 };  // blue light, position to the bottom
GLfloat fogColor[] = { 0.5, 0.5, 0.5, 1.0 };

GLfloat light_color0[] = { 0.1, 0.1, 0.1, 0.0 };
GLfloat light_emission[] = { 1.0, 1.0, 1.0, 1.0 };

void drawColoredUnitSphere(float r, float g, float b, float rs, float gs, float bs, float exp)
{
    // Define material properties
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { rs, gs, bs, 1.0 };

    // Set material properties, as defined above
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &exp);
    
    glutSolidSphere(1.0, 20, 20);
}

void CreateTriangle(float fposX, float fposY, float fposZ, float sposX, float sposY, float sposZ, float tposX, float tposY, float tposZ) {
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.2, 0.0);
		glVertex3f(fposX, fposY, fposZ);
		glNormal3f(fposX, fposY, fposZ);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(sposX, sposY, sposZ);
		glNormal3f(sposX, sposY, sposZ);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(tposX, tposY, tposZ);
		glNormal3f(tposX, tposY, tposZ);
	glEnd();
}

void CreateCube(float _ox, float _oy, float _oz, float _rm, float _gm, float _bm, float _rd, float _gd, float _bd, float _rs, float _gs, float _bs, float _shine) {
	glPushMatrix();
	GLfloat mat_ambient[] = { _rm, _gm,  _bm, 1.0 };
	GLfloat mat_diffuse[] = { _rd, _gd,  _bd, 1.0 };
	GLfloat mat_specular[] = { _rs, _gs,  _bs, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &_shine);
	glTranslatef(_ox, _oy, _oz);
		//bottom
						//fpz		 | spy           | tpx
		CreateTriangle(0, 0.0, 0.75, 0.75, 0.0, 0.0, 0, 0.0, 0);
		CreateTriangle(0, 0, 0.75, 0.75, 0, 0, 0.75, 0, 0.75);
		//leftSide
		CreateTriangle(0, 0, 0.75, 0, 0.75, 0, 0, 0, 0);
		CreateTriangle(0, 0, 0.75, 0, 0.75, 0, 0, 0.75, 0.75);

		//rightSide
		CreateTriangle(0.75, 0.75, 0, 0, 0.75, 0, 0, 0, 0);
		CreateTriangle(0.75, 0.75, 0, 0.75, 0, 0, 0, 0, 0);

		//top
		CreateTriangle(0.75, 0.75, 0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.0);
		CreateTriangle(0.75, 0.75, 0.0, 0.0, 0.75, 0.75, 0.75, 0.75, 0.75);

		//rightFrontSide
		CreateTriangle(0.75, 0.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
		CreateTriangle(0.75, 0.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75);

		//leftFrontSide
		CreateTriangle(0.0, 0.0, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75, 0.75);
		CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75);
	glPopMatrix();
}

//void CreateRectangle() {
//	//buttom
//	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
//	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.75, 0.0, 0.75);
//	//leftSide
//	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0);
//	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 1.75, 0.75);
//
//	//rightSide
//	CreateTriangle(0.75, 1.75, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0);
//	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
//
//	//top
//	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.0, 1.75, 0.0);
//	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
//
//	//rightFrontSide
//	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
//	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
//
//	//leftFrontSide
//	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
//	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
//}

// Subroutine for drawing a circular disc
void myDisc(float r, float n)
{
    glBegin(GL_TRIANGLE_FAN);
        // origin
        glVertex3f( 0.0f, 0.0, 0.0f);

        // Each vertex around the edge
        // Must draw the first vertex twice, to wrap around
        for (int i = 0; i<=n; i++)
        {
            float angle = 2.0*PI*(float)i/(float)n;
            // Corresponds to the same cylinder parameters
            glVertex3f( r*cos(angle), r*sin(angle), 0.0f);
        }
    glEnd();
}

// Alternate cylinder for drawing
// Draws a upright (vertical) cylinder with two ends
void mySolidCylinder (float r, float h, int n, int m)
{
    glPushMatrix ();

    // Apply translation, so that cylinder is centered at the origin,
    // just like other glut shapes
	glRotated(90, 1.0, 0.0, 0.0);
	float exp = 200.0;

	GLfloat diffuse[] = { 0.67, 0.37, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &exp);

    // draw a cylinder
    GLUquadricObj * qobj = gluNewQuadric ();
    gluQuadricDrawStyle (qobj, GLU_FILL);
    gluCylinder (qobj, r, r, h, n, m);
    gluDeleteQuadric (qobj);

    // draw each of the ends
    myDisc(r, n);

    //glPushMatrix(); // not really needed here, since we exit the function
    glTranslatef (0.0, 0.0, h);
    myDisc(r, n);
    //glPopMatrix ();

    glPopMatrix ();
}

void drawColoredCylinderS(float r, float g, float b, float rs, float gs, float bs, float exp, float radius, float height, int slices, int stacks) {
	glPushMatrix();
	float cyAngleInc = 2.0 * M_PI / (float)slices;
	float cyHeightInc = height / (float)stacks;

	//Define material properties
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { rs, gs, bs, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &exp);
	GLfloat light2_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, light2_emission);


	for (int rad = 0; rad < slices; rad++)
		for (int h = 0; h < stacks; h++) {
			glBegin(GL_QUADS);
			glVertex3f(radius * sin((float)rad* cyAngleInc), radius * cos((float)rad * cyAngleInc),h * cyHeightInc);
			glNormal3f(radius * sin((float)rad* cyAngleInc), radius * cos((float)rad * cyAngleInc),h * cyHeightInc);
			
			glVertex3f(radius * sin((float)rad* cyAngleInc), radius * cos((float)rad * cyAngleInc),(h + 1) * cyHeightInc);
			glNormal3f(radius * sin((float)rad* cyAngleInc), radius * cos((float)rad * cyAngleInc),(h + 1) * cyHeightInc);
			
			glVertex3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc),(h + 1) * cyHeightInc);
			glNormal3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc),(h + 1) * cyHeightInc);
			
			glVertex3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc),h * cyHeightInc);
			glNormal3f(radius * sin((float)(rad + 1) * cyAngleInc), radius * cos((float)(rad + 1) * cyAngleInc),h * cyHeightInc);
			glEnd();
		}
	
	glPopMatrix();
}

void display(void)
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Added controls to rotate the model around
	glPushMatrix();
		glRotatef(rotation, 0.0, 1.0, 0.0);

		//Floor - Obsidian
		glPushMatrix();
			GLfloat mat_ambient[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
			GLfloat mat_diffuse[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
			GLfloat mat_specular[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
			float shine = 38.4f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
			glScaled(3.0, 0.05, 3.0);
			glutSolidCube(1.0);
		glPopMatrix();

		//Cube - Brass
		glPushMatrix();
			glTranslated(-0.5, 0.5, -1.0);
			glScaled(0.5, 0.5, 0.5);
			CreateCube(0.5, 0.0, 0.0, 0.329412f, 0.223529f, 0.027451f, 0.780392f, 0.568627f, 0.113725f, 0.992157f, 0.941176f, 0.807843f, 27.8974);
		glPopMatrix();

		//Sphere - Perl
		glPushMatrix();
			GLfloat mat_ambient1[] = { 0.25f, 0.20725f, 0.20725f, 0.922f };
			GLfloat mat_diffuse1[] = { 1.0f, 0.829f, 0.829f, 0.922f };
			GLfloat mat_specular1[] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
			float shine1 = 11.264f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
			glMaterialfv(GL_FRONT, GL_SHININESS, &shine1);
			glTranslated(1.5, 0.5, 1.0);
			glScaled(0.25, 0.25, 0.25);
			glutSolidSphere(1.0, 120, 120);
		glPopMatrix();

		//StreetLight - Bronze
			//SolidCenter
		glPushMatrix();
			glScaled(0.25, 1.5, 0.25);
			CreateCube(5.5, 0.5, 0.0, 0.2125f, 0.1275f, 0.054f, 0.714f, 0.4284f, 0.18144f, 0.393548f, 0.271906f, 0.166721f, 25.6f);
		glPopMatrix();

		//Cube - Gold
		glPushMatrix();
			glScaled(0.50, 0.50, 0.50);
			CreateCube(2.5, 3.75, -0.15, 0.24725f, 0.1995f, 0.0745f, 0.75164f, 0.60648f, 0.22648f, 0.628281f, 0.555802f, 0.366065f, 51.2F);
		glPopMatrix();

		//Cylinder
		glPushMatrix();
			glTranslated(0.5, 0.5, 1.0);
			glScaled(0.25, 0.25, 0.25);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawColoredCylinderS(113.0 / 255.0, 255.0 / 255.0, 181.0 / 255.0, 0.5, 0.5, 0.5, 100.0, 1.0, 2.0, 8.0, 8.0);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void Fog() {
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.10);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 5.0);
}

void PointLight0() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glRotatef(rotationLight, 1.0, 0.0, 0.0);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);   // Both ambient and diffuse is white
	glPopMatrix();
}

void init(void)
{
	// Set clear (background) color
	glClearColor(0.3, 0.32, 0.354, 0.0);

	//AmbientLight
	GLfloat amb[] = { 1.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	// Set light properties...
	// Light 0 -- SpotLight
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);     // white light
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color0);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, (float)45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);

	// Light 1 -- Attenuated by distance -- directional light
	GLfloat light_color1[] = { lightIntensity, 0.0, 0.0, 1.0 }; //red
	GLfloat light_color1_amb[] = { lightIntensity * 0.3, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);     // white light
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_color1_amb);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);   // Both ambient and diffuse is white
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_color1);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.02);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.08);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);

	//Point light
	GLfloat light_position2[] = { 0.0, -2.0, 0.0, 0.0 };  // green light, position to the left
	GLfloat light2_color[] = { 0.0, 0.0, 0.8, 1.0 };

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_color);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_color);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_color);

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
	glEnable(GL_LIGHT2);

	//Fog
	Fog();
	// for KB select and moving lights
	lightSelect = NONE;

	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.10, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Using ORTHOGRAPHIC projection
	//glOrtho(-1.0*w/80.0, 1.0*w/80.0, -1.0*h/80.0, 1.0*h/80.0, 0.1, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(10.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 't':
		if (toggleShadeModel) {
			toggleShadeModel = false;
			glShadeModel(GL_FLAT);
		}
		else {
			toggleShadeModel = true;
			glShadeModel(GL_SMOOTH);
		}
		glutPostRedisplay();
		break;
	case 'w':
		rotation += 1.0f;
		break;
	case 'W':
		rotation -= 1.00f;
		break;

	case 'x':
		glEnable(GL_LIGHT0);
		break;
	case 'X':
		glDisable(GL_LIGHT0);
		break;
	case 'z':
		glEnable(GL_LIGHT1);
		break;
	case 'Z':
		glDisable(GL_LIGHT1);
		break;
	case 'c':
		glEnable(GL_LIGHT2);
		break;
	case 'C':
		glDisable(GL_LIGHT2);
		break;
	case 'o':
		rotationLight += 1;
		PointLight0();
		break;
	case 'O':
		rotationLight -= 1;
		PointLight0();
		break;

		case 0x1B:
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

// Use the arrow keys (in OpenGL) to move objects
void processSpecialKeys(int key, int x, int y)
{
	switch(key) {
		case GLUT_KEY_UP :
			break;
		case GLUT_KEY_DOWN :
			break;
		case GLUT_KEY_LEFT :
			break;
		case GLUT_KEY_RIGHT :
			break;
	}

	glutPostRedisplay();
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lighting Example");
	init();

	glutKeyboardFunc(keyboard);
    glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
