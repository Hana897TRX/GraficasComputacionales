#include <windows.h>
#include <GL/gl.h>
#include <glut.h>

static float step = 0.0f, stepinc = 0.05f;
static bool doAuto = false;
double cubeSize = 2.0;

void drawAxis( double length )
{
    // Draw a z-axis with a cone at the end
    // From CG using OpenGL - Hill and Kelley
    glPushMatrix();

    // Draw line
    glBegin(GL_LINES);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, length);
    glEnd();

    // Draw cone
    glTranslated(0.0, 0.0, length - 0.2);
    glutSolidCone(0.04, 0.2, 12, 9);

    glPopMatrix();

}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void inClassExercise(void)
{
	// Draw a wire cube
	// ----------------------------------------------------
    glColor3f(1.0, 1.0, 1.0);
    //NOTE: A opengl cube is centered at the Origin
    //      If we want a vertex of the cube at the origin,
    //      then we have to translate the cube first

    glPushMatrix();
        glTranslated(cubeSize / 2.0, cubeSize / 2.0, cubeSize / 2.0);
        glutWireCube( cubeSize );
    glPopMatrix();

    // Draw reference frame
    // ----------------------------------------------------
    glLineWidth( 2.0 );

    // z axis
	glColor3f(1.0, 0.0, 0.0);
	drawAxis( 1.0 );

    // x axis
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	    glRotated(90.0, 0.0, 1.0, 0.0);
	    drawAxis( 1.0 );
	glPopMatrix();

    // y axis
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	    glRotated(-90.0, 1.0, 0.0, 0.0);
	    drawAxis( 1.0 );
	glPopMatrix();

	glLineWidth( 1.0 );

    // Draw teapots
	// ----------------------------------------------------
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(cubeSize, cubeSize, cubeSize);
    // big one
    glutSolidTeapot(0.3);
    glPopMatrix();

    // little one
    glColor3f(0.505, 0.913, 0.886);
    glPushMatrix();
        glTranslated(cubeSize, cubeSize, cubeSize);
        glRotatef(step * 2.0, 0.0, 1.0, 0.0);
        glTranslatef(0.6, 0, 0);
        glutSolidTeapot(0.15);
    glPopMatrix();

    // Draw torus
	// ----------------------------------------------------
	// TO DO - Set Color
	// TO DO - Apply transformations - Move to one of the vertices
	// NOTE: dimension of cube given by cubeSize

    // big one
    glColor3f(0.8, 0.8, 1);
    glPushMatrix();
        glTranslated(0.0, cubeSize, 0.0);
        glRotatef(step, 0.0, 0.0, -1.0);
        glutWireTorus(0.15, 0.3, 10, 10);
    glPopMatrix();

    // TO DO - Apply transformations - Move object out (0.6 suggested)
    //          and rotate (by step*2.0 suggested) around larger object
    // Note: what has to be done first: rotate or translate?

    // little one
    glPushMatrix();
        glTranslated(0.0, cubeSize, 0.0);
        glRotatef(step * 2.0, 0.0, 0.0, 1.0);
        glTranslatef(0.6, 0, 0);
        glutWireTorus(0.075, 0.15, 10, 10);
    glPopMatrix();

    // Draw cubes
	// ----------------------------------------------------

    glColor3f(1, 0.4, 1);
    // big one
    glPushMatrix();
        glTranslated(0.0, 0.0, cubeSize);
        glutWireCube( 0.3 );
    glPopMatrix();

    // little one
    glPushMatrix();
        glTranslated(0.0, 0.6, cubeSize);
        glRotated(step * 2.0, 0.0, 1.0, 0.0);
        glutWireCube( 0.15 );
    glPopMatrix();

    // Draw cones
	// ----------------------------------------------------
    // TO DO - Set Color
	// TO DO - Apply transformations - Move to one of the vertices
	// NOTE: dimension of cube given by cubeSize
    glColor3f(0.4, 0.568, 1);
    // big one
    glPushMatrix();
        glTranslated(cubeSize, 0.0, cubeSize);
        glRotated(step, 0.5, 0.0, 0.5);
        glRotated(step * 4.0, 0.0, 0.0, -1.0);
        glutWireCone(0.3, 0.5, 10, 10 );
    glPopMatrix();
    // TO DO - Apply transformations - Move object out (0.6 suggested)
    //          and rotate (by step*2.0 suggested) around larger object
    // Note: what has to be done first: rotate or translate?

    // little one
    glColor3f(0.898, 0.8, 1);
    glPushMatrix();
        glTranslated(cubeSize, 0.0, cubeSize);
        glRotated(step, 0.5, 0.0, 0.5);
        glTranslated(0.0, 0.0, 0.8);
        glRotated(180, 0.0, 1.0, 0.0);
        glRotated(step * 6.0, 0.0, 0.0, 1.0);
        glutWireCone(0.15, 0.3, 10, 10 );
    glPopMatrix();

    // Draw spheres
	// ----------------------------------------------------
    // TO DO - Set Color
	// TO DO - Apply transformations - Move to one of the vertices
	// NOTE: dimension of cube given by cubeSize

    // big one
    glColor3f(0.2, 1, 0.6);
    glPushMatrix();
        glTranslated(cubeSize, 0.0, 0.0);
        glutSolidSphere( 0.3, 10, 10 );
    glPopMatrix();
    // TO DO - Apply transformations - Move object out (0.6 suggested)
    //          and rotate (by step*2.0 suggested) around larger object
    // Note: what has to be done first: rotate or translate?

    // little one
    glColor3f(0.458, 0.458, 0.458);
    glPushMatrix();
        glTranslated(cubeSize, 0.0, 0.0);
        glRotated(step * 2.0, 0.0, 0.5, 0.5);
        glTranslated(0.6, 0.0, 0.0);
        glutSolidSphere( 0.15, 10, 10 );
    glPopMatrix();
    // Draw dodecahedra
	// ----------------------------------------------------
    // TO DO - Set Color
	// TO DO - Apply transformations - Move to one of the vertices
	// NOTE: dimension of cube given by cubeSize

    // big one
    // TO DO - This function generates a unitary Dodecahedron, so
    //          additional scaling is needed. Must add glScaled
    //          (a scale of 0.3 is recommended)
    // Note: Remember that scaling is a transformation, and it will be
    //          applied to all subsequent operations unless properly
    //          isolated.
    glColor3f(0.992, 0.709, 0.568);
    glPushMatrix();
        glTranslated(0.0, cubeSize, cubeSize);
        glScaled(0.3, 0.3, 0.3);
        glRotated(step * 2.0, 0.0, 0.0, 1.0);
        glutWireDodecahedron();
    glPopMatrix();
    // TO DO - Apply transformations - Move object out (0.6 suggested)
    //          and rotate (by step*2.0 suggested) around larger object
    // Note: what has to be done first: rotate or translate?

    // little one
    glColor3f(0.854, 0.305, 0.062);
    glPushMatrix();
        glTranslated(0.0, cubeSize + 0.8, cubeSize);
        glScaled(0.1, 0.1, 0.1);
        glRotated(step * 3.0, 0.0, 1.0, 0.0);
        glutWireDodecahedron();
    glPopMatrix();

    glColor3f(0.815, 0.505, 0.913);
    glPushMatrix();
        glTranslated(0.0, cubeSize - 0.8, cubeSize);
        glScaled(0.1, 0.1, 0.1);
        glRotated(step * 3.0, 0.0, 1.0, 0.0);
        glutWireDodecahedron();
    glPopMatrix();

    // Draw icosahedra
	// ----------------------------------------------------
        // TO DO - Set Color
	// TO DO - Apply transformations - Move to one of the vertices
	// NOTE: dimension of cube given by cubeSize

    // big one
    // TO DO - This function generates a unitary Octahedron, so
    //          additional scaling is needed. Must add glScaled
    //          (a scale of 0.3 is recommended)
    // Note: Remember that scaling is a transformation, and it will be
    //          applied to all subsequent operations unless properly
    //          isolated.
    glColor3f(0.603, 0.062, 0.854);
    glPushMatrix();
        glTranslated(cubeSize, cubeSize,0.0);
        glScaled(0.3, 0.3, 0.3);
        glRotated(step * 3.0, 0.0, 1.0, 0.0);
        glutWireOctahedron();
    glPopMatrix();

    // TO DO - Apply transformations - Move object out (0.6 suggested)
    //          and rotate (by step*2.0 suggested) around larger object
    // Note: what has to be done first: rotate or translate?
    // little one
    glColor3f(0.505, 0.611, 0.913);
    glPushMatrix();
    glTranslated(cubeSize, cubeSize, 0.0);
        glRotated(step * 3.0, 0.0, 0.5, 0.5);
        glTranslated(0.6, 0.0, 0.0);
        glScaled(0.1, 0.1, 0.1);
        glutWireOctahedron();
    glPopMatrix();
}

