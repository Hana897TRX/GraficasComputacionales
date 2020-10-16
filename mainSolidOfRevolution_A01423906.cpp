#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <glut.h>
#include <iostream>

using namespace std;

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

static bool extrudeORsor = false;
static bool drawPoints = true;

static float xSpeed = 0.0, ySpeed = 0.0, xAngle = 0.0, yAngle = 0.0;

static int m = 10; // number of divisions in the solid of revolution
static int n = 16; // number of points in the profile

#define PI 3.1416

// Initialize the profile
GLfloat profile[16][3] = {{0.7, 0.0, 0.0},
    {0.35, 0.1, 0.0},
    {0.1, 0.2, 0.0},
    {0.1, 0.5, 0.0},
    {0.1, 0.8, 0.0},
    {0.2, 0.8, 0.0},
    {0.2, 0.83, 0.0},
    {0.23, 0.85, 0.0},
    {0.2, 0.87, 0.0},
    {0.2, 0.9, 0.0},
    {0.1, 0.9, 0.0},
    {0.1, 1.0, 0.0},
    {0.25, 1.25, 0.0},
    {0.5, 1.5, 0.0},
    {0.75, 1.75, 0.0},
    {1.0, 2.0, 0.0}};

// Create another profile variable, to store the transformed points
GLfloat totalPoints[10][16][3];

// function for matrix multiplication
// use pointers, so that result is stored in vec
void matrixmult( float *mat, float *vec, float *output) {
	
	float temp[3];
    // do matrix by vector mulitiplication and assign values
	// TO DO 
	output[0] = mat[0] * vec[0] + mat[4] * vec[1] + mat[8] * vec[2] + mat[12] * vec[3] + mat[3];
	output[1] = mat[1] * vec[0] + mat[5] * vec[1] + mat[9] * vec[2] + mat[13] * vec[3] + mat[7];
	output[2] = mat[2] * vec[0] + mat[6] * vec[1] + mat[10] * vec[2] + mat[14] * vec[3] + mat[11];
}

void normalize( float *vec)
{
	float magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	if (magnitude > 0.00000001) {
		vec[0] = vec[0] / magnitude;
		vec[1] = vec[1] / magnitude;
		vec[2] = vec[2] / magnitude;
	}
}

