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
GLfloat light_position0[] = {  0.0, 4.0, 0.0, 0.0};   // white light, position from above
GLfloat light_position1[] = { 4.0, 0.0, 0.0, 0.0 };  // red light, position to the right
GLfloat light_position2[] = { -4.0, 0.0, 0.0, 0.0 };  // green light, position to the left
GLfloat light_position3[] = { 0.0, -4.0, 0.0, 0.0 };  // blue light, position to the bottom

void init(void)
{
    // Set clear (background) color
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
	GLfloat light_color2[] = {0.0, lightIntensity, 0.0, 1.0 }; //green
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
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	// Activate (enable) light 1-3
	// TO DO

	// for KB select and moving lights
	lightSelect = NONE;

	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);
}

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
    glTranslatef (0.0, 0.0,-h / 2.0);
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
	float cyAngleInc = 2.0 * M_PI / (float)slices;
	float cyHeightInc = height / (float)stacks;

	//Define material properties
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { rs, gs, bs, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &exp);
	glBegin(GL_TRIANGLE)


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
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Added controls to rotate the model around
	glPushMatrix();

	// TO DO 
	rotY += angleInc;
	// Draw objects
	// ---------------------------------------------------
	// 1 - draw white sphere at the  center of the image
	// Define and set material properties
	glPushMatrix();
		glRotatef(rotY, 0.0, 1.0, 0.0);
		drawColoredUnitSphere(1.0, 1.0, 1.0, 0.8, 0.8, 0.8, 200.0);
	glPopMatrix();

	// 2 - draw a red shiny sphere at the upper left
	// Define and set material properties

	glPushMatrix();
		glTranslatef(-horizontalD, displace, 0.0);
		glRotatef(rotY, 0.0, 1.0, 0.0);
		drawColoredUnitSphere(0.8, 0.0, 0.0, 1.0, 1.0, 1.0, 30.0);
	glPopMatrix();

	// 3 - draw a brown, opaque, "tree trunk"
	// Define and set material properties
	// TO DO
	glPushMatrix();
		glTranslated(0.0, -2.0, 0.0);
		glRotated(rotY * 0.03, 0.0, 1.0, 0.0);
		drawColoredCylinderS(113.0/255.0, 255.0/255.0, 181.0/255.0, 0.5, 0.5, 0.5, 100.0, 1.0, 2.0, 8.0, 8.0);
	glPopMatrix();
	glPushMatrix();
		glTranslated(horizontalD, -2.5, 0.0);
		mySolidCylinder(0.75, 2, 20, 25);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Using ORTHOGRAPHIC projection
	glOrtho(-1.0*w/80.0, 1.0*w/80.0, -1.0*h/80.0, 1.0*h/80.0, 0.1, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	case 's':
		horizontalD += 0.25;
		break;
	case 'S':
		horizontalD -= 0.25;
		break;
	case 'e':
		glDisable(GL_LIGHT0);
		break;
	case 'E':
		glEnable(GL_LIGHT0);
		break;
	case 'r':
		glDisable(GL_LIGHT1);
		break;
	case 'R':
		glEnable(GL_LIGHT1);
		break;
	case 'y':
		glDisable(GL_LIGHT2);
		break;
	case 'Y':
		glEnable(GL_LIGHT2);
		break;
	case 'u':
		glDisable(GL_LIGHT3);
		break;
	case 'U':
		glEnable(GL_LIGHT3);
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