void display(void)
{
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    // apply rotation
    glRotated(step, 0.0, 1.0, 0.0);

    // Call the function which does all the drawing
   	inClassExercise();

   	glPopMatrix();

	glutSwapBuffers();

	// Code for automatic movement of planet
	if (doAuto) {
		step = (GLfloat)(((GLint)(step*100.f + stepinc*100.f)) % 36000)/100.0f;
	}
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Point the camera at the center of the cube
	gluLookAt(3.0, 3.0, 5.0, cubeSize/2.0, cubeSize/2.0, cubeSize/2.0, 0.0, 1.0, 0.0);

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'a':
		case 'A':
			// Toggle automatic movement of planet
			if (doAuto)
				doAuto = false;
			else
				doAuto = true;

		// Manual control of day and year movement
		case 's':
		case 'S':
			step = (GLfloat)((GLint)(step + 1.0f) % 360);
			glutPostRedisplay();
			break;
		case 0x1B:
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			break;
	}
}

void mouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Make the increment move faster
		if (btn == GLUT_LEFT_BUTTON)
			stepinc = stepinc + 0.1f;
		// Make the incremente move slower
		else if (btn == GLUT_RIGHT_BUTTON)
			stepinc = stepinc - 0.1f;
		// If middle button, then set increment to 0
		else {
			stepinc = 0.0f;
		}

		glutPostRedisplay();
	}
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("In-class Example: Push and Pop");
	init();

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
