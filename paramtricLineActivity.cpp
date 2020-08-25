#include <Windows.h>
#include <GL/gl.h>
#include <glut.h>
float p1[3];
float p2[3];
float midPoint[3];

float pointSize = 8.0F;
float lineWidth = 4.0F;
int color = 0;
int selectPoint = 0;

float t = 0.5;

void init(void) {
	//Set clear background color (rgba)
	//RGB 0 to 1
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 3; i++) {
		p1[i] = 0.0;
		p2[i] = 0.0;
		midPoint[i] = 0.0;
	}
}

void CreateTriangle(float fposX, float fposY, float fposZ, float sposX, float sposY, float sposZ, float tposX, float tposY, float tposZ) {
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.2, 0.0);
		glVertex3f(fposX, fposY, fposZ);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(sposX, sposY, sposZ);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(tposX, tposY, tposZ);
	glEnd();
}

void CreateCube() {
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
}

void CreateRectangle() {
	//buttom
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.75, 0.0, 0.75);
	//leftSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 1.75, 0.75);

	//rightSide
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);

	//top
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.0, 1.75, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);

	//rightFrontSide
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);

	//leftFrontSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
}

void Cilinder(float _offset) {
	//buttom
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.75, 0.0, 0.75);
	//leftSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 1.75, 0.75);

	//rightSide
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);

	//top
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.0, 1.75, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);

	//rightFrontSide
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);

	//leftFrontSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
}

void display(void) {
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(pointSize);

	if (color == 0)
		glColor3f(1.0, 0.0, 0.0);
	else if(color == 1)
		glColor3f(0.0, 1.0, 0.0);
	if (color == 2)
		glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
		glVertex3fv(p1);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex3fv(p2);
	glEnd();

	// Calculate midpoint
	// first point = p1
	// second point = p2

	midPoint[0] = p1[0] + (p2[0] - p1[0]) * t;
	midPoint[1] = p1[1] + (p2[1] - p1[1]) * t;
	midPoint[2] = p1[2] + (p2[2] - p1[2]) * t;
	
	glBegin(GL_POINTS);
		glVertex3fv(midPoint);
	glEnd();
	
	glLineWidth(lineWidth);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3fv(p1);
		glVertex3fv(p2);
	glEnd();

	//glFlush();
	glutSwapBuffers();
}

void reshape(int _widht, int _height) {
	//Set the viewport size, based on function input

	glViewport(0, 0, (GLsizei)_widht, (GLsizei)_height);

	//Set the projction matrix based on input size
	glMatrixMode(GL_PROJECTION);
	//first set as identity
	//then set perspective projection parmeters based on aspect ratio
	glLoadIdentity();
	//gluPerspective(20.0, (GLfloat)_widht / (GLfloat)_height, 0.10, 20.0);
	gluOrtho2D(0, 400, 0, 400);

	//Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set the "look at" point - where the "camera" is and where it is "pointed"
	//gluLookAt(10.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 's':
		pointSize -= 1.0;
		if (pointSize == 0.0)
			pointSize = 1.0;
		glutPostRedisplay();
		break;
	case 'S':
		pointSize += 1.0;
		if (pointSize >= 10.0)
			pointSize = 9.0;
		glutPostRedisplay();
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		color += 1;
		if (color == 3)
			color = 0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		color -= 1;
		if (color == -1)
			color = 2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (t > 0)
			t -= 0.025;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (t < 1)
			t += 0.025;
		glutPostRedisplay();
		break;
	}
}

void mouse(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN) 
	{
		if (btn == GLUT_LEFT_BUTTON) 
		{
			p1[0] = x;
			p1[1] = 400 - y;

			glutPostRedisplay();
		}
		if (btn == GLUT_RIGHT_BUTTON) {
			p2[0] = x;
			p2[1] = 400 - y;

			glutPostRedisplay();
		}
	}
}

void idle(void)
{
	p1[0] += 0.1;
	p2[0] += 0.1;

	p1[1] -= 0.1;
	p2[1] -= 0.1;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//GLUT INITIALIZATION
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Parametric Line Activity");

	//Additional initialization
	init();

	//Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	//glutIdleFunc(idle);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouse);

	//Do main loop
	glutMainLoop();

	//Exit
	return 0;
}