void crossproduct(float *vec1, float *vec2, float *output)
{
	float temp[3];

	output[0] =  vec1[1] * vec2[2] - vec1[2] * vec2[1];
	output[1] = -vec1[0] * vec2[2] + vec1[2] * vec2[0];
	output[2] =  vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void createSORPoints ()
{
    float angle = -2.0*PI/(float)m;
	float temp[3];

    // Create matrix
	float mat[16] = {0,0,0,0,
					 0,0,0,0,
					 0,0,0,0,
					 0,0,0,0};

	// If this is true, then use a transformation for an extrusion
	// THIS IS THE ONLY DIFFERENCE BETWEEN EXTRUDE AND SOLID OF REVOLUTION
	if ( extrudeORsor )
	{
		mat[0] = 1;
		mat[1] = 0;
		mat[2] = 0;
		mat[3] = 0;

		mat[4] = 0;
		mat[5] = 1;
		mat[6] = 0;
		mat[7] = 0;

		mat[8] = 0;
		mat[9] = 0;
		mat[10] = 1;
		mat[11] = 1;

		mat[12] = 0;
		mat[13] = 0;
		mat[14] = 1;
		mat[15] = 1;
	}
	// else create use matrix values for rotation
	else 
	{
		mat[0] = cos(angle);
		mat[2] = sin(angle);
		mat[5] = 1;
		mat[8] = -sin(angle);
		mat[10] = cos(angle);
		mat[15] = 1;
	}

	// Calculate points for (transformed) profiles
	// TO DO 

	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 3; k++) {
					totalPoints[i][j][k] = profile[j][k];
				}
			}
		}
		else {
			for (int j = 0; j < 16; j++) {
				float temp[3];
				for (int k = 0; k < 3; k++) {
					temp[k] = totalPoints[i - 1][j][k];
				}

				float output[3];

				matrixmult(&mat[0], &temp[0], &output[0]);

				for (int k = 0; k < 3; k++) {
					totalPoints[i][j][k] = output[k];
				}
			}
		}
	}
}

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
	glClearColor(0.75, 0.75, 0.75, 1.0);
	glEnable(GL_DEPTH_TEST);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set light
	GLfloat myPos[] = {1.0, 3.0, 10.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, myPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Update LIGHT properties
	updateLights();

	// create Solid of Revolution (SOR) points
	createSORPoints();
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
    float vx1, vx2, vy1, vy2, vz1, vz2, nx, ny, nz;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Set material properties
	setMaterials();

	glPushMatrix();
	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);

	// Create solid of revolution
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n-1; j++){

            // Calculate the normal. There are several options:
            // 1 - Calculate a normal for each point
            // 2 - Calculate a normal for each face
            // A - Calculate the normal based on the current polygon
            // B - Calculate the normal based on the 4 adjacent polygons, and obtain an average
            // C - Calculate the normal based on a (known) underlying surface
            // In this case, calculate one normal per polygon, based only on the polygon vertices (cross product)
            vx1 = totalPoints[0][j+1][0] - totalPoints[i][j+1][0];
            vx2 = totalPoints[0][j][0] - totalPoints[i][j+1][0];
            vy1 = totalPoints[0][j+1][1] - totalPoints[i][j+1][1];
            vy2 = totalPoints[0][j][1] - totalPoints[i][j+1][1];
            vz1 = totalPoints[0][j+1][2] - totalPoints[i][j+1][2];
            vz2 = totalPoints[0][j][2] - totalPoints[i][j+1][2];

            nx = vy1*vz2 - vz1*vy2;
            ny = -vx1*vz2 - vz1*vx2;
            nz = vx1*vy2 - vy1*vx2;

            // Set the normal
			// If normal is based on the polygon, then it is the same for both polygons
            glNormal3f(nx, ny, nz);
            
            if (i == m-1 ) {
				if (!extrudeORsor){
					// Draw polygons between the last and the first profile
					glVertex3fv(totalPoints[0][j]);
					glVertex3fv(totalPoints[0][j + 1]);
					glVertex3fv(totalPoints[i][j]);

					glVertex3fv(totalPoints[i][j]);
					glVertex3fv(totalPoints[i][j + 1]);
					glVertex3fv(totalPoints[0][j + 1]);
				}
            }
            else {
				// Draw polygons between the other profiles
				glVertex3fv(totalPoints[i][j]);
				glVertex3fv(totalPoints[i][j + 1]);
				glVertex3fv(totalPoints[i + 1][j]);

				glVertex3fv(totalPoints[i + 1][j]);
				glVertex3fv(totalPoints[i + 1][j + 1]);
				glVertex3fv(totalPoints[i][j + 1]);
            }
        }
    }
    glEnd();

    // draw the actual points, if needed
    if (drawPoints) {
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 0.1, 0.1);
        glPointSize(2.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){

                glVertex3f(totalPoints[i][j][0], totalPoints[i][j][1], totalPoints[i][j][2]);
            }
        }
        glEnd();
		glEnable(GL_LIGHTING);
    }

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
	float aspect = (((float)w)/(float)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, 0.01, 30.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 7.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
}

// Use the arrow keys (in OpenGL) for controlling cylinder
void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_UP :
				m += 1;
				if (m > 10)
                    m = 10;
				break;
		case GLUT_KEY_DOWN :
				m -= 1;
				if (m < 2)
                    m = 2;
				break;
		case GLUT_KEY_LEFT :
				n += 1;
				if (n > 16)
                    n = 16;
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
			if(extrudeORsor)
				extrudeORsor = false;
			else
				extrudeORsor = true;
			m = 10;
			n = 16;
			createSORPoints();
			glutPostRedisplay();
			break;

		case 'T':
			drawPoints = !drawPoints;
			glutPostRedisplay();
			break;

		case '*':
			xSpeed += 0.1;
			break;
		case '+':
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
		case 'v':
			m--;
			if (m < 2)
				m = 2;
			break;
		case 'V':
			m++;
			if (m > 10)
				m = 10;
			break;
		case 'c':
			n--;
			if (n < 2)
				n = 2;
			break;
		case 'C':
			n++;
			if (n > 16)
				n = 16;
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
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solid of Revolution - TO DO in class");

	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinner);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
	return 0;
}
